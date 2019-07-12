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
            int i = 0;
            byte[] txBuf = new byte[100];

            // '<','Device_ID','Command','FirstRegAddress','CountToRead/WriteData','>'
            // '<','Device_ID','Command','FirstRegAddress','BytesCount','DataBytes','>'

            //txBuf[i++] = (byte)'<';
            //txBuf[i++] = (byte)11;
            //txBuf[i++] = (byte)0x01;
            //txBuf[i++] = (byte)0;
            //txBuf[i++] = (byte)10;
            //txBuf[i++] = (byte)'>';

            txBuf[i++] = (byte)'<';
            txBuf[i++] = (byte)11;      // ID
            txBuf[i++] = (byte)0x02;    // cmd
            txBuf[i++] = (byte)0;       // regAddr
            txBuf[i++] = (byte)1;       // countReadWriteData
            txBuf[i++] = (byte)'>';

            //txBuf[i++] = (byte)'<';
            //txBuf[i++] = (byte)11;      // ID
            //txBuf[i++] = (byte)0x03;    // cmd
            //txBuf[i++] = (byte)0;       // regAddr
            //txBuf[i++] = (byte)2;       // countReadWriteData(ignored)
            //txBuf[i++] = (byte)0x0E;    // msb data
            //txBuf[i++] = (byte)0x0F;    // lsb data
            //txBuf[i++] = (byte)'>';

            if (serialPort1.IsOpen)
            {
                serialPort1.Write(txBuf, 0, i);
                //serialPort1.WriteLine(textBox2.Text);
            }
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            byte[] b = new byte[50];
            int bytesToRead = serialPort1.BytesToRead;

            serialPort1.Read(b, 0, bytesToRead);

            for (int i = 0; i < bytesToRead; ++i)
            {
                rxString += b[i].ToString() + ",";
            }
            
            // rxString += serialPort1.ReadExisting() + "\r\n";
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            textBoxLog.Text = rxString;
        }
    }
}
