using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;

namespace Zadanie_2_3_8
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            Console.OutputEncoding = Encoding.UTF8;
            List<CultureInfo> list = new List<CultureInfo>
            {
                new CultureInfo("en"),
                new CultureInfo("de"),
                new CultureInfo("fr"),
                new CultureInfo("ru"),
                new CultureInfo("ar"),
                new CultureInfo("cs"),
                new CultureInfo("pl")
            };

            foreach (var language in list)
            {
                Console.WriteLine("----------------");
                Console.WriteLine(language.NativeName + ":\n");
                
                for (int i = 0; i < 12; i++)
                    Console.WriteLine(language.DateTimeFormat.MonthNames[i] + " - " +
                                      language.DateTimeFormat.AbbreviatedMonthNames[i]);
                
                Console.WriteLine();
                for (int i = 0; i < 7; i++)
                    Console.WriteLine(language.DateTimeFormat.DayNames[i] + " - " +
                                      language.DateTimeFormat.AbbreviatedDayNames[i]);
                
                Console.WriteLine();
                Console.WriteLine(DateTime.Now.ToString(language));
            }
            Console.ReadKey();
        }
    }
}