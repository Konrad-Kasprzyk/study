using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Zadanie_1._3._4
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Enter full directory path or leave empty for current directory:");
            string path = Console.ReadLine();
            if (string.IsNullOrEmpty(path))
                path = Directory.GetCurrentDirectory();

            var dir = new DirectoryInfo(path);
            var dirFiles = dir.GetFiles();
            var fileLengths = new List<long>();
            foreach (FileInfo f in dirFiles)
            {
                Console.WriteLine($"File {f.Name} has {f.Length} bytes.");
                fileLengths.Add(f.Length);
            }
            long allFilesLength = fileLengths.Aggregate((a, b) => a + b);
            Console.WriteLine($"All files length is {allFilesLength} bytes.");

            Console.ReadKey();
        }
    }
}