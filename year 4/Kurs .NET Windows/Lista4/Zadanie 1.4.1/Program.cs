using System;

namespace Zadanie_1._4._1
{
    internal class Program
    {
        static int Typed(int a, int b)
        {
            return a * 42 + 11 / (a + b) + 3;
        }
        static dynamic Dynamic(dynamic a, dynamic b)
        {
            return a * 42 + 11 / (a + b) + 3;
        }

        static void TestTyped(int howManyTimes)
        {
            DateTime start = DateTime.Now;
            for (int i = 0; i < howManyTimes; i++)
                Typed(i, 42);
            DateTime stop = DateTime.Now;
            Console.WriteLine($"Typed function time: {stop - start}");
        }

        static void TestDynamic(int howManyTimes)
        {
            DateTime start = DateTime.Now;
            for (int i = 0; i < howManyTimes; i++)
                Dynamic(i, 42);
            DateTime stop = DateTime.Now;
            Console.WriteLine($"Dynamic function time: {stop - start}");
        }
        
        public static void Main(string[] args)
        {
            Console.WriteLine("200 millions runs");
            TestTyped(200000000);
            TestDynamic(200000000);
            Console.ReadKey();
            // Test dla 200 mln wywołań
            // Typowana funkcja jest około 10-15 razy szybsza w tym konkretnym teście
        }
    }
}