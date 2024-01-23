using System;
using System.IO;
using System.Collections.Generic;
//GoogleAPIs
using Google.Apis.Auth.OAuth2;
using Google.Apis.Sheets.v4;
using Google.Apis.Sheets.v4.Data;
using Google.Apis.Services;
using System.Runtime.InteropServices;

namespace CShapBaseAlgorithm
{
    class GetGoogleSheet
    {
        protected SheetsService m_GoogleSheetsService;
        protected string m_strJsonPath = "../../../Key.json";
        protected string m_strApplicationName = "GraphInfo";
        protected string m_strSheetId = "1Xob06tQoNfHWl434moOkg61i2by-W89nDxt9K8f0puc";
        protected string m_strSheetRange = "!A1:";

        protected string m_strSheetName = "";
        public string SheetName
        {
            get { return m_strSheetName; }
            set { m_strSheetName = value; }
        }
        protected string m_strLastColumn = "";
        public string LastColumn
        {
            get { return m_strLastColumn; }
            set { m_strLastColumn = value; }
        }

        public GetGoogleSheet()
        {
            Init();
        }

        public GetGoogleSheet(string _strSheetName, string _strLastColumn)
        {
            Init(_strSheetName, _strLastColumn);
        }

        ~GetGoogleSheet()
        {
        }

        public virtual void Init()
        {
            GoogleCredential credential;

            ReadJsonFile(out credential);

            if (credential != null)
            {
                m_GoogleSheetsService = CreateGoogleSheetsAPIService(credential);
            }
        }

        public virtual void Init(string _strSheetName, string _strLastColumn)
        {
            m_strSheetName = _strSheetName;
            m_strLastColumn = _strLastColumn;

            GoogleCredential credential;

            ReadJsonFile(out credential);

            if (credential != null)
            {
                m_GoogleSheetsService = CreateGoogleSheetsAPIService(credential);
            }
        }

        protected virtual void ReadJsonFile(out GoogleCredential _credential)
        {
            using (FileStream stream = new FileStream(m_strJsonPath, FileMode.Open, FileAccess.Read))
            {
                _credential = GoogleCredential.FromStream(stream).CreateScoped(SheetsService.Scope.SpreadsheetsReadonly);
            }
        }

        protected virtual SheetsService CreateGoogleSheetsAPIService(GoogleCredential _credential)
        {
            SheetsService service = new SheetsService(new BaseClientService.Initializer()
            {
                HttpClientInitializer = _credential,
                ApplicationName = m_strApplicationName,
            });

            return service;
        }

        public virtual IList<IList<object>> GetGoogleSheetValue()
        {
            SpreadsheetsResource.ValuesResource.GetRequest request = 
                m_GoogleSheetsService.Spreadsheets.Values.Get(m_strSheetId, 
                m_strSheetName + m_strSheetRange + m_strLastColumn);

            ValueRange response = request.Execute();
            return response.Values;
        }
    }
}
