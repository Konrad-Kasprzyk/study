using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zadanie_2_5_3
{
    class Program
    {
        static void Main(string[] args)
        {
            // Wstaw Miejscowosc
            using (var context = new Zadanie2DataContext())
            {
               context.Miejscowoscs.InsertOnSubmit(new Miejscowosc(){Nazwa = "Biala"});
               context.Miejscowoscs.InsertOnSubmit(new Miejscowosc(){Nazwa = "ToDelete"});
               context.SubmitChanges();
            }

            // update, delete
            using (var context = new Zadanie2DataContext())
            {
                var miejscowosc = context.Miejscowoscs.FirstOrDefault(m => m.Nazwa == "Biala");
                if (miejscowosc != null)
                    miejscowosc.Nazwa = "Biala2";
                var miejscowoscDelete = context.Miejscowoscs.FirstOrDefault(m => m.Nazwa == "ToDelete");
                if (miejscowoscDelete != null)
                    context.Miejscowoscs.DeleteOnSubmit(miejscowoscDelete);
                context.SubmitChanges();
            }

            // Wstaw Studenta i Miejscowosc naraz
            using (var context = new Zadanie2DataContext())
            {
                var miejscowosc = new Miejscowosc() {Nazwa = "Sady"};
                context.Miejscowoscs.InsertOnSubmit(miejscowosc);
                var student = new Student()
                    {Imie = "Ola", Nazwisko = "Gruszka", DataUrodzenia = DateTime.Now.Date, Miejscowosc = miejscowosc};
                context.Students.InsertOnSubmit(student);
                context.SubmitChanges();
            }

            using (var context = new Zadanie2DataContext())
            {
                foreach (var miejscowosc in context.Miejscowoscs)
                {
                    Console.WriteLine($"{miejscowosc.ID} {miejscowosc.Nazwa}");
                }

                foreach (var student in context.Students)
                {
                    Console.WriteLine($"{student.ID} {student.Imie} {student.Miejscowosc.Nazwa}");
                }
            }

            Console.ReadKey();
        }
    }
}
