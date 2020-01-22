namespace FakeAD
{
    using System;
    using System.Diagnostics;
    using System.Linq;
    using System.Threading;
    using System.Threading.Tasks.Dataflow;

    public class FakeADViaProducerConsumerDataFlow : FakeADBase
    {
        public override bool IsOpened => thread_ != null && thread_.IsAlive;

        public override bool Open(int samples)
        {
            Debug.Assert(thread_ == null);

            if (samples <= 0)
                throw new ArgumentException("Invalid samples.");

            samples_ = samples;
            isRunning_ = true;
            dataBuffer_ = new BufferBlock<double[]>();

            thread_ = new Thread(FakeADRoutine);
            thread_.IsBackground = false;
            thread_.Start();

            return true;
        }

        public override int Read(double[] buffer, int offset, int count)
        {
            if (!IsOpened)
                throw new InvalidOperationException("AD is not opened yet!");

            if (buffer == null)
                throw new ArgumentNullException("buffer");

            if (offset < 0 || offset >= buffer.Length)
                throw new ArgumentException("offset");

            if (count <= 0 || offset + count > buffer.Length)
                throw new ArgumentException("count");

            if (count % (samples_ * Channels) != 0)
                throw new ArgumentException("count");

            int expectedDataCount = count;

            while (expectedDataCount > 0)
            {
                var data = dataBuffer_.Receive();
                Array.Copy(data, 0, buffer, offset, data.Length);

                expectedDataCount -= data.Length;
                offset += data.Length;
            }

            return count;
        }

        public override void Release()
        {
            if (!IsOpened)
                throw new InvalidOperationException("AD is not opened yet!");

            isRunning_ = false;

            dataBuffer_.Complete();

            thread_.Join();
            thread_ = null;

            dataBuffer_ = null;
        }

        private void FakeADRoutine()
        {
            int dataLength = samples_ * Channels;
            var dataGenerators = new SinusWaveDataGenerator[Channels];
            for (int i = 0; i < dataGenerators.Length; ++i)
                dataGenerators[i] = new SinusWaveDataGenerator(0.5, SamplingRate);

            while (isRunning_)
            {
                var data = Enumerable
                    .Range(0, dataLength)
                    .Select(n => dataGenerators[n % Channels].Next())
                    .ToArray();
                dataBuffer_.Post(data);
            }
        }

        private Thread thread_;
        private bool isRunning_;
        private int samples_;
        private BufferBlock<double[]> dataBuffer_;
    }
}


// References:
// https://docs.microsoft.com/en-us/dotnet/standard/parallel-programming/how-to-implement-a-producer-consumer-dataflow-pattern
// https://docs.microsoft.com/en-us/dotnet/standard/parallel-programming/dataflow-task-parallel-library
// https://docs.microsoft.com/en-us/dotnet/standard/parallel-programming/walkthrough-using-dataflow-in-a-windows-forms-application
// https://stackoverflow.com/questions/1287461/fill-listint-using-linq
