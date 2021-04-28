using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Zadanie_2_1_1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            this.comboBox1.Items.Add("3-letnie");
            this.comboBox1.Items.Add("3.5-letnie");
            this.comboBox1.Items.Add("5-letnie");
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void buttonAccept_Click(object sender, EventArgs e)
        {
            string type = checkBox1.Checked ? checkBox1.Text : checkBox2.Text;
            MessageBox.Show(this.textBoxName.Text + "\n" + this.textBoxAddress.Text + "\n" + this.comboBox1.Text + "\n" + type, "Uczelnia");
        }
    }
}
