
// FTPExampleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "FTPExample.h"
#include "FTPExampleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <functional>


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFTPExampleDlg 대화 상자



CFTPExampleDlg::CFTPExampleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FTPEXAMPLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFTPExampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFTPExampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CFTPExampleDlg::OnBnClickedButtonConnect)
END_MESSAGE_MAP()


// CFTPExampleDlg 메시지 처리기

BOOL CFTPExampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CFTPExampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CFTPExampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CFTPExampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFTPExampleDlg::OnBnClickedButtonConnect()
{
	// 소켓 초기화
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	struct sockaddr_in sin;

	// 소켓 생성
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	sin.sin_family = AF_INET;
	sin.sin_port = htons(22);
	sin.sin_addr.s_addr = inet_addr("193.122.104.241");
	if (connect(sock, (struct sockaddr*)(&sin),
		sizeof(struct sockaddr_in)) != 0) {
		fprintf(stderr, "failed to connect!\n");
		return;
	}

	// libssh2 초기화
	int rc = libssh2_init(0);
	if (rc != 0)
	{
		//std::cerr << "libssh2 초기화에 실패하였습니다." << std::endl;
		return;
	}

	// SSH 세션 초기화
	LIBSSH2_SESSION* session;
	session = libssh2_session_init();
	if (session == nullptr)
	{
		//std::cerr << "SSH 세션을 생성할 수 없습니다." << std::endl;
		libssh2_exit();
		return;
	}

	const char* host = "193.122.104.241";
	const int port = 22;
	const char* user = "roboticsmas";
	const char* password = "qazwsx1212!";

	libssh2_session_set_blocking(session, 1);  // 블로킹 모드 설정 (0: non-blocking, 1: blocking)
	libssh2_session_set_timeout(session, 1000000);  // 타임아웃 설정 (밀리초 단위)
	
	// SSH 연결 설정
	rc = libssh2_session_startup(session, sock);
	if (rc != 0)
	{
		//std::cerr << "SSH 연결에 실패하였습니다." << std::endl;
		libssh2_session_free(session);
		libssh2_exit();
		return;
	}

	// SSH 사용자 인증
	rc = libssh2_userauth_password(session, user, password);
	if (rc != 0)
	{
		//std::cerr << "SSH 사용자 인증에 실패하였습니다." << std::endl;
		libssh2_session_disconnect(session, "인증 실패");
		libssh2_session_free(session);
		libssh2_exit();
		return;
	}

	// SFTP 세션 초기화
	LIBSSH2_SFTP* sftp;
	sftp = libssh2_sftp_init(session);
	if (sftp == nullptr)
	{
		//std::cerr << "SFTP 세션을 생성할 수 없습니다." << std::endl;
		libssh2_session_disconnect(session, "SFTP 초기화 실패");
		libssh2_session_free(session);
		libssh2_exit();
		return;
	}

	// 파일 다운로드
	const char* remoteFilePath = "/home1/roboticsmas/test/LXtestPIC_1.JPG.enc";
	TCHAR Path[MAX_PATH];
	SHGetSpecialFolderPath(NULL, Path, CSIDL_DESKTOP, FALSE);

	//const char* localFilePath = temp + "\\LXtestPIC_1.JPG.enc";
	CString localFilePath;

	localFilePath.Format(_T("%s%s"), Path, "\\/result/LXtestPIC_1.JPG.enc");
	LIBSSH2_SFTP_HANDLE* sftp_handle;
	sftp_handle = libssh2_sftp_open(sftp, remoteFilePath, LIBSSH2_FXF_READ, 0);
	if (sftp_handle == nullptr)
	{
		//std::cerr << "원격 파일을 열 수 없습니다." << std::endl;
		libssh2_sftp_shutdown(sftp);
		libssh2_session_disconnect(session, "SFTP 디렉터리 열기 실패");
		libssh2_session_free(session);
		libssh2_exit();
		return;
	}

	std::ofstream localFile;
	localFile.open(localFilePath, std::ios::binary);

	char buffer[102400];
	ssize_t bytesRead;
	while ((bytesRead = libssh2_sftp_read(sftp_handle, buffer, sizeof(buffer))) > 0)
	{
		localFile.write(buffer, bytesRead);
	}

	localFile.close();

	if (bytesRead < 0)
	{
		//std::cerr << "파일 다운로드 중 오류가 발생했습니다." << std::endl;
		libssh2_sftp_close(sftp_handle);
		libssh2_sftp_shutdown(sftp);
		libssh2_session_disconnect(session, "파일 다운로드 실패");
		libssh2_session_free(session);
		libssh2_exit();
		return;
	}

	int result = libssh2_sftp_unlink(sftp, remoteFilePath);
	if (result != 0)
	{
		//std::cerr << "원격 파일을 삭제할 수 없습니다." << std::endl;
		libssh2_sftp_shutdown(sftp);
		libssh2_session_disconnect(session, "원격 파일 삭제 실패");
		libssh2_session_free(session);
		libssh2_exit();
		return;
	}

	libssh2_sftp_close(sftp_handle);
	libssh2_sftp_shutdown(sftp);

	// SFTP 세션 및 SSH 세션 정리
	libssh2_session_disconnect(session, "작업 완료");
	libssh2_session_free(session);
	libssh2_exit();
}