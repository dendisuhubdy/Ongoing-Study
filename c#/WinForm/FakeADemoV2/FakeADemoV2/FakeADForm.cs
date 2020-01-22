namespace FakeADemoV2
{
    using System.Diagnostics;
    using System.Drawing;
    using System.Threading;
    using System.Windows.Forms;

    using FakeAD;

    public partial class FakeADForm : Form
    {
        private Bitmap canvas_;
        private Thread thread_;
        private bool isRunning_;

        public FakeADForm()
        {
            InitializeComponent();
        }

        private void StartAD()
        {
            Debug.Assert(thread_ == null);

            isRunning_ = true;

            thread_ = new Thread(ADRoutine);
            thread_.IsBackground = false;
            thread_.Start();
        }

        private void StopAD()
        {
            Debug.Assert(thread_ != null);

            isRunning_ = false;
            thread_.Join();
            thread_ = null;
        }

        private void ADRoutine()
        {
            using (var ad = new FakeADViaProducerConsumerDataFlow())
            {
                if (!ad.Open(64))
                    return;

                var data = new double[64];

                while (isRunning_)
                {
                    ad.Read(data, 0, data.Length);
                }
            }
        }

        private void FakeADForm_Layout(object sender, LayoutEventArgs e)
        {
            canvas_ = new Bitmap(ClientRectangle.Width, ClientRectangle.Height);
        }

        private void startStopToolStripButton_Click(object sender, System.EventArgs e)
        {
            if (isRunning_)
            {
                StopAD();
                startStopToolStripButton.Text = "Start";
                startStopToolStripButton.ToolTipText = "Start";
            }
            else
            {
                StartAD();
                startStopToolStripButton.Text = "Stop";
                startStopToolStripButton.ToolTipText = "Stop";
            }
        }
    }
}
