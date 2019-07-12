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

        // Protocol
        // Incoming packet format
        // '<','Device_ID','Command','FirstRegAddress','countReadWriteData','>'
        // Ansver packet format
        // '<','Device_ID','Command','FirstRegAddress','BytesCount','DataBytes','>'

        byte DeviceID = 11;
        const byte CMD_READ_READ_REGS   = 0x01;
        const byte CMD_WRITE_READ_REGS  = 0x04;
        const byte CMD_READ_RW_REGS     = 0x02;
        const byte CMD_WRITE_RW_REGS    = 0x03;
        const byte PACKET_START_SYMBOL  = (byte)'<';
        const byte PACKET_END_SYMBOL    = (byte)'>';

        const UInt16 ButtonCodeUp = (UInt16)(1 << 0);
        const UInt16 ButtonCodeDN = (UInt16)(1 << 1);
        const UInt16 ButtonCodeLF = (UInt16)(1 << 2);
        const UInt16 ButtonCodeRT = (UInt16)(1 << 3);
        const UInt16 ButtonCodeOK = (UInt16)(1 << 4);
        const UInt16 ButtonCodeESC = (UInt16)(1 << 5);
        const UInt16 ButtonCodeAUTO = (UInt16)(1 << 6);
        const UInt16 ButtonCode2P = (UInt16)(1 << 7);

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
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
                button1.Text = "Open Port";
                return;
            }

            if (comboBoxPorts.Text.Length == 0) return;

            serialPort1.PortName = comboBoxPorts.Text;
            serialPort1.Open();
            button1.Text = "Close Port";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen) return;
            
            int i = 0;
            byte[] txBuf = new byte[100];

            int ID = int.Parse(textBoxID.Text);
            int readRdRegNum = int.Parse(textBoxRdRegNum.Text);

            txBuf[i++] = (byte)PACKET_START_SYMBOL;
            txBuf[i++] = (byte)ID;      // Device_ID
            txBuf[i++] = (byte)CMD_READ_READ_REGS;    // Command
            txBuf[i++] = (byte)readRdRegNum;
            txBuf[i++] = (byte)1;
            txBuf[i++] = (byte)PACKET_END_SYMBOL;

            serialPort1.Write(txBuf, 0, i);
        }



        private void buttonGetRdWrReg_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen) return;

            int i = 0;
            byte[] txBuf = new byte[100];

            int ID = int.Parse(textBoxID.Text);
            int readRdRegNum = int.Parse(textBoxRdWrRegNum.Text);

            txBuf[i++] = (byte)PACKET_START_SYMBOL;
            txBuf[i++] = (byte)ID;      // ID
            txBuf[i++] = (byte)CMD_READ_RW_REGS;    // cmd
            txBuf[i++] = (byte)readRdRegNum;       // regAddr
            txBuf[i++] = (byte)1;       // countReadWriteData
            txBuf[i++] = (byte)PACKET_END_SYMBOL;

            serialPort1.Write(txBuf, 0, i);
        }

        private void buttonSetRdWrReg_Click(object sender, EventArgs e)
        {
            if (!serialPort1.IsOpen) return;

            int i = 0;
            byte[] txBuf = new byte[100];

            int ID = int.Parse(textBoxID.Text);
            int readRdRegNum = int.Parse(textBoxWrRegNum.Text);
            int writeData = int.Parse(textBoxWriteData.Text);

            txBuf[i++] = (byte)PACKET_START_SYMBOL;
            txBuf[i++] = (byte)ID;                  // ID
            txBuf[i++] = (byte)CMD_WRITE_RW_REGS;   // cmd
            txBuf[i++] = (byte)readRdRegNum;        // regAddr
            txBuf[i++] = (byte)2;                   // countReadWriteData(ignored)
            txBuf[i++] = (byte)((writeData>>8) & 0xFF); // msb data
            txBuf[i++] = (byte)(writeData & 0xFF);      // lsb data
            txBuf[i++] = (byte)PACKET_END_SYMBOL;

            serialPort1.Write(txBuf, 0, i);
        }



        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            byte[] b = new byte[50];
            int bytesToRead = serialPort1.BytesToRead;

            serialPort1.Read(b, 0, bytesToRead);

            rxString = "\r\n";

            for (int i = 0; i < bytesToRead; ++i)
                rxString += b[i].ToString() + ",";

            for (int i = 0; i < bytesToRead; ++i)
            {
                if (b[i] == PACKET_START_SYMBOL)
                {
                    if (b[i + 1] == DeviceID)
                    {
                        if (b[i + 2] == CMD_READ_READ_REGS)
                        {
                            rxString += "\r\nRdRegAddr: " + b[i + 3].ToString();
                            rxString += "\r\nRdRegData: " + ((b[i + 5]<<8)|b[i + 6]).ToString();
                        }
                        if (b[i + 2] == CMD_WRITE_READ_REGS)
                        {
                            rxString += "\r\nWrRegAddr: " + b[i + 3].ToString();
                            rxString += "\r\nWrRegData: " + ((b[i + 5] << 8) | b[i + 6]).ToString();
                        }
                        if (b[i + 2] == CMD_READ_RW_REGS)
                        {
                            rxString += "\r\nWrRegAddr: " + b[i + 3].ToString();
                            rxString += "\r\nWrRegData: " + ((b[i + 5] << 8) | b[i + 6]).ToString();
                        }
                        if (b[i + 2] == CMD_WRITE_RW_REGS)
                        {
                            rxString += "\r\nWrRegAddr: " + b[i + 3].ToString();
                            rxString += "\r\nWrRegData: " + ((b[i + 5] << 8) | b[i + 6]).ToString();
                        }
                    }
                }
            }
            
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            textBoxLog.Text = rxString;
        }

        private void buttonLF_Click(object sender, EventArgs e)
        {
            UInt16 writeData = ButtonCodeLF;
            SetRdReg( 0, writeData);
        }
        private void buttonRT_Click(object sender, EventArgs e)
        {
            UInt16 writeData = ButtonCodeRT;
            SetRdReg(0, writeData);
        }
        private void buttonESC_Click(object sender, EventArgs e)
        {
            UInt16 writeData = ButtonCodeESC;
            SetRdReg(0, writeData);
        }

        void SetRdReg(byte readRdRegNum, UInt16 writeData)
        {
            if (!serialPort1.IsOpen) return;

            int i = 0;
            byte[] txBuf = new byte[100];

            txBuf[i++] = (byte)PACKET_START_SYMBOL;
            txBuf[i++] = (byte)DeviceID;                  // ID
            txBuf[i++] = (byte)CMD_WRITE_READ_REGS;   // cmd
            txBuf[i++] = (byte)readRdRegNum;        // regAddr
            txBuf[i++] = (byte)2;                   // countReadWriteData(ignored)
            txBuf[i++] = (byte)((writeData >> 8) & 0xFF); // msb data
            txBuf[i++] = (byte)(writeData & 0xFF);      // lsb data
            txBuf[i++] = (byte)PACKET_END_SYMBOL;

            serialPort1.Write(txBuf, 0, i);
        }





    }
}
