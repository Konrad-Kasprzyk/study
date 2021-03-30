using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;

namespace Zadanie_1._2._4
{
    public class ListHelper
    {
        public static List<TOutput> ConvertAll<T, TOutput>(List<T> list, Converter<T, TOutput> converter)
        {
            if (list == null)
                return null;
            if (converter == null)
                throw new ArgumentNullException(nameof(converter));

            return list.Select(item => converter(item)).ToList();
        }

        public static List<T> FindAll<T>(List<T> list, Predicate<T> match)
        {
            if (list == null)
                return null;
            if (match == null)
                throw new ArgumentNullException(nameof(match));

            return list.Where(t => match(t)).ToList();
        }

        public static void ForEach<T>(List<T> list, Action<T> action)
        {
            if (action == null)
                throw new ArgumentNullException(nameof(action));

            foreach (T t in list)
                action(t);
        }

        public static int RemoveAll<T>(List<T> list, Predicate<T> match)
        {
            if (list == null)
                return 0;
            if (match == null)
                throw new ArgumentNullException(nameof(match));

            List<T> toRemove = list.Where(t => match(t)).ToList();
            int howMany = toRemove.Count;
            foreach (T t in toRemove)
            {
                list.Remove(t);
            }

            return howMany;
        }

        public static void Sort<T>(List<T> list, Comparison<T> comparison)
        {
            if (list == null)
                return;
            if (comparison == null)
                throw new ArgumentNullException(nameof(comparison));
            
            if (list.Count > 0)
                list.Sort(comparison);
        }
    }
    
    internal class Program
    {
        public static void Main(string[] args)
        {
            int Comp(int x, int y)
            {
                if (x < y) return -1;
                if (x > y) return 1;
                return 0;
            }

            List<char> startList = new List<char>{'3', '4', '5', '6', '9', '8', '7', '1', '2'};
            
            Console.WriteLine("Oryginalna lista char");
            foreach (char item in startList)
                Console.Write($"{item} ");
            
            Console.WriteLine("\n\nLista po ConvertAll do int");
            List<int> list = ListHelper.ConvertAll(startList, x => (int)char.GetNumericValue(x));
            foreach (int item in list)
                Console.Write($"{item} ");
            
            Console.WriteLine("\n\nLista po Sort");
            ListHelper.Sort(list, Comp);
            foreach (int item in list)
                Console.Write($"{item} ");
            
            Console.WriteLine("\n\nLista po FindAll 1<x<9");
            List<int> filteredList = ListHelper.FindAll(list, x => x > 1 && x < 9);
            foreach (int item in filteredList)
                Console.Write($"{item} ");

            Console.WriteLine("\n\nForEach dodający 10 do każdego elementu");
            ListHelper.ForEach(filteredList,  x => Console.Write($"{x + 10} "));
            
            Console.WriteLine("\n\nLista po RemoveAll x>5"); 
            ListHelper.RemoveAll(filteredList, x => x > 5);
            foreach (int item in filteredList)
                Console.Write($"{item} ");

            Console.ReadKey();
        }
    }
}