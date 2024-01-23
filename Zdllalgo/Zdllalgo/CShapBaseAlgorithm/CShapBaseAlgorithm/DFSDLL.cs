using System;
using System.Runtime.InteropServices;

namespace CShapBaseAlgorithm
{
    class DFSDLL
    {
        [DllImport("AlgorithmDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr DFS(IntPtr _ptr, int _iArrCount, ref int _iOutArrCount, int _iStartNode);

        [DllImport("AlgorithmDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void FreeIntArryPtr(IntPtr _ptr);

        public void SetDFS(IntPtr _GraphInfoArryPtr, int _iGraphInfoArryLength, int _iStartNode)
        {
            int iOutArryCount = 0;
            IntPtr OutPtr = DFS(_GraphInfoArryPtr, _iGraphInfoArryLength, ref iOutArryCount, _iStartNode);

            int[] OutGraphInfoArry = new int[iOutArryCount];
            for (int i = 0; i < iOutArryCount; i++)
            {
                IntPtr elementPtr = new IntPtr(OutPtr.ToInt64() + Marshal.SizeOf(typeof(int)) * i);
                OutGraphInfoArry[i] = (int)Marshal.PtrToStructure(elementPtr, typeof(int));
            }

            FreeIntArryPtr(OutPtr);

            Console.WriteLine("DFS " + _iStartNode + "번 노드부터 DFS탐색시, 조우한 순서대로 노드 출력");
            for (int i = 0; i < iOutArryCount; ++i)
            {
                if ((i + 1) == iOutArryCount)
                {
                    Console.WriteLine(OutGraphInfoArry[i]);
                }
                else
                {
                    Console.Write(OutGraphInfoArry[i] + " -> ");
                }
            }
            Console.WriteLine("아무 버튼이나 누르시면 종료됩니다.");
            Console.WriteLine(" ");
            Console.ReadKey();
        }
    }
}
