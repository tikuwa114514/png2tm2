
// pngtotm2Dlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "pngtotm2.h"
#include "pngtotm2Dlg.h"
#include "afxdialogex.h"
#include "tim2utils.h"
#include "util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    


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






Cpngtotm2Dlg::Cpngtotm2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PNGTOTM2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cpngtotm2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, PNGpath, PNGPath);
	DDX_Control(pDX, Dirpath, DirPath);
}

BEGIN_MESSAGE_MAP(Cpngtotm2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(selectPNG, &Cpngtotm2Dlg::OnBnClickedselectpng)
	ON_BN_CLICKED(selectDIR, &Cpngtotm2Dlg::OnBnClickedselectdir)
	ON_BN_CLICKED(convert, &Cpngtotm2Dlg::OnBnClickedconvert)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()




BOOL Cpngtotm2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


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


	SetIcon(m_hIcon, TRUE);	
	SetIcon(m_hIcon, FALSE);

	DragAcceptFiles();
	return TRUE;  
}

void Cpngtotm2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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



void Cpngtotm2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;


		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


HCURSOR Cpngtotm2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cpngtotm2Dlg::OnBnClickedselectpng()
{
	#define DEF_EXT  _T("*.png")
	const wchar_t* FILTER = _T("PNG Files (*.png)|*.png|")_T("TM2 Files (*.tm2)|*.tm2|");
	CString imagepath;
	CFileDialog dlg(TRUE, DEF_EXT, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, FILTER,NULL,0,TRUE);
	if (dlg.DoModal() == IDOK)
	{
		imagepath = dlg.GetPathName();
		PNGPath.SetWindowTextW(imagepath);
	}
	else
	{
		return;
	}
}


void Cpngtotm2Dlg::OnBnClickedselectdir()
{
	CString dirpath;
	CFolderPickerDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		dirpath = dlg.GetPathName();
		DirPath.SetWindowTextW(dirpath);
	}
	else
	{
		return;
	}

}


void Cpngtotm2Dlg::OnBnClickedconvert()
{
	CString pngpath,dirpath;
	PNGPath.GetWindowTextW(pngpath);
	DirPath.GetWindowTextW(dirpath);
	if (pngpath.IsEmpty())
	{
		CString errorDisplay;
		errorDisplay.Format(_T("Error:%s"), _T("PNG path is empty"));
		AfxMessageBox(errorDisplay);
		return;
	}
	if (dirpath.IsEmpty())
	{
		CString errorDisplay;
		errorDisplay.Format(_T("Error:%s"), _T("Dir path is empty"));
		AfxMessageBox(errorDisplay);
		return;
	}
	DWORD error;
	std::wstring wpngpath(pngpath);
	std::wstring wdirpath(dirpath);
	error = convertimage(wpngpath, wdirpath);
	if (errno != 0)
	{
		CString errorDisplay;
		errorDisplay.Format(_T("Failed convert %s"), wpngpath.c_str());
		AfxMessageBox(errorDisplay);
		return;
	}
	CString errorDisplay;
	errorDisplay.Format(_T("%s"), _T("Convert is finished!"));
	AfxMessageBox(errorDisplay);
	return;
}



void Cpngtotm2Dlg::OnDropFiles(HDROP hDropInfo)
{
	UINT length = DragQueryFile(hDropInfo, -1, NULL, 0);
	CString imagepath, dirpath;
	DWORD error;
	for (size_t i = 0; i < length; i++)
	{
		DragQueryFile(hDropInfo, i, imagepath.GetBuffer(MAX_PATH), MAX_PATH + 1);
		imagepath.ReleaseBuffer();
		dirpath = imagepath.Left(imagepath.ReverseFind('\\'));
		std::wstring wimagepath(imagepath);
		std::wstring wdirpath(dirpath);
		error = convertimage(wimagepath, wdirpath);
		if (errno != 0)
		{
			if (errno != 0)
			{
				//CDialogEx::OnDropFiles(hDropInfo);
				CString errorDisplay;
				errorDisplay.Format(_T("Failed convert %s"), wimagepath.c_str());
				AfxMessageBox(errorDisplay);
			}
			CString errorDisplay;
			errorDisplay.Format(_T("Failed convert %s"), wimagepath.c_str());
			AfxMessageBox(errorDisplay);
		}
	}	
	CString errorDisplay;
	errorDisplay.Format(_T("%s"), _T("Convert is finished!"));
	AfxMessageBox(errorDisplay);
}
