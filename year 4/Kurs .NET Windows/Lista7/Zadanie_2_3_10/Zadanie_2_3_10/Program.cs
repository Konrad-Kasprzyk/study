using System;
using System.IO;
using System.Reflection;

namespace Zadanie_2_3_10
{
    class ResourceReader
    {
        public static string GetData(string filename)
        {
            var asm = Assembly.GetExecutingAssembly();
            using (Stream stream = asm.GetManifestResourceStream($"Zadanie_2_3_10.{filename}"))
            using (StreamReader reader = new StreamReader(stream ?? throw new InvalidOperationException(
                "Filename not found in current workspace")))
                return reader.ReadToEnd();
        }
    }
    
    internal class Program
    {
        public static void Main(string[] args)
        {
            Console.WriteLine(ResourceReader.GetData("Resource.txt"));
            Console.ReadKey();
        }
    }
}