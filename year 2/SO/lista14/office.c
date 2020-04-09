#include "csapp.h"

static __thread unsigned seed;

#define DEBUG
#ifdef DEBUG
static __unused void outc(char c) {
  Write(STDOUT_FILENO, &c, 1);
}
#else
#define outc(c)
#endif

typedef struct office {
  /* TODO: Put internal state & mutexes & condvars here. */
  
  //something to determine which one to take; how to implement tickets?
  int free_seats;
  bool *seats; //if seat[number] is false then it is taken (numbered seats = tickets)
  int number_of_seats; //size of seats[]
  int next_customer; //determines which customer is taken by clerk
  bool is_job_done; //just for while loop for safety - doesn't matter
  bool clerk_busy;
  pthread_mutex_t mutex;
  pthread_cond_t clerk_waiting; //clerk doing nothing
  pthread_cond_t clerk_ready; //ready to take another customer
  pthread_cond_t job_done; //signal to customer that it's finished and he can go
} office_t;

static void office_init(office_t *o, unsigned seats) {
  /* TODO: Initialize internal state of post office. */
  o->free_seats = seats;
  o->seats = (bool*) malloc(seats * sizeof(bool));
  for(int i = 0; i < seats; i++){
    o->seats[i] = true;
  }
  o->number_of_seats = seats;
  o->next_customer = seats+1;
  o->is_job_done = false;
  o->clerk_busy = false;
  pthread_mutex_init(&(o->mutex), NULL);
  pthread_cond_init(&(o->clerk_waiting), NULL);
  pthread_cond_init(&(o->clerk_ready), NULL);
  pthread_cond_init(&(o->job_done), NULL);
}

static void office_destroy(office_t *o) {
  /* TODO: Destroy all synchronization primitives. */
  pthread_cond_destroy(&(o->clerk_ready));
  pthread_cond_destroy(&(o->clerk_waiting));
  pthread_cond_destroy(&(o->job_done));
  pthread_mutex_destroy(&(o->mutex));
  free(&(o->seats));
}

static int find_free_seat(office_t *o){
  for(int i = 0; i < o->number_of_seats; i++){
    if(o->seats[i]){
      safe_printf("[%ld] Took: %d \n",pthread_self(),i);
      o->seats[i] = false;
      return i;
    }
  }
  return -1;
}

static bool customer_walk_in(office_t *o) {
  /* TODO: No seats then leave, otherwise wait for a clerk call. */
  pthread_mutex_lock(&(o->mutex));
  bool walk_in = o->free_seats > 0;
  if(walk_in){
    
    //take a free seat with a number(ticket);
    o->free_seats--;
    int my_seat_number = find_free_seat(o);
    assert(my_seat_number != -1 && my_seat_number < o->number_of_seats); //for safety - it shouldn't happen
    
    //if I'm first I should wake the clerk
    if(o->free_seats == o->number_of_seats - 1){
      pthread_cond_signal(&(o->clerk_waiting));
    }
    
    while(my_seat_number != o->next_customer || o->clerk_busy){
      pthread_cond_wait(&(o->clerk_ready),&(o->mutex));
    }
    o->clerk_busy = true;
    //Going to the clerk, leaving my seat free;
    o->seats[my_seat_number] = true;
    safe_printf("[%ld] Released: %d \n",pthread_self(),my_seat_number);
    o->free_seats++;

    //Wait until the job is done
    while(!o->is_job_done)
      pthread_cond_wait(&(o->job_done),&(o->mutex));
    safe_printf("[%ld] Done the job, from seat: %d\n",pthread_self(), my_seat_number);

    o->is_job_done = false;
  }
  pthread_mutex_unlock(&(o->mutex));
  return walk_in;
}

static int find_first_waiting_customer(office_t* o, int prev_next){
  int i = (prev_next + 1 < o->number_of_seats) ? prev_next + 1 : 0;
      safe_printf("Find_first_waiting- prev_next: %d \n",prev_next);

  while(i != prev_next){
    safe_printf("Find_first_waiting- i: %d \n",i);
    //if somebody is on the seat then make him next
    if(!o->seats[i]){
      return i;
    }
    i = (i+1 < o->number_of_seats) ? i+1 : 0;
  }
  return prev_next;
}
static void clerk_wait(office_t *o) {
  /* TODO: Wait for a customer or call one from a seat. */
  pthread_mutex_lock(&(o->mutex));
    //while there is no customers
    while(o->free_seats == o->number_of_seats){
      pthread_cond_wait(&(o->clerk_waiting),&(o->mutex));
    }

    //TODO: determine which one to pick and save it in some variable in office* o
    o->next_customer = find_first_waiting_customer(o, o->next_customer);
    assert(o->next_customer != -1 && o->next_customer < o->number_of_seats); //for safety - it shouldn't happen
    pthread_cond_broadcast(&(o->clerk_ready));
  
  pthread_mutex_unlock(&(o->mutex));
}

static void clerk_done(office_t *o) {
  /* TODO: Tell the customer that the job is done. */
  pthread_mutex_lock(&(o->mutex));
    o->is_job_done = true;
  pthread_cond_signal(&(o->job_done)); //only one will wait for this signal
  o->clerk_busy = false;
  pthread_mutex_unlock(&(o->mutex));

}

static void *customer(void *data) {
  office_t *b = data;

  seed = (unsigned)pthread_self();

  while (true) {
    if (customer_walk_in(b)) {
      /* Yay! I sent my registered mail :) */
      outc('+');
      /* I guess they'll force me to go there again... */
      usleep(rand_r(&seed) % 5000 + 5000);
    } else {
      /* Heck! No empty seats :( */
      outc('-');
      /* Try again in a while... */
      usleep(rand_r(&seed) % 500 + 500);
    }
  }

  return NULL;
}

static void *clerk(void *data) {
  office_t *b = data;

  seed = (unsigned)pthread_self();

  while (true) {
    /* Wait for customer to walk in or grab one that is seated. */
    clerk_wait(b);
    /* Do the paperwork! */
    usleep(rand_r(&seed) % 500 + 500);
    /* Another customer leaving happy? */
    clerk_done(b);
  }

  return NULL;
}

#define SEATS 4
#define CUSTOMERS 12

int main(void) {
  office_t o;
  office_init(&o, SEATS);

  pthread_t clerkThread;
  pthread_t customerThread[CUSTOMERS];

  Pthread_create(&clerkThread, NULL, clerk, &o);
  for (int i = 0; i < CUSTOMERS; i++)
    Pthread_create(&customerThread[i], NULL, customer, &o);

  pthread_join(clerkThread, NULL);
  for (int i = 0; i < CUSTOMERS; i++)
    Pthread_join(customerThread[i], NULL);

  office_destroy(&o);
  return 0;
}
