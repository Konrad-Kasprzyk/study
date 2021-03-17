using System;
using System.Linq;

namespace Zadanie_1._1._6
{
    // example usage: methods, fields, properties, indexers, delegations, events, loops, if, switch
    public class Numbers
    {   
        // fields
        private readonly int[] _numbers;
        public int publicNumber = 42;

        // constructor
        public Numbers(int publicNumber)
        {
            this.publicNumber = publicNumber;
        }
        
        public Numbers(params int[] input)
        {
            _numbers = new int[input.Length];
            for (int i = 0; i < input.Length; i++)
                _numbers[i] = input[i];
        }
        
        // method
        public int Sum()
        {
            return _numbers.Sum();
        }

        // indexer
        public int this[int i]
        {
            get => _numbers[i]; 
            set => _numbers[i] = value;
        }

        // property
        public int NumberOfElements => _numbers.Length;
    }

    // delegate type
    public delegate void Operator(int x, int y);
    public class Maths
    {
        public static void StaticPrintSum(int x, int y) { Console.WriteLine(x + y); }
        public void PrintDiff(int x, int y) { Console.WriteLine(x - y); }
    }

    // event
    static class Calculate
    {
        public static event Operator Operators;

        public static void PerformCalculations(int x, int y)
        {
            Operators?.Invoke(x, y);
        }
    }

    
    internal static class Zadanie6
    {
        public static void Main(string[] args)
        {
            Numbers example = new Numbers(13);
            Console.WriteLine($"public number {example.publicNumber}"); 
            example = new Numbers(1, 2, 3, 4, 5, 6);
            Console.WriteLine(example.publicNumber);
            example.publicNumber = 99;
            example[2] = example.publicNumber;
            Console.WriteLine(example[2]);
            Console.WriteLine("Sum of elements equals " + example.Sum());
            Console.WriteLine(example.NumberOfElements);

            Maths maths = new Maths();
            Calculate.Operators += Maths.StaticPrintSum;
            Calculate.Operators += maths.PrintDiff;
            Calculate.PerformCalculations(4,2);

            for (int i = 0; i < 3; i++)
            {
                Console.WriteLine(i);
            }

            int j = 3;
            while (j >= 0)
            {
                Console.WriteLine(j);
                j--;
            }

            if (2 == 2)
                Console.WriteLine(2 == 2);
            
            int caseSwitch = 1;
            switch (caseSwitch)
            {
                case 1: Console.WriteLine("Case 1"); break;
                case 2: Console.WriteLine("Case 2"); break;
                case 3: Console.WriteLine("Case 3"); break;
                default: Console.WriteLine("Case default"); break;
            }
            Console.ReadKey(); 
        }
    }
}