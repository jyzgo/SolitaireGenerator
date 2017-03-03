using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace GenerateNewLevel
{
    static class ThreadSafeRandom
    {
        [ThreadStatic]
        private static System.Random Local;

        public static System.Random ThisThreadsRandom
        {
            get { return Local ?? (Local = new System.Random(unchecked(Environment.TickCount * 31 + Thread.CurrentThread.ManagedThreadId))); }
        }
    }

    public static class MTExtension
    {
        public static void RandomShuffle<T>(this IList<T> list)
        {
            int n = list.Count;
            while (n > 1)
            {
                n--;
                int k = ThreadSafeRandom.ThisThreadsRandom.Next(n + 1);
                T value = list[k];
                list[k] = list[n];
                list[n] = value;
            }
        }
    }

    public class newLv
    {
        public newLv()
        {
            for (int i = 0; i < 52; i++)
            {
                _oriList.Add(i);

            }
            Shuffule();

            for(int i  = 0; i  < 28; i++)
            {
                head28 += _oriList[i].ToString();
            }
        }
        public string head28;
        HashSet<string> _set = new HashSet<string>();


        void Shuffule()
        {
            _oriList.RandomShuffle<int>();
        }

        public string ToContent()
        {
            StringBuilder build = new StringBuilder();
            for(int i  = 0; i < _oriList.Count; i ++)
            {
                build.Append(_oriList[i].ToString());

                build.Append("\n");
                
            }
            return build.ToString();
            
        }

        List<int> _oriList = new List<int>();
    }

    class Program
    {
        static void Main(string[] args)
        {
            int count = 0;
            for (int i = 0; i < args.Length; i++)
            {
                var s = args[i];
                if (s == "-num")
                {
                    count = Convert.ToInt32( args[i + 1]);
                }
            }


            ReArrangeFile();

        }


        public static void GenLevel()
        {
            HashSet<string> _s = new HashSet<string>();
            HashSet<string> final = new HashSet<string>();
            for (int i = 0; i < 200000; i++)
            {
                var newLv = new newLv();
                if (_s.Contains(newLv.head28))
                {
                    continue;
                }
                _s.Add(newLv.head28);
                final.Add(newLv.ToContent());
            }



            Console.Write("dd count " + final.Count);

            int c = 0;
            foreach (var s in final)
            {
                c++;
                File.WriteAllText("Sol/original/solitaire" + c + ".txt", s);
            }

        }

        const string arrangePath = "Sol/arrange/";
        public static void ReArrangeFile()
        {
            string[] files =   Directory.GetFiles(arrangePath);
            List<int> _fileIndexList = new List<int>();
            for(int i  = 0; i < files.Length; i ++)
            {
                var fileName = files[i];
                var m = fileName.Remove(0, 21);
                var d = Path.GetFileNameWithoutExtension(m);
                _fileIndexList.Add(Convert.ToInt32(d)); 
                Console.WriteLine("aa "  + d);
            }

            _fileIndexList.Sort();
            for(int i  = 0; i < _fileIndexList.Count; i ++)
            {
                int curIndex = _fileIndexList[i];
                File.Move(arrangePath + "solitaire" + curIndex + ".txt", arrangePath + (i + 1) + ".txt");
                Console.WriteLine(_fileIndexList[i]);
            }
        }
        

   



    }





}
