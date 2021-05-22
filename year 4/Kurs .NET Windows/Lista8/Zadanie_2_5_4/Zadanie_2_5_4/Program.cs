using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zadanie_2_5_4
{
    class Program
    {
        static void Main(string[] args)
        {
            using (var context = new Zadanie2Context())
            {
                var miejscowosc = context.Miejscowosc.FirstOrDefault();
                if (miejscowosc != null)
                    miejscowosc.Nazwa = "Grzybowo";

                context.SaveChanges();

                var student = context.Student.FirstOrDefault();
                if (student != null)
                    context.Student.Remove(student);

                context.SaveChanges();

                var newMiejscowosc = new Miejscowosc() {Nazwa = "Tuszyn"};
                var newStudent = new Student() {Imie = "Kamil", Nazwisko = "Kowalski", DataUrodzenia = DateTime.Now.Date, Miejscowosc = newMiejscowosc};
                context.Miejscowosc.Add(newMiejscowosc);
                context.Student.Add(newStudent);

                context.SaveChanges();

                foreach (var m in context.Miejscowosc)
                {
                    Console.WriteLine(m.Nazwa);
                }

                foreach (var s in context.Student)
                {
                    Console.WriteLine($"{s.Imie} {s.Nazwisko} {s.DataUrodzenia} {s.Miejscowosc.Nazwa}");
                }
            }

            Console.ReadKey();
        }
    }

    public class Zadanie2Context : DbContext
    {
        public Zadanie2Context() : base("Server=localhost\\SQLEXPRESS;database=Zadanie2;integrated security=true") { }
        public Zadanie2Context(string connectionString) : base(connectionString) { }

        public DbSet<Student> Student { get; set; }
        public DbSet<Miejscowosc> Miejscowosc { get; set; }
    
        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);
            modelBuilder.Entity<Miejscowosc>().HasMany(miejscowosc => miejscowosc.Studenci).WithRequired(student => student.Miejscowosc).HasForeignKey(student => student.MiejscowoscID);
            modelBuilder.Entity<Miejscowosc>().ToTable("Miejscowosc");
            modelBuilder.Entity<Student>().ToTable("Student");
        }
    }

    public class Student
    {
        public int ID { get; set; }
        public string Imie { get; set; }
        public string Nazwisko { get; set; }
        public DateTime DataUrodzenia { get; set; }
        public virtual Miejscowosc Miejscowosc { get; set; }
        public int MiejscowoscID { get; set; }
    }

    public class Miejscowosc
    {
        public int ID { get; set; }
        public string Nazwa { get; set; }
        public ICollection<Student> Studenci { get; set; }
    }
}
