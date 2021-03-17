using System;
using System.Linq;

namespace Zadanie_1._1._2
{
    /// <summary>
    ///     Holds two dimensional int array. Elements are indexed from 1.
    /// </summary>
    public class Grid
    {
        private readonly int _columns;
        private readonly int[,] _elements;
        /// <summary>
        ///     Creates two dimensional int array.
        /// </summary>
        /// <param name="n">Number of rows.</param>
        /// <param name="m">Number of columns.</param>
        public Grid(int n, int m)
        {
            _elements = new int[n, m];
            _columns = m;
        }
        /// <summary>
        ///     Get row of elements.
        /// </summary>
        /// <param name="i">Row number, indexed from 1.</param>
        public int[] this[int i]
        {
            get
            {
                i--;
                return Enumerable.Range(0, _columns)
                    .Select(x => _elements[i, x])
                    .ToArray();
            }
        }
        /// <summary>
        ///     Get or set single element.
        /// </summary>
        /// <param name="i">Row number, indexed from 1.</param>
        /// <param name="j">Column number, indexed from 1.</param>
        public int this[int i, int j]
        {
            get => _elements[i - 1, j - 1];
            set => _elements[i - 1, j - 1] = value;
        }
    }
    
    internal static class Zadanie2
    {
        public static void Main(string[] args)
        {
            const int n = 2;
            const int m = 4;
            Grid grid1 = new Grid(n, m);
            for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                grid1[i, j] = i * 10 + j;

            Console.WriteLine("All elements");
            for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                Console.WriteLine(grid1[i, j]);

            Console.WriteLine("First row");
            foreach (int element in grid1[1]) Console.WriteLine(element);

            Console.WriteLine("First row after changes");
            grid1[1, 2] = 42;
            foreach (int element in grid1[1]) Console.WriteLine(element);
            Console.ReadKey();
        }
    }
}