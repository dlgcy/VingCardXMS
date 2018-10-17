// VingCardXMS.h : main header file for the VINGCARDXMS DLL
//

#if !defined(AFX_VINGCARDXMS_H__A80B0A0A_B2B4_49F6_BD39_6BDC2D8F4CF0__INCLUDED_)
#define AFX_VINGCARDXMS_H__A80B0A0A_B2B4_49F6_BD39_6BDC2D8F4CF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVingCardXMSApp
// See VingCardXMS.cpp for the implementation of this class
//

class CVingCardXMSApp : public CWinApp
{
public:
	BOOL m_Connected;
	CString	m_strAppl;
	CString	m_strChRoom;
	CString	m_strChUT;
	CString	m_strCmd;
	CString	m_strEnd;
	CString	m_strChFName;
	CString	m_strChLName;
	CString	m_strFName;
	CString	m_strLic;
	CString	m_strLName;
	CString	m_strMain;
	int		m_iRegRes;
	CString	m_strRoom;
	CString	m_strStart;
	CString	m_strSysFName;
	CString	m_strSysID;
	CString	m_strSysLName;
	CString	m_strUG;
	CString	m_strUT;
	int		m_iUnRegRes;
	CString	m_strResult;
	CString	m_strIP;
	CString m_strEncoder;
	CString m_cardtype;
private:
	CAsyncSocket m_mySocket;
	void BuildData(char, char*);
	BYTE *TCPSend(BYTE*, int);
public:
	CVingCardXMSApp();

public:
	void OnbtnReg();
	void OnbtnUnReg();
	void OnbtnGetBitmap();
	void OnbtnMakeKey();
	void OnbtnConnect();
	void OnbtnCloseConn();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVingCardXMSApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CVingCardXMSApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#pragma pack(1)

struct SPMSifHdr{
	DWORD32 ui32Synch1;		//Message synch1 = 0x55555555.
	DWORD32 ui32Synch2;		//Message synch1 = 0xaaaaaaaa.
	USHORT  ui16Version;	//Header format version = 1.
	DWORD32 ui32Cmd;		//field Command
	DWORD32 ui32BodySize;	//field size of message body.
} ;

struct SPMSifRegisterMsg
{
	SPMSifHdr	hdr1;
	char		szLicense[20];
	char		szApplName[20];
	int			nRet;
};

struct SPMSifUnregisterMsg
{
	SPMSifHdr	hdr1;
	int			nRet;
};

struct SPMSifEncodeKcdRmtMsg
{
	SPMSifHdr	hdr1;
	char		ff;
	char		Dta[512];
	char        dd[3];
	char        ss[3];
	BOOL		Debug;
	char		szOpId[10];
	char		szOpFirst[16];
	char		szOpLast[16];
};

struct SPMSifReturnKcdLclMsg
{
	SPMSifHdr	hdr1;
	char		ff;
	char		Dta[512];
	BOOL		Debug;
	char		szOpId[10];
	char		szOpFirst[16];
	char		szOpLast[16];
};

#pragma pack()

void SetHeader(SPMSifHdr *hdr1, int Cmd);
int GetSize(int Cmd);




extern "C"
{
	__declspec(dllexport) LPCSTR XMS_ReadCard(LPSTR buffer,LPCTSTR szPMSifIP,LPCSTR szLic,LPCSTR szAppl,LPCSTR szSysID,LPCSTR szSysFName,LPCSTR szSysLName);
	__declspec(dllexport) LPCSTR XMS_WriteCard(LPSTR buffer,LPCTSTR szPMSifIP,LPCSTR szLic,LPCSTR szAppl,LPCSTR szSysID,LPCSTR szSysFName,LPCSTR szSysLName,LPCSTR szCmd,LPCTSTR szRoom,LPCTSTR szArr,LPCTSTR szDep,LPCTSTR szEncoder,LPCTSTR userType,LPCTSTR groupType);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VINGCARDXMS_H__A80B0A0A_B2B4_49F6_BD39_6BDC2D8F4CF0__INCLUDED_)
