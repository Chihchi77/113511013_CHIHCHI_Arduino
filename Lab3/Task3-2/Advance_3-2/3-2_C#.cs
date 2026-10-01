using System;
using System.IO.Ports;
using System.Windows.Forms;

namespace Arduino_Adv_3_2
{
    public partial class Form1 : Form
    {
        private SerialPort serialPort;

        public Form1()
        {
            InitializeComponent();

            // Designer 沒有幫 button2 綁定 Click，
            // 所以在這裡手動綁定
            button2.Click += button2_Click;
        }

        // Form 開啟時執行
        private void Form1_Load(object sender, EventArgs e)
        {
            serialPort = new SerialPort();

            // 改成你的 Arduino 實際 COM Port
            serialPort.PortName = "COM3";

            serialPort.BaudRate = 9600;
            serialPort.DataBits = 8;
            serialPort.Parity = Parity.None;
            serialPort.StopBits = StopBits.One;
            serialPort.NewLine = "\n";

            try
            {
                serialPort.Open();

                MessageBox.Show("Arduino connected.");
            }
            catch (Exception ex)
            {
                MessageBox.Show(
                    "Cannot open serial port.\n\n" +
                    ex.Message
                );
            }
        }

        // =========================
        // ON button
        // button1 = ON
        // =========================
        private void button1_Click(object sender, EventArgs e)
        {
            if (serialPort != null && serialPort.IsOpen)
            {
                serialPort.WriteLine("ON");
            }
            else
            {
                MessageBox.Show("Serial port is not connected.");
            }
        }

        // =========================
        // OFF button
        // button2 = OFF
        // =========================
        private void button2_Click(object sender, EventArgs e)
        {
            if (serialPort != null && serialPort.IsOpen)
            {
                serialPort.WriteLine("OFF");
            }
            else
            {
                MessageBox.Show("Serial port is not connected.");
            }
        }

        // 關閉程式時關閉 COM port
        protected override void OnFormClosing(FormClosingEventArgs e)
        {
            if (serialPort != null && serialPort.IsOpen)
            {
                serialPort.Close();
            }

            base.OnFormClosing(e);
        }
    }
}