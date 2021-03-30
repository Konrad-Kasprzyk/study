using System;
using System.Collections;
using System.Collections.Generic;

namespace Zadanie_1._2._1
{
     public static class MeasureClass
    {
        public static DateTime start, end;

        public static void MeasureDictionary(int loops, int loops2, int loops3)
        {
            Dictionary<int, int> dict = new Dictionary<int, int>();
            start = DateTime.Now;
            for (int i = 0; i < loops; i++) dict.Add(i, i);
            end = DateTime.Now;
            Console.WriteLine($"Dictionary czas wstawiania elementów dla {loops} iteracji: {end - start}");

            int holdInt;
            start = DateTime.Now;
            for (int i = 0; i < loops2; i++) holdInt= dict[i%loops];
            end = DateTime.Now;
            Console.WriteLine($"Dictionary czas przeglądania elementów dla {loops2} iteracji: {end - start}");
            
            start = DateTime.Now;
            for (int i = 0; i < loops3; i++) dict.Remove(i);
            end = DateTime.Now;
            Console.WriteLine($"Dictionary czas usuwania elementów dla {loops3} iteracji: {end - start}");
        }

        public static void MeasureHashtable(int loops, int loops2, int loops3)
        {
            Hashtable dict = new Hashtable();
            start = DateTime.Now;
            for (int i = 0; i < loops; i++) dict.Add(i, i);
            end = DateTime.Now;
            Console.WriteLine($"Hashtable czas wstawiania elementów dla {loops} iteracji: {end - start}");

            object holdObj;
            start = DateTime.Now;
            for (int i = 0; i < loops2; i++) holdObj = dict[i%loops];
            end = DateTime.Now;
            Console.WriteLine($"Hashtable czas przeglądania elementów dla {loops2} iteracji: {end - start}");
            
            start = DateTime.Now;
            for (int i = 0; i < loops3; i++) dict.Remove(i);
            end = DateTime.Now;
            Console.WriteLine($"Hashtable czas usuwania elementów dla {loops3} iteracji: {end - start}");
        }

        public static void MeasureList(int loops, int loops2, int loops3)
        {
            List<int> list = new List<int>();
            start = DateTime.Now;
            for (int i = 0; i < loops; i++) list.Add(i);
            end = DateTime.Now;
            Console.WriteLine($"List czas wstawiania elementów dla {loops} iteracji: {end - start}");

            int holdInt;
            start = DateTime.Now;
            for (int i = 0; i < loops2; i++) holdInt = list[i%loops];
            end = DateTime.Now;
            Console.WriteLine($"List czas przeglądania elementów dla {loops2} iteracji: {end - start}");
            
            start = DateTime.Now;
            for (int i = 0; i < loops3; i++) list.Remove(i);
            end = DateTime.Now;
            Console.WriteLine($"List czas usuwania elementów dla {loops3} iteracji: {end - start}");
        }
        
        public static void MeasureArrayList(int loops, int loops2, int loops3)
        {
            ArrayList list = new ArrayList();
            start = DateTime.Now;
            for (int i = 0; i < loops; i++) list.Add(i);
            end = DateTime.Now;
            Console.WriteLine($"ArrayList czas wstawiania elementów dla {loops} iteracji: {end - start}");

            object holdObj;
            start = DateTime.Now;
            for (int i = 0; i < loops2; i++) holdObj = list[i%loops];
            end = DateTime.Now;
            Console.WriteLine($"ArrayList czas przeglądania elementów dla {loops2} iteracji: {end - start}");
            
            start = DateTime.Now;
            for (int i = 0; i < loops3; i++) list.Remove(i);
            end = DateTime.Now;
            Console.WriteLine($"ArrayList czas usuwania elementów dla {loops3} iteracji: {end - start}");
        }
    }
     
    internal class Program
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Test dodawania elementów, wyszukania elementów i usuwania elementów ze struktury.");
            int howManyElements = 10000000;
            int howmanySearch = 100000000;
            int howmanyRemove = 10000000;
            MeasureClass.MeasureDictionary(howManyElements, howmanySearch, howmanyRemove);
            Console.WriteLine();
            MeasureClass.MeasureHashtable(howManyElements, howmanySearch, howmanyRemove);
            Console.WriteLine();
            
            howManyElements = 20000000;
            howmanySearch = 800000000;
            howmanyRemove = 500;
            MeasureClass.MeasureList(howManyElements, howmanySearch, howmanyRemove);
            Console.WriteLine();
            MeasureClass.MeasureArrayList(howManyElements, howmanySearch, howmanyRemove);

            Console.ReadKey();
            // Dictionary jest szybsze od Hashtable w tworzeniu, wyszukiwaniu i usuwaniu elementów wg testów.
            // Wg pomiarów z internetu powinno wyjść, że Hashtable ma szybsze wyszukiawnie elementów.
            
            // List jest szybsze od ArrayList w tworzeniu i usuwaniu elementów wg testów.
            // List jest lekko wolniejsze od ArrayList w wyszukiwaniu elementów wg testów.
        }
    }
}