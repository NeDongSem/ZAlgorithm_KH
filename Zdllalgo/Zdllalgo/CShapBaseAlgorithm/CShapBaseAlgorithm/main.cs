using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CShapBaseAlgorithm
{
    class main
    {
        public static int Main()
        {
            GetGoogleSheetGraphInfo GetGoogleSheetGraphInfo = new GetGoogleSheetGraphInfo("Graph1", "C12",1,9);

            DijkstraDLL DijkstraDLL = new DijkstraDLL();
            DijkstraDLL.SetDijkstra(GetGoogleSheetGraphInfo.GraphInfoArryPtr, GetGoogleSheetGraphInfo.GraphInfoArry.Length, GetGoogleSheetGraphInfo.StartNode, GetGoogleSheetGraphInfo.EndNode);

            GetGoogleSheetGraphInfo GetGoogleSheetGraphInfo2 = new GetGoogleSheetGraphInfo("Graph2", "C27", 1, 10);
            DijkstraDLL.SetDijkstra(GetGoogleSheetGraphInfo2.GraphInfoArryPtr, GetGoogleSheetGraphInfo2.GraphInfoArry.Length, GetGoogleSheetGraphInfo2.StartNode, GetGoogleSheetGraphInfo2.EndNode);

            BFSDLL BFSDLL = new BFSDLL();
            BFSDLL.SetBFS(GetGoogleSheetGraphInfo2.GraphInfoArryPtr, GetGoogleSheetGraphInfo2.GraphInfoArry.Length, GetGoogleSheetGraphInfo2.StartNode);
            
            DFSDLL DFSDLL = new DFSDLL();
            DFSDLL.SetDFS(GetGoogleSheetGraphInfo2.GraphInfoArryPtr, GetGoogleSheetGraphInfo2.GraphInfoArry.Length, GetGoogleSheetGraphInfo2.StartNode);

            KruskalDll KruskalDll = new KruskalDll();
            KruskalDll.SetKruskal(GetGoogleSheetGraphInfo2.GraphInfoArryPtr, GetGoogleSheetGraphInfo2.GraphInfoArry.Length);


            GetGoogleSheetBoxPos2D GetGoogleSheetGraphInfo3 = new GetGoogleSheetBoxPos2D("BoxPos2D", "D5");
            AABBDLL AABBDLL = new AABBDLL();
            AABBDLL.SetAABB(GetGoogleSheetGraphInfo3.BoxPos2DArry[0], GetGoogleSheetGraphInfo3.BoxPos2DArry[1]);
            AABBDLL.SetAABB(GetGoogleSheetGraphInfo3.BoxPos2DArryPtr,1,2);
            AABBDLL.SetAABB_Overlap(GetGoogleSheetGraphInfo3.BoxPos2DArry[2], GetGoogleSheetGraphInfo3.BoxPos2DArry[3]);

            return 0;
        }
    }
}
