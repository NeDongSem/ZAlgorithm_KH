using System;
using System.Collections.Generic;
//GoogleAPIs
using System.Runtime.InteropServices;

namespace CShapBaseAlgorithm
{
    public struct BoxPos2D
    {
        public float fLeft;
        public float fRight;
        public float fTop;
        public float fBottom;
    }

    class GetGoogleSheetBoxPos2D : GetGoogleSheet
    {
        BoxPos2D[] m_BoxPos2DArry;
        public BoxPos2D[] BoxPos2DArry
        {
            get { return m_BoxPos2DArry; }
        }

        IntPtr m_BoxPos2DArryPtr;
        public IntPtr BoxPos2DArryPtr
        {
            get { return m_BoxPos2DArryPtr; }
        }

        public GetGoogleSheetBoxPos2D(string _strSheetName, string _strLastColumn)
        {
            Init(_strSheetName, _strLastColumn);
        }

        ~GetGoogleSheetBoxPos2D()
        {
            Marshal.FreeHGlobal(m_BoxPos2DArryPtr);
        }

        public override void Init(string _strSheetName, string _strLastColumn)
        {
            m_strSheetName = _strSheetName;
            m_strLastColumn = _strLastColumn;

            base.Init();

            SettingBoxPos2DArry();
            SettingBoxPos2DArryPtr();
        }

        public void SettingBoxPos2DArry()
        {
            IList<IList<object>> BoxPos2DValuesList = GetGoogleSheetValue();
            int iBoxPos2DCount = BoxPos2DValuesList.Count - 1;

            m_BoxPos2DArry = new BoxPos2D[iBoxPos2DCount];
            int iIndexTemp = 0;
            bool bTypeName = true;
            if (BoxPos2DValuesList != null && iBoxPos2DCount > 0)
            {
                foreach (var row in BoxPos2DValuesList)
                {
                    if (bTypeName)
                    {
                        bTypeName = false;
                        continue;
                    }
                    BoxPos2D boxPos2D = new BoxPos2D();

                    boxPos2D.fLeft = float.Parse((string)row[0]);
                    boxPos2D.fRight = float.Parse((string)row[1]);
                    boxPos2D.fTop = float.Parse((string)row[2]);
                    boxPos2D.fBottom = float.Parse((string)row[3]);

                    m_BoxPos2DArry[iIndexTemp++] = boxPos2D;
                }
            }
        }

        public void SettingBoxPos2DArryPtr()
        {
            m_BoxPos2DArryPtr = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(BoxPos2D)) * m_BoxPos2DArry.Length);
            for (int i = 0; i < m_BoxPos2DArry.Length; i++)
            {
                IntPtr ptr = new IntPtr(m_BoxPos2DArryPtr.ToInt64() + i * Marshal.SizeOf(typeof(BoxPos2D)));
                Marshal.StructureToPtr(m_BoxPos2DArry[i], ptr, false);
            }

            byte[] byteArray = new byte[Marshal.SizeOf(typeof(BoxPos2D)) * m_BoxPos2DArry.Length];
            Marshal.Copy(m_BoxPos2DArryPtr, byteArray, 0, byteArray.Length);
        }
    }
}
 