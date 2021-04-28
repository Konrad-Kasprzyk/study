using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Zadanie_2_1_7
{
    public partial class Form1 : Form
    {
        HttpClient httpClient = new HttpClient();
        WebClient webClient = new WebClient();

        public Form1()
        {
            InitializeComponent();
        }

        private async void button1_Click(object sender, EventArgs e)
        {
            var response = await httpClient.GetStringAsync("https://www.google.pl/");
            this.textBox1.Text = response;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string response = webClient.DownloadString("https://www.google.pl/");
            this.textBox2.Text = response;
        }
    }
}
