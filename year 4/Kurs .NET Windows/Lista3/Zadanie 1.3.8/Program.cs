using System;
using System.Collections.Generic;
using System.Linq;

namespace Zadanie_1._3._8
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            var list = new List<int>() { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

            int Func(int x) => x <= 2 ? 1 : Func(x - 1) + Func(x - 2);
            
            foreach (int item in list.Select(Func))
                Console.WriteLine(item);

            Console.ReadKey();
        }
    }
}