using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Zadanie_1._3._6
{
    public class Request
    {
        public string Time { get; set; }
        public string Ip { get; set; }
        public string Type { get; set; }
        public string Resource { get; set; }
        public string Status{ get; set; }
    }
    
    internal class Program
    {
        public static void Main(string[] args)
        {
            string path = Path.Combine(Directory.GetCurrentDirectory(), "file_1_3_6.txt");
            var reader = new StreamReader(path);
            var requests = new List<Request>();

            string temp;
            while ((temp = reader.ReadLine()) != null)
            {
                string[] data = temp.Split(' ');
                requests.Add(new Request() 
                    {Time = data[0], Ip = data[1], Type = data[2], Resource = data[3], Status = data[4]});
            }

            var query = (from req in requests
                group req by req.Ip into r
                orderby r.Count() descending
                select new { IP = r.Key, Count = r.Count() }).Take(3);

            foreach (var item in query)
                Console.WriteLine(item);

            Console.ReadKey();
        }
    }
}