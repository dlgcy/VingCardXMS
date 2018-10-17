// VingCardXMS.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "VingCardXMS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

#define  CMD_REGISTER		1
#define  CMD_UNREGISTER		2
#define  CMD_ENCODERMT	    4
#define  CMD_RETURNKCD		5

#define	 TCP_SOCKET_PORT	3015

/////////////////////////////////////////////////////////////////////////////
// CVingCardXMSApp

BEGIN_MESSAGE_MAP(CVingCardXMSApp, CWinApp)
	//{{AFX_MSG_MAP(CVingCardXMSApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVingCardXMSApp construction

CVingCardXMSApp::CVingCardXMSApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	m_strAppl = _T("test");
	m_strChRoom = _T("201");
	m_strChUT = _T("Single Room");
	m_strCmd = _T("I");
	m_strEnd = _T("");
	m_strChFName = _T("Teddy");
	m_strChLName = _T("");
	m_strFName = _T("Ted");
	m_strLic = _T("42987413");
	m_strLName = _T("Jones");
	m_strMain = _T("12");
	m_iRegRes = 9;
	m_strRoom = _T("201");
	m_strStart = _T("");
	m_strSysFName = _T("Jason");
	m_strSysID = _T("7289");
	m_strSysLName = _T("Phillips");
	m_strUG = _T("GUEST");
	m_strUT = _T("GUEST");
	m_iUnRegRes = 9;
	m_strResult = _T("-1");
	m_strIP = _T("00.00.00.00");
	m_strEncoder = _T("");
	m_cardtype = _T("new");
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVingCardXMSApp object

CVingCardXMSApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CVingCardXMSApp initialization

BOOL CVingCardXMSApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}
	m_mySocket.Create(NULL, SOCK_STREAM, NULL);
	m_Connected = FALSE;

	return TRUE;
}

/************************************************************************/
/*  注册                                                              */
/************************************************************************/
void CVingCardXMSApp::OnbtnReg() 
{
	SPMSifRegisterMsg *m_RegMsg;
	BYTE *pbytesSend;
	BYTE *pbytesReceive;
	
	m_RegMsg = new SPMSifRegisterMsg;

	strcpy(m_RegMsg->szLicense, m_strLic);		//Build the data
	strcpy(m_RegMsg->szApplName, m_strAppl);
	m_RegMsg->nRet=0;
	SetHeader(&m_RegMsg->hdr1, CMD_REGISTER);
		
	pbytesSend = new BYTE[sizeof(SPMSifRegisterMsg)];
	memcpy(pbytesSend, m_RegMsg, sizeof(SPMSifRegisterMsg));     //copy m_RegMsg structure to pbytesStore

	pbytesReceive=TCPSend(pbytesSend, sizeof(SPMSifRegisterMsg));		  //sends pbytesStore and receives the response

	m_RegMsg=(SPMSifRegisterMsg*)pbytesReceive;						//copy response back to structure
	m_iRegRes=m_RegMsg->nRet;
}

/************************************************************************/
/* 反注册                                                                     */
/************************************************************************/
void CVingCardXMSApp::OnbtnUnReg() 
{
	SPMSifUnregisterMsg *m_UnregMsg;
	BYTE *pbytesSend;
	BYTE *pbytesReceive;
	
	m_UnregMsg = new SPMSifUnregisterMsg;

	m_UnregMsg->nRet=0;
	SetHeader(&m_UnregMsg->hdr1, CMD_UNREGISTER);
	
	pbytesSend = new BYTE[sizeof(SPMSifUnregisterMsg)];
	memcpy(pbytesSend, m_UnregMsg, sizeof(SPMSifUnregisterMsg));     //copy structure to pbytesStore

	pbytesReceive=TCPSend(pbytesSend, sizeof(SPMSifUnregisterMsg));         //sends pbytesStore

	m_UnregMsg=(SPMSifUnregisterMsg*)pbytesReceive;						//copy response back to structure
	m_iUnRegRes=m_UnregMsg->nRet;
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
void CVingCardXMSApp::OnbtnGetBitmap() 
{
	SPMSifReturnKcdLclMsg *m_RetKcdMsg;
	BYTE *pbytesSend;
	BYTE *pbytesReceive;
	
	m_RetKcdMsg = new SPMSifReturnKcdLclMsg;

	m_RetKcdMsg->ff ='E';// m_strCmd[0];                       //build the structure
	BuildData(m_RetKcdMsg->ff, &m_RetKcdMsg->Dta[0]);    // get data
	m_RetKcdMsg->Debug=FALSE;
	strcpy(m_RetKcdMsg->szOpId, m_strSysID);
	strcpy(m_RetKcdMsg->szOpFirst, m_strSysFName);
	strcpy(m_RetKcdMsg->szOpLast, m_strSysLName);
	SetHeader(&m_RetKcdMsg->hdr1, CMD_RETURNKCD);

	pbytesSend = new BYTE[sizeof(SPMSifReturnKcdLclMsg)];
	memcpy(pbytesSend, m_RetKcdMsg, sizeof(SPMSifReturnKcdLclMsg));	  //copy structure to pbytesStore

	pbytesReceive=TCPSend(pbytesSend, sizeof(SPMSifReturnKcdLclMsg));           //send pbytesStore

	m_RetKcdMsg=(SPMSifReturnKcdLclMsg*)pbytesReceive;							//copy response back to structure

	m_strMain=m_RetKcdMsg->Dta;
	m_strResult=m_RetKcdMsg->ff;
}

/************************************************************************/
/* 制卡                                                                     */
/************************************************************************/
void CVingCardXMSApp::OnbtnMakeKey() 
{
	SPMSifEncodeKcdRmtMsg *m_EncKcdLclMsg;
	BYTE *pbytesSend;
	BYTE *pbytesReceive;

	m_EncKcdLclMsg = new SPMSifEncodeKcdRmtMsg;

    if(m_cardtype == "new")
	{
	    m_EncKcdLclMsg->ff = 'I';//m_strCmd[0];	
	}
	else if(m_cardtype == "copy")
	{
		m_EncKcdLclMsg->ff = 'H';//m_strCmd[0];	
	}
	else 
	{
         m_EncKcdLclMsg->ff = 'E';
	}
					
	BuildData(m_EncKcdLclMsg->ff, &m_EncKcdLclMsg->Dta[0]);   
	strcpy(m_EncKcdLclMsg->dd,m_strEncoder);
	strcpy(m_EncKcdLclMsg->ss,_T("00"));
	m_EncKcdLclMsg->Debug=FALSE;								//Build all the data
	strcpy(m_EncKcdLclMsg->szOpId, m_strSysID);
	strcpy(m_EncKcdLclMsg->szOpFirst, m_strSysFName);
	strcpy(m_EncKcdLclMsg->szOpLast, m_strSysLName);


	SetHeader(&m_EncKcdLclMsg->hdr1, CMD_ENCODERMT);

	pbytesSend = new BYTE[sizeof(SPMSifEncodeKcdRmtMsg)];
	memcpy(pbytesSend, m_EncKcdLclMsg, sizeof(SPMSifEncodeKcdRmtMsg));

	pbytesReceive=TCPSend(pbytesSend, sizeof(SPMSifEncodeKcdRmtMsg));

	m_EncKcdLclMsg=(SPMSifEncodeKcdRmtMsg*)pbytesReceive;

	m_strMain=m_EncKcdLclMsg->Dta;
	m_strResult=m_EncKcdLclMsg->ff;
}



/************************************************************************/
/* 组织数据                                                                     */
/************************************************************************/
void CVingCardXMSApp::BuildData(char Cmd, char* Data)
{

	strcpy(Data, "\x1E");  
	strcat(Data, "R");
	strcat(Data, m_strRoom);
	strcat(Data, "\x1E");
	strcat(Data, "T");
	strcat(Data, m_strUT);
	if(m_strFName != "")
	{
		strcat(Data, "\x1E");
		strcat(Data, "F");
		strcat(Data, m_strFName);
	}
	if(m_strLName != "")
	{
		strcat(Data, "\x1E");
		strcat(Data, "N");
		strcat(Data, m_strLName);
	}
	if(Cmd == 'C')
	{
		if(m_strChRoom != "")
		{
			strcat(Data, "\x1E");
			strcat(Data, "R");
			strcat(Data, m_strChRoom);
		}
		if(m_strChUT != "")
		{
			strcat(Data, "\x1E");
			strcat(Data, "T");
			strcat(Data, m_strChUT);
		}
		if(m_strChFName != "")
		{
			strcat(Data, "\x1E");
			strcat(Data, "F");
			strcat(Data, m_strChFName);
		}
		if(m_strChLName != "")
		{
			strcat(Data, "\x1E");
			strcat(Data, "N");
			strcat(Data, m_strChLName);
		}
	}
	if(m_strUG != "")
	{
		strcat(Data, "\x1E");
		strcat(Data, "U");
		strcat(Data, m_strUG);
	}
	if(m_strStart != "")
	{
		strcat(Data, "\x1E");
		strcat(Data, "D");
		strcat(Data, m_strStart);
	}
	if(m_strEnd != "")
	{
		strcat(Data, "\x1E");
		strcat(Data, "O");
		strcat(Data, m_strEnd);
	}

	strcat(Data, "\x1E");
	strcat(Data, "1");//取电区块，新增
	//strcat(Data, "/");
	strcat(Data, "110324160518706");//31313033323431363035313837303600
	
	strcat(Data, "\x1E");
	strcat(Data, "2");//房间区块，修改由1块移动到2块，因取电冲突
	strcat(Data, m_strRoom);//32303538000000000000000000000000=2058
}

void CVingCardXMSApp::OnbtnCloseConn()
{
	if(m_mySocket!=NULL)
	{
		  closesocket(m_mySocket);
		  WSACleanup();
	}
   

} 

void CVingCardXMSApp::OnbtnConnect() 
{
	//Disable button whilst processing	
	if (m_Connected)  
	{
		m_strMain = "Already Connected";

	}
	else //make a connection
	{
		//Set blocking mode
		//to use non blocking mode you should derive a sub class of CAsynSocket
		//call its AsyncSelect function to enable function overrides and override
		//the OnConnect and OnReceive functions to handle event notification
		//When using blocking (as here) calls to .Connect or .Send wait for an answer

		DWORD dw = 0; //0=blocking, 1 = non blocking
		m_mySocket.IOCtl(FIONBIO, &dw);     
        //AfxMessageBox("Again Connected");
		//connect
		if (m_mySocket.Connect( m_strIP, TCP_SOCKET_PORT))
		{
			m_Connected = TRUE;
			m_strMain = "Connected successfully";
		}
		else
		{
			m_strMain = "Couldn't connect";
		}
	}
}

void SetHeader(SPMSifHdr *hdr1, int Cmd)
{
	hdr1->ui32Synch1=0x55555555;
	hdr1->ui32Synch2=0xaaaaaaaa;
 	hdr1->ui16Version=1;
 	hdr1->ui32Cmd=Cmd;
	hdr1->ui32BodySize=GetSize(Cmd)-sizeof(SPMSifHdr);	
}

int GetSize(int Cmd)
{
	switch(Cmd)
	{
	case CMD_REGISTER:
		return sizeof(SPMSifRegisterMsg);
	case CMD_UNREGISTER:
		return sizeof(SPMSifUnregisterMsg);
	case CMD_ENCODERMT:
		return sizeof(SPMSifEncodeKcdRmtMsg);
	case CMD_RETURNKCD:
		return sizeof(SPMSifReturnKcdLclMsg);
	default:
		return sizeof(SPMSifHdr);
	}
}

BYTE *CVingCardXMSApp::TCPSend(BYTE *pbytesStore, int size)
{
	BYTE *pbytes;
	BOOL bEmpty;
	int nRetVal, nRead;
	int nMsgSize;
	SPMSifHdr spHdr;

	m_mySocket.Send((void*)pbytesStore, size);

	nRetVal = m_mySocket.Receive((void*)&spHdr, sizeof(SPMSifHdr), MSG_PEEK);
	
	if ((nRetVal >= sizeof(SPMSifHdr)) && (spHdr.ui32Synch1 == 0x55555555) && (spHdr.ui32Synch2 == 0xaaaaaaaa))
	{
		nMsgSize = spHdr.ui32BodySize + sizeof(SPMSifHdr);
		pbytes = new BYTE[nMsgSize];
		
		bEmpty = FALSE;
		nRead = 0;
		nRetVal = 0;
		while(!bEmpty)
		{
			nRetVal = m_mySocket.Receive(pbytes, nMsgSize);

			if (nRetVal > 0)
				nRead += nRetVal;

			if ((nRetVal <= 0) || (nRead == nMsgSize))
				bEmpty = TRUE;
			else if (nRead <= nMsgSize)
				pbytes += nRetVal;
		}
		
		if (nRead == nMsgSize)
			return pbytes;
	}
	return pbytesStore;
}




__declspec(dllexport) LPCSTR XMS_ReadCard(LPSTR buffer,LPCTSTR szPMSifIP,LPCSTR szLic,LPCSTR szAppl,LPCSTR szSysID,LPCSTR szSysFName,LPCSTR szSysLName)
{
	theApp.InitInstance();
	theApp.m_strIP = szPMSifIP;
	theApp.m_strLic = szLic;
    theApp.m_strAppl = szAppl;
	theApp.m_strSysID = szSysID;
	theApp.m_strFName = szSysFName;
	theApp.m_strLName = szSysLName;
	
	theApp.m_strCmd = _T("E");

	theApp.OnbtnConnect();
	theApp.OnbtnReg();
	theApp.OnbtnGetBitmap();

	strcpy(buffer, theApp.m_strMain); 


//	theApp.OnbtnUnReg();
	theApp.OnbtnCloseConn();
	return theApp.m_strResult;

}

__declspec(dllexport) LPCSTR XMS_WriteCard(LPSTR buffer,LPCTSTR szPMSifIP,LPCSTR szLic,LPCSTR szAppl,LPCSTR szSysID,LPCSTR szSysFName,LPCSTR szSysLName,
										   LPCSTR szCmd,LPCTSTR szRoom,LPCTSTR szArr,LPCTSTR szDep,LPCTSTR szEncoder,LPCTSTR userType,LPCTSTR groupType)
{
	theApp.InitInstance();
	theApp.m_strIP = szPMSifIP;
	theApp.m_strLic = szLic;
    theApp.m_strAppl = szAppl;
	theApp.m_strSysID = szSysID;
	theApp.m_strFName = szSysFName;
	theApp.m_strLName = szSysLName;
	
	theApp.m_cardtype = szCmd;
	theApp.m_strRoom = szRoom;
	theApp.m_strStart = szArr;
	theApp.m_strEnd = szDep;
	theApp.m_strEncoder = szEncoder;

	theApp.m_strUT = userType;
	theApp.m_strUG = groupType;
	
    
	theApp.OnbtnConnect();

	theApp.OnbtnReg();
	theApp.OnbtnMakeKey();

	strcpy(buffer, theApp.m_strMain); 			
	//theApp.OnbtnUnReg();
	theApp.OnbtnCloseConn();
    return theApp.m_strResult;



}
