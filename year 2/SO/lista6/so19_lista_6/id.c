#include "csapp.h"

static const char *uidname(uid_t uid) {
  /* TODO: Something is missing here! */
  struct passwd* pswd = getpwuid(uid);
  return pswd->pw_name;
  
}

static const char *gidname(gid_t gid) {
  /* TODO: Something is missing here! */
  struct group* grp = getgrgid(gid);
  return grp->gr_name;
}

static int getid(uid_t *uid_p, gid_t *gid_p, gid_t **gids_p) {
  gid_t *gids = NULL;
  int ngid = 2;
  int groups;

  /* TODO: Something is missing here! */

  *uid_p = getuid();
  *gid_p = getgid();
  // int getgroups(int size, gid_t list[]);
  // gdy size = 0, to gid_t list[] nie jest modyfikowany i zwracana jest liczba wszystkich id
  ngid = getgroups(0, NULL);
  gids = malloc(ngid * sizeof(gid_t));
  getgroups(ngid, gids);

  *gids_p = gids;
  return ngid;
}

int main(void) {
// uid - User Id, stored in /etc/passwd
// gid - Group Id

  uid_t uid;
  gid_t *gids, gid;
  int groups = getid(&uid, &gid, &gids);

  printf("uid=%d(%s) gid=%d(%s) ", uid, uidname(uid), gid, gidname(gid));
  printf("groups=%d(%s)", gids[0], gidname(gids[0]));
  for (int i = 1; i < groups; i++)
    printf(",%d(%s)", gids[i], gidname(gids[i]));
  putchar('\n');

  free(gids);

  return 0;
}
