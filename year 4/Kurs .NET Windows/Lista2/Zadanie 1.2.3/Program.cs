using System;
using System.Collections.Generic;

namespace Zadanie_1._2._3
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            List<char> startList = new List<char>{'3', '4', '5', '6', '9', '8', '7', '1', '2'};
            
            Console.WriteLine("Oryginalna lista char");
            foreach (char item in startList)
                Console.Write($"{item} ");
            
            Console.WriteLine("\n\nLista po ConvertAll do int");
            List<int> list = startList.ConvertAll(delegate (char x) { return (int) char.GetNumericValue(x); });
            foreach (int item in list)
                Console.Write($"{item} ");
            
            Console.WriteLine("\n\nLista po Sort");
            list.Sort(delegate (int x, int y) { 
                if (x < y)
                    return -1;
                if (x > y)
                    return 1;
                return 0; });
            foreach (int item in list)
                Console.Write($"{item} ");
            
            Console.WriteLine("\n\nLista po FindAll 1<x<9");
            List<int> filteredList = list.FindAll(delegate (int x) { return x > 1 && x < 9; });
            foreach (int item in filteredList)
                Console.Write($"{item} ");

            Console.WriteLine("\n\nForEach dodający 10 do każdego elementu"); 
            filteredList.ForEach(delegate (int x) { Console.Write($"{x + 10} "); });
            
            Console.WriteLine("\n\nLista po RemoveAll x>5"); 
            filteredList.RemoveAll(delegate (int x) { return x > 5; });
            foreach (int item in filteredList)
                Console.Write($"{item} ");

            Console.ReadKey();
        }
    }
}