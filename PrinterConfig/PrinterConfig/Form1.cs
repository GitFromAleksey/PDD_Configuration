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
            comboBoxPorts.Items.Clear();
            comboBoxPorts.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames()); // список COM портов
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen) return;

            if (comboBoxPorts.Text.Length == 0) return;

            serialPort1.PortName = comboBoxPorts.Text;
            serialPort1.Open();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            byte[] txBuf = new byte[100];

            txBuf[0] = (byte)'<';
            txBuf[1] = (byte)11;
            txBuf[2] = (byte)0x03;
            txBuf[3] = (byte)'D';
            txBuf[4] = (byte)'F';
            txBuf[5] = (byte)'F';
            txBuf[6] = (byte)'F';
            txBuf[7] = (byte)'F';
            txBuf[8] = (byte)'F';
            txBuf[9] = (byte)'>';

            if (serialPort1.IsOpen)
            {
                serialPort1.Write(txBuf, 0, 10);
                //serialPort1.WriteLine(textBox2.Text);
            }
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            rxString += serialPort1.ReadExisting().Replace("\0", "") + "\r\n";
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            textBoxLog.Text = rxString;
        }
    }
}
