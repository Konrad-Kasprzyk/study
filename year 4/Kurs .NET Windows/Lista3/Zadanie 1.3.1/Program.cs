using System;
using System.Linq;

namespace Zadanie_1._3._1
{
    public static class StringExtensions
    {
        public static bool IsPalindrome (this string s)
        {
            string clearS = new string(s.Where(c => char.IsLetter(c) || char.IsDigit(c)).ToArray());

            char[] charArray = clearS.ToCharArray();
            Array.Reverse( charArray );
            string reverseClearS = new string( charArray );

            return string.Equals(clearS, reverseClearS, StringComparison.OrdinalIgnoreCase);
        }
    }
    
    internal class Program
    {
        public static void Main(string[] args)
        {
            string s = "kajak";
            Console.WriteLine(s);
            Console.WriteLine(s.IsPalindrome());
            s = "\nKobyła ma mały bok.";
            Console.WriteLine(s);
            Console.WriteLine(s.IsPalindrome());
            s = "\n+-\\?$%*()Kobyła ma mały bok.";
            Console.WriteLine(s);
            Console.WriteLine(s.IsPalindrome());
            s = "\n+-\\?$%*() K o b y       ł a ma mały bok..";
            Console.WriteLine(s);
            Console.WriteLine(s.IsPalindrome());
            s = "\n123";
            Console.WriteLine(s);
            Console.WriteLine(s.IsPalindrome());
            Console.ReadKey();
        }
    }
}