using System;
using System.Globalization;

namespace Zadanie_2_3_1
{
    public class Complex : IFormattable
    {
        private const double Tolerance = 0.0000001;
        public double r, i;
        
        public Complex() {}
        public Complex(double r) { this.r = r; }
        public Complex(double r, double i) { this.r = r; this.i = i; }
        
        public static Complex operator + (Complex a, Complex b) 
            => new Complex(a.r + b.r, a.i + b.i);
        
        public static Complex operator - (Complex a, Complex b)
            => new Complex(a.r - b.r, a.i - b.i);
        
        public static Complex operator * (Complex a, Complex b)
            => new Complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
        
        public static Complex operator / (Complex a, Complex b)
            => new Complex((a.r * b.r + a.i * b.i) / (b.r * b.r + b.i * b.i),
                           (a.i * b.r - a.r * b.i) / (b.r * b.r + b.i * b.i));
        
        public static bool operator == (Complex a, Complex b)
            => Math.Abs(a.r - b.r) < Tolerance && Math.Abs(a.i - b.i) < Tolerance;
        
        public static bool operator != (Complex a, Complex b)
            => Math.Abs(a.r - b.r) > Tolerance || Math.Abs(a.i - b.i) > Tolerance;

        public override string ToString()
        {
            return ToString("d");
        }

        public string ToString(string format)
        {
            return this.ToString(format, null);
        }

        public string ToString(string format, IFormatProvider formatProvider)
        {
            if (string.IsNullOrEmpty(format)) format = "d";
            if (formatProvider == null) formatProvider = CultureInfo.CurrentCulture;

            switch (format)
            {
                case "d": return r + "+" + i + "i";
                case "w": return "[" + r + ", " + i + "]";
                default: throw new FormatException($"Invalid string format: {format}");
            }
        }
    }

    
    internal class Program
    {
        public static void Main(string[] args)
        {
            Complex z = new Complex(1, 3);
            Complex z2 = new Complex(1, 3);
            Complex z3 = z + z2;
            
            Console.WriteLine(String.Format("{0}", z3));
            Console.WriteLine(String.Format("{0:d}", z3));
            Console.WriteLine(String.Format("{0:w}", z3));

            Console.WriteLine(z == z2);
            Console.WriteLine(z != z2);

            Console.ReadKey();
        }
    }
}