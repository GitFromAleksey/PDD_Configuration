namespace PrinterConfig
{
    partial class Form1
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.textBoxLog = new System.Windows.Forms.TextBox();
            this.comboBoxPorts = new System.Windows.Forms.ComboBox();
            this.button1 = new System.Windows.Forms.Button();
            this.textBoxID = new System.Windows.Forms.TextBox();
            this.buttonGetReadReg = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.textBoxRdRegNum = new System.Windows.Forms.TextBox();
            this.buttonGetRdWrReg = new System.Windows.Forms.Button();
            this.textBoxRdRegVal = new System.Windows.Forms.TextBox();
            this.textBoxRdWrRegVal = new System.Windows.Forms.TextBox();
            this.buttonSetRdWrReg = new System.Windows.Forms.Button();
            this.textBoxWriteData = new System.Windows.Forms.TextBox();
            this.textBoxRdWrRegNum = new System.Windows.Forms.TextBox();
            this.textBoxWrRegNum = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // textBoxLog
            // 
            this.textBoxLog.Location = new System.Drawing.Point(12, 176);
            this.textBoxLog.Multiline = true;
            this.textBoxLog.Name = "textBoxLog";
            this.textBoxLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBoxLog.Size = new System.Drawing.Size(453, 127);
            this.textBoxLog.TabIndex = 0;
            // 
            // comboBoxPorts
            // 
            this.comboBoxPorts.FormattingEnabled = true;
            this.comboBoxPorts.Location = new System.Drawing.Point(12, 12);
            this.comboBoxPorts.Name = "comboBoxPorts";
            this.comboBoxPorts.Size = new System.Drawing.Size(121, 21);
            this.comboBoxPorts.TabIndex = 1;
            this.comboBoxPorts.DropDown += new System.EventHandler(this.comboBox1_DropDown);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(139, 12);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 2;
            this.button1.Text = "Open Port";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // textBoxID
            // 
            this.textBoxID.Location = new System.Drawing.Point(220, 14);
            this.textBoxID.Name = "textBoxID";
            this.textBoxID.Size = new System.Drawing.Size(42, 20);
            this.textBoxID.TabIndex = 3;
            this.textBoxID.Text = "11";
            // 
            // buttonGetReadReg
            // 
            this.buttonGetReadReg.Location = new System.Drawing.Point(108, 44);
            this.buttonGetReadReg.Name = "buttonGetReadReg";
            this.buttonGetReadReg.Size = new System.Drawing.Size(84, 23);
            this.buttonGetReadReg.TabIndex = 4;
            this.buttonGetReadReg.Text = "GetRdReg";
            this.buttonGetReadReg.UseVisualStyleBackColor = true;
            this.buttonGetReadReg.Click += new System.EventHandler(this.button2_Click);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // textBoxRdRegNum
            // 
            this.textBoxRdRegNum.Location = new System.Drawing.Point(12, 46);
            this.textBoxRdRegNum.Name = "textBoxRdRegNum";
            this.textBoxRdRegNum.Size = new System.Drawing.Size(42, 20);
            this.textBoxRdRegNum.TabIndex = 5;
            this.textBoxRdRegNum.Text = "0";
            // 
            // buttonGetRdWrReg
            // 
            this.buttonGetRdWrReg.Location = new System.Drawing.Point(108, 70);
            this.buttonGetRdWrReg.Name = "buttonGetRdWrReg";
            this.buttonGetRdWrReg.Size = new System.Drawing.Size(84, 23);
            this.buttonGetRdWrReg.TabIndex = 6;
            this.buttonGetRdWrReg.Text = "GetRdWrReg";
            this.buttonGetRdWrReg.UseVisualStyleBackColor = true;
            this.buttonGetRdWrReg.Click += new System.EventHandler(this.buttonGetRdWrReg_Click);
            // 
            // textBoxRdRegVal
            // 
            this.textBoxRdRegVal.Location = new System.Drawing.Point(198, 46);
            this.textBoxRdRegVal.Name = "textBoxRdRegVal";
            this.textBoxRdRegVal.Size = new System.Drawing.Size(42, 20);
            this.textBoxRdRegVal.TabIndex = 7;
            // 
            // textBoxRdWrRegVal
            // 
            this.textBoxRdWrRegVal.Location = new System.Drawing.Point(198, 72);
            this.textBoxRdWrRegVal.Name = "textBoxRdWrRegVal";
            this.textBoxRdWrRegVal.Size = new System.Drawing.Size(42, 20);
            this.textBoxRdWrRegVal.TabIndex = 8;
            // 
            // buttonSetRdWrReg
            // 
            this.buttonSetRdWrReg.Location = new System.Drawing.Point(108, 96);
            this.buttonSetRdWrReg.Name = "buttonSetRdWrReg";
            this.buttonSetRdWrReg.Size = new System.Drawing.Size(84, 23);
            this.buttonSetRdWrReg.TabIndex = 9;
            this.buttonSetRdWrReg.Text = "SetRdWrReg";
            this.buttonSetRdWrReg.UseVisualStyleBackColor = true;
            this.buttonSetRdWrReg.Click += new System.EventHandler(this.buttonSetRdWrReg_Click);
            // 
            // textBoxWriteData
            // 
            this.textBoxWriteData.Location = new System.Drawing.Point(60, 98);
            this.textBoxWriteData.Name = "textBoxWriteData";
            this.textBoxWriteData.Size = new System.Drawing.Size(42, 20);
            this.textBoxWriteData.TabIndex = 10;
            this.textBoxWriteData.Text = "22";
            // 
            // textBoxRdWrRegNum
            // 
            this.textBoxRdWrRegNum.Location = new System.Drawing.Point(12, 72);
            this.textBoxRdWrRegNum.Name = "textBoxRdWrRegNum";
            this.textBoxRdWrRegNum.Size = new System.Drawing.Size(42, 20);
            this.textBoxRdWrRegNum.TabIndex = 11;
            this.textBoxRdWrRegNum.Text = "0";
            // 
            // textBoxWrRegNum
            // 
            this.textBoxWrRegNum.Location = new System.Drawing.Point(12, 98);
            this.textBoxWrRegNum.Name = "textBoxWrRegNum";
            this.textBoxWrRegNum.Size = new System.Drawing.Size(42, 20);
            this.textBoxWrRegNum.TabIndex = 12;
            this.textBoxWrRegNum.Text = "0";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(477, 328);
            this.Controls.Add(this.textBoxWrRegNum);
            this.Controls.Add(this.textBoxRdWrRegNum);
            this.Controls.Add(this.textBoxWriteData);
            this.Controls.Add(this.buttonSetRdWrReg);
            this.Controls.Add(this.textBoxRdWrRegVal);
            this.Controls.Add(this.textBoxRdRegVal);
            this.Controls.Add(this.buttonGetRdWrReg);
            this.Controls.Add(this.textBoxRdRegNum);
            this.Controls.Add(this.buttonGetReadReg);
            this.Controls.Add(this.textBoxID);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.comboBoxPorts);
            this.Controls.Add(this.textBoxLog);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.TextBox textBoxLog;
        private System.Windows.Forms.ComboBox comboBoxPorts;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox textBoxID;
        private System.Windows.Forms.Button buttonGetReadReg;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.TextBox textBoxRdRegNum;
        private System.Windows.Forms.Button buttonGetRdWrReg;
        private System.Windows.Forms.TextBox textBoxRdRegVal;
        private System.Windows.Forms.TextBox textBoxRdWrRegVal;
        private System.Windows.Forms.Button buttonSetRdWrReg;
        private System.Windows.Forms.TextBox textBoxWriteData;
        private System.Windows.Forms.TextBox textBoxRdWrRegNum;
        private System.Windows.Forms.TextBox textBoxWrRegNum;
    }
}

