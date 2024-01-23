using System;
using System.Runtime.InteropServices;

namespace CShapBaseAlgorithm
{
    class DijkstraDLL
    {
        [DllImport("AlgorithmDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Dijkstra(IntPtr _ptr, int _iArrCount, ref int _iOutArrCount, int _iStartNode, int _iEndNode);

        [DllImport("AlgorithmDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void FreeGraphInfoArryPtr(IntPtr _ptr);

        public void SetDijkstra(IntPtr _GraphInfoArryPtr, int _iGraphInfoArryLength, int _iStartNode, int _iEndNode)
        {
            int iOutArryCount = 0;
            IntPtr OutPtr = Dijkstra(_GraphInfoArryPtr, _iGraphInfoArryLength, ref iOutArryCount, _iStartNode, _iEndNode);

            GraphInfo[] OutGraphInfoArry = new GraphInfo[iOutArryCount];
            for (int i = 0; i < iOutArryCount; i++)
            {
                IntPtr elementPtr = new IntPtr(OutPtr.ToInt64() + Marshal.SizeOf(typeof(GraphInfo)) * i);
                OutGraphInfoArry[i] = (GraphInfo)Marshal.PtrToStructure(elementPtr, typeof(GraphInfo));
            }

            FreeGraphInfoArryPtr(OutPtr);

            Console.WriteLine("다익스트라 길찾기 결과");
            for (int i = 0; i < iOutArryCount; ++i)
            {
                Console.Write(OutGraphInfoArry[i].iNode + " -> ");
            }
            Console.WriteLine(_iEndNode);
            Console.WriteLine("아무 버튼이나 누르시면 종료됩니다.");
            Console.WriteLine(" ");
            Console.ReadKey();
        }
    }
}
