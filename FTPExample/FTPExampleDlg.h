
// FTPExampleDlg.h: 헤더 파일
//

#pragma once
#include <winsock2.h>
#include <fstream>

#include "libssh2.h"
#include "libssh2_sftp.h"

#pragma comment(lib, "ws2_32.lib")

//#ifdef _DEBUG
//#define DCURL_STATICLIB
//#else
//#define CURL_STATICLIB
//#endif // _DEBUG
//
//
//#include "curl/curl.h"
//#include <Winsock2.h>
//
//#ifdef _DEBUG
//#pragma comment(lib, "libcurl_a_debug.lib")
//#else
//#pragma comment(lib, "libcurl_a.lib")
//#endif // _DEBUG
//
//#pragma comment(lib, "wldap32.lib")
//#pragma comment(lib, "Ws2_32.lib")
//#pragma comment(lib, "CRYPT32.lib")
//#pragma comment(lib, "Normaliz.lib")

// CFTPExampleDlg 대화 상자
class CFTPExampleDlg : public CDialogEx
{
// 생성입니다.
public:
	CFTPExampleDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FTPEXAMPLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	
public:
	afx_msg void OnBnClickedButtonConnect();
	size_t GetFilesList_response(void* ptr, size_t size, size_t nmemb, void* data);
};
