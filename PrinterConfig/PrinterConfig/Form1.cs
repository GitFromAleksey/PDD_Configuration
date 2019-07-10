using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PrinterConfig
{
    public partial class Form1 : Form
    {
        string rxString = "";
        
        public Form1()
        {
            InitializeComponent();
        }

        private void comboBox1_DropDown(object sender, EventArgs e)
        {
            comboBox1.Items.Clear();
            comboBox1.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames()); // список COM портов
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen) return;

            if (comboBox1.Text.Length == 0) return;

            serialPort1.PortName = comboBox1.Text;
            serialPort1.Open();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            byte[] txBuf = new byte[100];

            txBuf[0] = (byte)'A';
            txBuf[1] = (byte)'B';
            txBuf[2] = (byte)'C';
            txBuf[3] = (byte)'D';
            txBuf[4] = (byte)'F';
            txBuf[5] = (byte)'F';
            txBuf[6] = (byte)'F';
            txBuf[7] = (byte)'F';
            txBuf[8] = (byte)'F';
            txBuf[9] = (byte)'F';

            if (serialPort1.IsOpen)
            {
                serialPort1.Write(txBuf, 0, 10);
                //serialPort1.WriteLine(textBox2.Text);
            }
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            rxString += serialPort1.ReadExisting();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            textBox1.Text = rxString;
        }
    }
}
