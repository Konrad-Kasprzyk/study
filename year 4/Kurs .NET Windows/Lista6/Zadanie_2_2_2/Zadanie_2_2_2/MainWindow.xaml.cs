using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Zadanie_2_2_2
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public List<Employee> Employees { get; set; }
        public MainWindow()
        {
            InitializeComponent();
            Employees = new List<Employee>();
            Employees.Add(new Employee(){Name = "Max", Surname="Holloway"});
            Employees.Add(new Employee(){Name = "Adam", Surname="Szczucki"});
            Employees.Add(new Employee(){Name = "Marek", Surname="Mirek"});

            DataContext = this;
        }

    }

    public class Employee
    {
        public string Name { get; set; }
        public string Surname { get; set; }
    }
}
