using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Zadanie_2_1_3
{
    public partial class Form1 : Form
    {
        static int Width = 350;
        static int Height = 350;
        int secHAND = 110, minHAND = 95, hrHAND = 80;
        int CenterX = Width / 2;
        int CenterY = Height / 2;

        public Form1()
        {
            InitializeComponent();

            this.SetStyle(ControlStyles.UserPaint, true);
            this.SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            this.SetStyle(ControlStyles.DoubleBuffer, true);
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            this.Invalidate();
        }

        protected override void OnPaint( PaintEventArgs e )
        {
            var currTime = DateTime.Now;
            Graphics g = e.Graphics;
            using ( Font f = new Font( "LED", 48 ) )
            {
                StringFormat sf = new StringFormat();
                sf.Alignment = StringAlignment.Center;
                sf.LineAlignment = StringAlignment.Center;
                g.Clear( SystemColors.Control );
                g.DrawEllipse(new Pen(Color.Black, 1f), 0, 0, Width, Height);

                g.DrawString("12", f, Brushes.Black, 125, 0);
                g.DrawString("3", f, Brushes.Black, 290, 140);
                g.DrawString("6", f, Brushes.Black, 145, 282);
                g.DrawString("9", f, Brushes.Black, 0, 140);

                //second hand
                int[] handPoint = secAndMinPoint(currTime.Second, secHAND);
                g.DrawLine(new Pen(Color.Red, 1f), CenterX, CenterY, handPoint[0], handPoint[1]);

                //minute hand
                handPoint = secAndMinPoint(currTime.Minute, minHAND);
                g.DrawLine(new Pen(Color.Black, 3f), CenterX, CenterY, handPoint[0], handPoint[1]);

                //hour hand
                handPoint = hrPoint(currTime.Hour%12, currTime.Minute, hrHAND);
                g.DrawLine(new Pen(Color.Gray, 5f), CenterX, CenterY, handPoint[0], handPoint[1]);
            }
        }

        private int[] secAndMinPoint(int val, int hlen)
        {
            int[] hPoint = new int[2];
            val *= 6;   //each minute and second make 6 degree

            if (val >= 0 && val <= 180)
            {
                hPoint[0] = CenterX + (int)(hlen * Math.Sin(Math.PI * val / 180));
                hPoint[1] = CenterY - (int)(hlen * Math.Cos(Math.PI * val / 180));
            }
            else
            {
                hPoint[0] = CenterX - (int)(hlen * -Math.Sin(Math.PI * val / 180));
                hPoint[1] = CenterY - (int)(hlen * Math.Cos(Math.PI * val / 180));
            }
            return hPoint;
        }

        private int[] hrPoint(int hval, int mval, int hlen)
        {
            int[] hPoint = new int[2];

            //each hour makes 30 degree
            //each min makes 0.5 degree
            int val = (int)((hval * 30) + (mval * 0.5));

            if (val >= 0 && val <= 180)
            {
                hPoint[0] = CenterX + (int)(hlen * Math.Sin(Math.PI * val / 180));
                hPoint[1] = CenterY - (int)(hlen * Math.Cos(Math.PI * val / 180));
            }
            else
            {
                hPoint[0] = CenterX - (int)(hlen * -Math.Sin(Math.PI * val / 180));
                hPoint[1] = CenterY - (int)(hlen * Math.Cos(Math.PI * val / 180));
            }
            return hPoint;
        }
    }
}
