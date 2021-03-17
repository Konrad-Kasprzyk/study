using System;
using System.Linq;

namespace Zadanie_1._1._1
{
    internal static class Zadanie1
    {
        public static void Main(string[] args)
        {
            for (int i = 1; i < 100000; i++)
            {
                char[] charDigits = i.ToString().ToCharArray();
                int[] digits = Array.ConvertAll(charDigits, c => (int) char.GetNumericValue(c));
                bool skip = digits.Any(digit => digit != 0 && i % digit != 0);
                if (skip)
                    continue;
                int sum = digits.Sum();
                if (i % sum != 0)
                    continue;
                Console.WriteLine(i);
            }
            Console.ReadKey();
        }
    }
}