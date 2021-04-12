using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Zadanie_1._3._3
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            string path = Path.Combine(Directory.GetCurrentDirectory(), "file_1_3_3.txt");
            var reader = new StreamReader(path);
            string surname;
            var surnames = new List<string>();
            Console.WriteLine("All surnames:");
            while ((surname = reader.ReadLine()) != null)
            {
                surnames.Add(surname);
                Console.WriteLine(surname);
            }

            Console.WriteLine();
            foreach (char item in 
                from x in surnames
                group x by x[0] into set
                orderby set.Key
                select set.Key)
            {
                Console.WriteLine(item);
            }

            Console.ReadKey();
        }
    }
}