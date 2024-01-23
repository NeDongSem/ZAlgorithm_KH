using System;
using System.Runtime.InteropServices;

namespace CShapBaseAlgorithm
{
    class BFSDLL
    {
        [DllImport("AlgorithmDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr BFS(IntPtr _ptr, int _iArrCount, ref int _iOutArrCount, int _iStartNode);

        [DllImport("AlgorithmDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void FreeIntArryPtr(IntPtr _ptr);

        public void SetBFS(IntPtr _GraphInfoArryPtr, int _iGraphInfoArryLength, int _iStartNode)
        {
            int iOutArryCount = 0;
            IntPtr OutPtr = BFS(_GraphInfoArryPtr, _iGraphInfoArryLength, ref iOutArryCount, _iStartNode);

            int[] OutGraphInfoArry = new int[iOutArryCount];
            for (int i = 0; i < iOutArryCount; i++)
            {
                IntPtr elementPtr = new IntPtr(OutPtr.ToInt64() + Marshal.SizeOf(typeof(int)) * i);
                OutGraphInfoArry[i] = (int)Marshal.PtrToStructure(elementPtr, typeof(int));
            }

            FreeIntArryPtr(OutPtr);

            Console.WriteLine("BFS " + _iStartNode + "번 노드와 가까운 순서대로 출력 결과");
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
