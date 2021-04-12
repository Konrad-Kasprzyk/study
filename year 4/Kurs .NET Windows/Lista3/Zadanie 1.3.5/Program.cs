using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Zadanie_1._3._5
{
    public class Person
    {
        public string Name { get; set; }
        public string Surname { get; set; }
        public long Pesel { get; set; }
    }

    public class Account
    {
        public long Pesel { get; set; }
        public long AccountNumber { get; set; }
    }
    
    internal class Program
    {
        public static void Main(string[] args)
        {
            string peselPath = Path.Combine(Directory.GetCurrentDirectory(), "first_file_1_3_5.txt");
            string accountsPath = Path.Combine(Directory.GetCurrentDirectory(), "second_file_1_3_5.txt");
            var peselReader = new StreamReader(peselPath);
            var accountsReader = new StreamReader(accountsPath);
            var people = new List<Person>();
            var accounts = new List<Account>();
            string temp;
            string[] data;
            while ((temp = peselReader.ReadLine()) != null)
            {
                data = temp.Split(' ');
                people.Add(new Person() {Name = data[0], Surname = data[1], Pesel = long.Parse(data[2])});
            }
            while ((temp = accountsReader.ReadLine()) != null)
            {
                data = temp.Split(' ');
                accounts.Add(new Account() {Pesel = long.Parse(data[0]), AccountNumber = long.Parse(data[1])});
            }

            Console.WriteLine("File 1");
            foreach (Person p in people)
                Console.WriteLine($"{p.Name} {p.Surname} {p.Pesel}");
            Console.WriteLine("\nFile 2");
            foreach (Account a in accounts)
                Console.WriteLine($"{a.Pesel} {a.AccountNumber}");
            Console.WriteLine();
            
            foreach (var item in
                from per in people
                join acc in accounts on per.Pesel equals acc.Pesel
                select new { Name = per.Name, Surname = per.Surname, Pesel = per.Pesel, AccountNumber = acc.AccountNumber })
            {
                Console.WriteLine(item);
            }
            
            Console.ReadKey();
        }
    }
}