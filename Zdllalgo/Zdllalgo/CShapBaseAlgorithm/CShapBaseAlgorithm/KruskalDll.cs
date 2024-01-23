using System;
using System.Runtime.InteropServices;

namespace CShapBaseAlgorithm
{
    class KruskalDll
    {
        [DllImport("AlgorithmDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Kruskal(IntPtr _ptr, int _iArrCount, ref int _iOutArrCount);

        [DllImport("AlgorithmDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void FreeIntArryPtr(IntPtr _ptr);

        public void SetKruskal(IntPtr _GraphInfoArryPtr, int _iGraphInfoArryLength)
        {
            int iOutArryCount = 0;
            IntPtr OutPtr = Kruskal(_GraphInfoArryPtr, _iGraphInfoArryLength, ref iOutArryCount);

            int[] OutGraphInfoArry = new int[iOutArryCount];
            for (int i = 0; i < iOutArryCount; i++)
            {
                IntPtr elementPtr = new IntPtr(OutPtr.ToInt64() + Marshal.SizeOf(typeof(int)) * i);
                OutGraphInfoArry[i] = (int)Marshal.PtrToStructure(elementPtr, typeof(int));
            }

            FreeIntArryPtr(OutPtr);

            Console.WriteLine("Kruskal 최소 신장 트리 구성시 이어진 노드");
            for (int i = 0; i < iOutArryCount; ++i)
            {
                if ((i + 1) == iOutArryCount)
                {
                    Console.WriteLine("구성된 트리의 총 길이는 " + OutGraphInfoArry[i] + "입니다.");
                }
                else
                {
                    Console.Write(OutGraphInfoArry[i] + " - " + OutGraphInfoArry[++i] + " || ");
                }
            }
            Console.WriteLine("아무 버튼이나 누르시면 종료됩니다.");
            Console.WriteLine(" ");
            Console.ReadKey();
        }
    }
}
