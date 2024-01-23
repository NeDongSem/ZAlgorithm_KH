using System;
using System.Collections.Generic;
//GoogleAPIs
using System.Runtime.InteropServices;

namespace CShapBaseAlgorithm
{
    public struct GraphInfo
    {
        public int iNode;
        public int iNearNode;
        public int iDistance;
    }

    class GetGoogleSheetGraphInfo : GetGoogleSheet
    {
        int m_iStartNode = 1;
        public int StartNode
        {
            get { return m_iStartNode; }
            set { m_iStartNode = value; }
        }
        int m_iEndNode = 10;
        public int EndNode
        {
            get { return m_iEndNode; }
            set { m_iEndNode = value; }
        }

        GraphInfo[] m_GraphInfoArry;
        public GraphInfo[] GraphInfoArry
        {
            get { return m_GraphInfoArry; }
        }

        IntPtr m_GraphInfoArryPtr;
        public IntPtr GraphInfoArryPtr
        {
            get { return m_GraphInfoArryPtr; }
        }

        //C# 초기화 리스트 - 내부 함수를 구현할 수 없어서 주석 처리 -> 외부에서 Init을 불러줘야 하는 귀찮음이 있음.
        //public GetGoogleSheetGraphInfo(string _strSheetName, int _iLastColumnNum, int _iStartNode, int _iEndNode)
        //    => (this.m_strSheetName, this.m_iLastColumnNum, this.m_iStartNode, this.m_iEndNode)
        //    = (_strSheetName, _iLastColumnNum, _iStartNode, _iEndNode);

        public GetGoogleSheetGraphInfo(string _strSheetName, string _strLastColumn, int _iStartNode, int _iEndNode)
        {
            Init(_strSheetName, _strLastColumn, _iStartNode, _iEndNode);
        }

        ~GetGoogleSheetGraphInfo()
        {
            Marshal.FreeHGlobal(m_GraphInfoArryPtr);
        }

        public void Init(string _strSheetName, string _strLastColumn, int _iStartNode, int _iEndNode)
        {
            m_strSheetName = _strSheetName;
            m_strLastColumn = _strLastColumn;
            m_iStartNode = _iStartNode;
            m_iEndNode = _iEndNode;

            Init();

            SettingGraphInfoArry();
            SettingGraphInfoArryPtr();
        }

        public void SettingGraphInfoArry()
        {
            IList<IList<object>> GraphInfoValuesList = GetGoogleSheetValue();
            int iNodeInfoCount = GraphInfoValuesList.Count - 1;

            m_GraphInfoArry = new GraphInfo[iNodeInfoCount];
            int iIndexTemp = 0;
            bool bTypeName = true;
            if (GraphInfoValuesList != null && iNodeInfoCount > 0)
            {
                foreach (var row in GraphInfoValuesList)
                {
                    if (bTypeName)
                    {
                        bTypeName = false;
                        continue;
                    }
                    GraphInfo graphInfo = new GraphInfo();
                    graphInfo.iNode = int.Parse((string)row[0]);
                    graphInfo.iNearNode = int.Parse((string)row[1]);
                    graphInfo.iDistance = int.Parse((string)row[2]);
                    m_GraphInfoArry[iIndexTemp++] = graphInfo;
                }
            }
        }

        public void SettingGraphInfoArryPtr()
        {
            m_GraphInfoArryPtr = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(GraphInfo)) * m_GraphInfoArry.Length);
            for (int i = 0; i < m_GraphInfoArry.Length; i++)
            {
                IntPtr ptr = new IntPtr(m_GraphInfoArryPtr.ToInt64() + i * Marshal.SizeOf(typeof(GraphInfo)));
                Marshal.StructureToPtr(m_GraphInfoArry[i], ptr, false);
            }

            byte[] byteArray = new byte[Marshal.SizeOf(typeof(GraphInfo)) * m_GraphInfoArry.Length];
            Marshal.Copy(m_GraphInfoArryPtr, byteArray, 0, byteArray.Length);
        }
    }
}
