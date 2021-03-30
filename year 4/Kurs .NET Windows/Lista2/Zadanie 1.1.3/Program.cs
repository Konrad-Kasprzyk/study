using System;
using System.Reflection;

namespace Zadanie_1._1._3
{
    public class SampleClass
    {
        private readonly Random _rand = new Random();
        private void PrivateMethod()
        {
            int a = 42;
            int b = a * _rand.Next(100);
        }
        public void PublicMethod()
        {
            int a = 42;
            int b = a * _rand.Next(100);
        }
    }
    
    internal class Program
    {
        public static void Main(string[] args)
        {
            int loops = 20000000;
            TimeSpan private_time, public_time;
            DateTime start = DateTime.Now, end;
            SampleClass sampleObject = new SampleClass();
            
            for (int i = 0; i < loops; i++)
            {
                // Omit Just In Time loop start up delay
                if(i==20)
                    start = DateTime.Now;
                typeof(SampleClass).GetMethod("PrivateMethod", BindingFlags.NonPublic | BindingFlags.Instance)?.Invoke(sampleObject, null);
            }
            end = DateTime.Now;
            private_time = end - start;
            
            for (int i = 0; i < loops; i++)
            {
                // Omit Just In Time loop start up delay
                if(i==20)
                    start = DateTime.Now;
                sampleObject.PublicMethod();
            }
            end = DateTime.Now;
            public_time = end - start;

            Console.WriteLine($"Liczba iteracji - {loops}, Podsumowanie czasow wywołania metod:");
            Console.WriteLine($"Prywatna metoda = {private_time}");
            Console.WriteLine($"Publiczna metoda = {public_time}");
            Console.WriteLine("Wywołanie metody prywatnej za pomocą refleksji jest ponad 10 razy wolniejsze");
            Console.ReadKey();
        }
    }
}