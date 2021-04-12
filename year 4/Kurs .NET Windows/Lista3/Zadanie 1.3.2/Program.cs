using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Zadanie_1._3._2
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            string path = Path.Combine(Directory.GetCurrentDirectory(), "file_1_3_2.txt");
            var reader = new StreamReader(path);
            string number;
            var numbers = new List<int>();
            while ((number = reader.ReadLine()) != null)
                numbers.Add(int.Parse(number));

            Console.WriteLine("LINQ");
            foreach (int elem in 
                from x in numbers
                where x > 100
                orderby x descending
                select x)
            {
                Console.WriteLine(elem);
            }
            
            Console.WriteLine("\nLINQ to Objects");
            foreach (int elem in numbers
                .Where(x => x > 100)
                .OrderByDescending(x => x)
                )
            {
                Console.WriteLine(elem);
            }
            
            // Różnica pomiędzy LINQ where/orderby, a LINQ to Objects Where, OrderBy:
            // dla where/orderby używamy składni SQL, dla Where/OrderBy funkcji anonimowych.
            
            Console.ReadKey();
        }
    }
}