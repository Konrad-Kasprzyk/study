using System;
using System.Collections.Generic;

namespace Zadanie_2_3_2
{
    public class Set
    {
        private readonly List<int> _set;

        public Set()
        {
            _set = new List<int>();
        }

        public Set(params int[] elems)
        {
            _set = new List<int>();
            foreach (int elem in elems)
                AddItem(elem);
        }

        public void AddItem(int item)
        {
            if (_set.Contains(item))
                return;
            _set.Add(item);
        }
        
        public void Remove(int item) => _set.Remove(item);

        public void Clear() => _set.Clear();

        public bool Contains(int item) => _set.Contains(item);

        public int Count => _set.Count;

        public override string ToString()
        {
            if (Count == 0)
                return "";
            string res = _set[0].ToString();
            for (int i = 1; i < Count; i++)
                res += " " + _set[i];
            return res;
        }
    }

    internal class Program
    {
        public static void Main(string[] args)
        {
            Set set = new Set(1, 2, 3, 4, 5);
            Console.WriteLine($"Elements in set: {set}");
            set.AddItem(1);
            set.AddItem(2);
            set.AddItem(6);
            set.AddItem(42);
            Console.WriteLine($"Elements in set after adding 1, 2, 6, 42:\n{set}");

            Console.ReadKey();
        }
    }
}