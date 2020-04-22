using System;
using System.IO;

namespace Lista6
{
    class l6z1
    {
        static void Main(string[] args)
        {
            Main_z1();
            l6z2.Main_z2();
            l6z3.Main_z3();   
        }

        public static void Main_z1()
        {
            Console.WriteLine("Lista 6, zadanie 1");

            LoggerFactory loggerFactory = LoggerFactory.Instance();
            ILogger noneLogger = loggerFactory.GetLogger(LogType.None);
            ILogger consoleLogger = loggerFactory.GetLogger(LogType.Console);
            ILogger fileLogger = loggerFactory.GetLogger(LogType.File, "C:\\file_folder\\foo.txt");

            noneLogger.Log("message1");
            consoleLogger.Log("message2");
            fileLogger.Log("message3");

            using (StreamReader sr = new StreamReader("C:\\file_folder\\foo.txt"))
            {
                String line = sr.ReadToEnd();
                Console.WriteLine(line);
            }
            Console.ReadLine();
        }
    }

    public interface ILogger
    {
        void Log(string Message);
    }
    public enum LogType { None, Console, File }

    public class NoneLogger : ILogger
    {
        public void Log(string Message){}
    }

    public class ConsoleLogger : ILogger
    {
        public void Log(string Message)
        {
            Console.WriteLine(Message);
        }
    }

    public class FileLogger : ILogger
    {
        private string filePath;
        public FileLogger(string filePath)
        {
            if (filePath == null)
                throw new ArgumentException();
            this.filePath = filePath;
        }
        public void Log(string Message)
        {
            System.IO.File.WriteAllText(filePath, Message);
        }
    }

    public class LoggerFactory
    {
        private static LoggerFactory _instance;

        public ILogger GetLogger(LogType LogType, string Parameters = null)
        {
            switch (LogType)
            {
                case LogType.None:
                    return new NoneLogger();
                case LogType.Console:
                    return new ConsoleLogger();
                case LogType.File:
                    return new FileLogger(Parameters);
                default:
                    throw new ArgumentException();
            }
        }
        public static LoggerFactory Instance() {
            if (_instance != null)
            {
                return _instance;
            }
            _instance = new LoggerFactory();
            return _instance;
        }
    }

}
