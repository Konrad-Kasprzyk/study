using System;
using System.Collections.Concurrent;
using System.Threading;

namespace Zadanie_2_3_4
{
    internal class Program
    {
        // A signal to the barber that a new client is waiting. If the barber is asleep, this signal will wake him up.
        static AutoResetEvent cutNextEvent = new AutoResetEvent(false);
        // Customers waiting in the waiting room.
        static ConcurrentQueue<Customer> customersQueue = new ConcurrentQueue<Customer>();

        public static void Main(string[] args)
        {
            Random rand = new Random();

            // Barber enters barbershop.
            new Thread(Barber.CutHair) { IsBackground = true, Name = "Barber" }.Start();
            Thread.Sleep(100);

            // Customers enter barbershop.
            for (int i = 0; i < 10; i++)
            {
                Customer c = new Customer() { Name = "Customer number " + i };
                new Thread(c.EnterBarbershop) {IsBackground = true, Name = "Thread" + i}.Start();
                Thread.Sleep(rand.Next(500, 1500));
            }
            Console.ReadKey();
        }

        class Barber
        {
            public static void CutHair()
            {
                while (!customersQueue.IsEmpty)
                {
                    // The haircut takes one second.
                    Thread.Sleep(1000);

                    if (customersQueue.TryDequeue(out Customer c))
                    {
                        Console.WriteLine("Barber served customer {0}.", c.Name);
                    }
                }

                Console.WriteLine("Barber falls asleep.");
                GoToSleep();
            }

            private static void GoToSleep()
            {
                cutNextEvent.WaitOne();
                Console.WriteLine("New client!");

                CutHair();
            }
        }
        
        class Customer
        {
            public string Name { get; set; }

            public void EnterBarbershop()
            {
                // There are no empty chairs in the waiting room.
                if (customersQueue.Count > 2)
                {
                    Console.WriteLine($"{Name} leaves the barber because there are no empty chairs in the waiting room");
                    return;
                }
                // Customer enter waiting room
                customersQueue.Enqueue(this);

                // If the client is the only one in the waiting room, it is possible that the barber is asleep.
                // Check if barber is asleep and wake him up if necessary.
                if (customersQueue.Count == 1)
                    cutNextEvent.Set();
                else
                    Console.WriteLine($"{Name} sits down in the waiting room.");
            }
        }
    }
}