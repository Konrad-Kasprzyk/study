using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Zadanie_2_1_2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            
            this.listView1.Columns.Clear();
            this.listView1.Items.Clear();

            this.listView1.Columns.Add("Nazwisko", 80);
            this.listView1.Columns.Add("imię", -2);

            ListViewItem li = this.listView1.Items.Add("Kowalski");
            li.SubItems.Add("Marek");

            li = this.listView1.Items.Add("Holloway");
            li.SubItems.Add("Max");
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            this.progressBar1.Increment(1);
        }


        private void buttonStartProgressBar_Click(object sender, EventArgs e)
        {
            this.timer1.Start();
        }


        private void buttonResetProgressBar_Click(object sender, EventArgs e)
        {
            this.timer1.Stop();
            this.progressBar1.Value = 0;
        }
    }
}
