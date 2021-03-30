using System;
using System.Reflection;

namespace Zadanie_1._1._4
{
    public class SampleAttribute : Attribute {}
    public class Oznakowane : Attribute {}

    public class SampleClass
    {
        [Oznakowane]
        public int ProperMethod() { return 1; }

        [Oznakowane]
        public char BadReturnTypeMethod() { return 'a'; }

        public bool BadReturnTypeNoAttributeMethod() { return true; }

        [SampleAttribute]
        public int BadAttributeMethod() { return 42; }
        
        [Oznakowane]
        public int WithParametersMethod(int foo) { return 42; }

        [Oznakowane]
        static public int StaticMethod() { return 42; }
        
        [Oznakowane]
        public int ProperMethod2() { return 2; }
    }
    internal class Program
    {
        /// <summary>
        /// Run object methods which have 'Oznakowane' attribute, are public,
        /// not static, return int and do not take parameters.
        /// </summary>
        /// <param name="obj">Object to run filtered methods</param>
        public static void PrintMethods(object obj)
        {
            MethodInfo[] sampleClassMethods = obj.GetType().GetMethods(BindingFlags.Public | BindingFlags.Instance | BindingFlags.DeclaredOnly);

            foreach (MethodInfo method in sampleClassMethods)
            {
                if (method.ReturnType != typeof(int) || method.GetParameters().Length != 0)
                    continue;
                if (method.GetCustomAttribute(typeof(Oznakowane)) is Oznakowane)
                    Console.WriteLine(method.Invoke(obj, null));
            }
        }
        
        public static void Main(string[] args)
        {
            SampleClass sampleClass = new SampleClass();
            PrintMethods(sampleClass);
            
            Console.ReadKey();
        }
    }
}