using System;
using System.Runtime.InteropServices;

namespace CShapBaseAlgorithm
{
    class AABBDLL
    {
        [DllImport("AlgorithmDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool AABB(BoxPos2D _ABoxPos2D, BoxPos2D _BBoxPos2D);

        [DllImport("AlgorithmDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool AABB_ArryPtr(IntPtr _BoxPos2DArryPtr, int _iBox1Index, int _iBox2Index);

        [DllImport("AlgorithmDLL.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.U1)]
        public static extern bool AABB_Overlap(BoxPos2D _ABoxPos2D, BoxPos2D _BBoxPos2D);
        
        public bool SetAABB(BoxPos2D _ABoxPos2D, BoxPos2D _BBoxPos2D)
        {
            bool bCol = AABB(_ABoxPos2D, _BBoxPos2D);

            if (bCol)
            {
                Console.WriteLine("두 객체는 AABB 충돌 검사시 충돌 한 것으로 판정되었습니다.");
                Console.WriteLine("AABB 충돌 검사는 정확한 충돌 검사가 아니므로");
                Console.WriteLine("추가적인 충돌검사를 해보시는 걸 추천드립니다.");
                Console.WriteLine("아무 버튼이나 누르시면 종료됩니다.");
                Console.WriteLine(" ");
                Console.ReadKey();
            }
            else
            {
                Console.WriteLine("두 객체는 충돌하지 않았습니다.");
                Console.WriteLine("아무 버튼이나 누르시면 종료됩니다.");
                Console.WriteLine(" ");
                Console.ReadKey();
            }

            return bCol;
        }

        public bool SetAABB(IntPtr _BoxPos2DArryPtr, int _iBox1Index, int _iBox2Index)
        {
            bool bCol = AABB_ArryPtr(_BoxPos2DArryPtr, _iBox1Index, _iBox2Index);

            if (bCol)
            {
                Console.WriteLine(_iBox1Index + "번 객체와 " + _iBox2Index + "번 객체는 AABB 충돌 검사시 충돌 한 것으로 판정되었습니다.");
                Console.WriteLine("AABB 충돌 검사는 정확한 충돌 검사가 아니므로");
                Console.WriteLine("추가적인 충돌검사를 해보시는 걸 추천드립니다.");
                Console.WriteLine("아무 버튼이나 누르시면 종료됩니다.");
                Console.WriteLine(" ");
                Console.ReadKey();
            }
            else
            {
                Console.WriteLine("두 객체는 충돌하지 않았습니다.");
                Console.WriteLine("아무 버튼이나 누르시면 종료됩니다.");
                Console.WriteLine(" ");
                Console.ReadKey();
            }

            return bCol;
        }

        public bool SetAABB_Overlap(BoxPos2D _ABoxPos2D, BoxPos2D _BBoxPos2D)
        {
            bool bCol = AABB_Overlap(_ABoxPos2D, _BBoxPos2D);

            if (bCol)
            {
                Console.WriteLine("두 객체는 AABB 충돌 검사시 충돌 한 것으로 판정되었습니다.");
                Console.WriteLine("AABB 충돌 검사는 정확한 충돌 검사가 아니므로");
                Console.WriteLine("추가적인 충돌검사를 해보시는 걸 추천드립니다.");
                Console.WriteLine("아무 버튼이나 누르시면 종료됩니다.");
                Console.WriteLine(" ");
                Console.ReadKey();
            }
            else
            {
                Console.WriteLine("두 객체는 충돌하지 않았습니다.");
                Console.WriteLine("아무 버튼이나 누르시면 종료됩니다.");
                Console.WriteLine(" ");
                Console.ReadKey();
            }

            return bCol;
        }
    }
}
