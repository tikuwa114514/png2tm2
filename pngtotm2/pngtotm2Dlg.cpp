﻿
// pngtotm2Dlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "pngtotm2.h"
#include "pngtotm2Dlg.h"
#include "afxdialogex.h"
#include "tim2utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
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


// Cpngtotm2Dlg ダイアログ



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


// Cpngtotm2Dlg メッセージ ハンドラー

BOOL Cpngtotm2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
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

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	DragAcceptFiles();
	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
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

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void Cpngtotm2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR Cpngtotm2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cpngtotm2Dlg::OnBnClickedselectpng()
{
	#define DEF_EXT  _T("*.png")
	#define FILTER   _T("PNG(*.png)|*.png")
	CString pngpath;
	CFileDialog dlg(TRUE, DEF_EXT, NULL, 0, FILTER);
	if (dlg.DoModal() == IDOK)
	{
		pngpath = dlg.GetPathName();
		PNGPath.SetWindowTextW(pngpath);
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
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void Cpngtotm2Dlg::OnBnClickedconvert()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
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
	Cpngtotm2Dlg::convertpng2tm2(pngpath, dirpath);
	return;
}

DWORD Cpngtotm2Dlg::convertpng2tm2(CString pngpath,CString dirpath) {
	CString pngname, tm2path;
	pngname = pngpath.Mid(pngpath.ReverseFind('\\') + 1);
	pngname = pngname.Left(pngname.ReverseFind('.') + 1);
	tm2path = dirpath + "\\" + pngname + _T("tm2");
	uint32_t dataSize;
	int w, h;
	void* data = OutbreakPngToTm2(CT2A(pngpath), 0, &w, &h, &dataSize);
	if (data)
	{
		FILE* outfp;
		outfp = fopen(CT2A(tm2path), "wb");
		if (outfp == NULL)
		{
			CString errorDisplay;
			errorDisplay.Format(_T("Error:%s"), _T("Can't write tm2"));
			AfxMessageBox(errorDisplay);
			return -1;
		}
		if (fwrite(data, sizeof(char), dataSize, outfp) < 1) {
			CString errorDisplay;
			errorDisplay.Format(_T("Error:%s"), _T("Faild save tm2"));
			AfxMessageBox(errorDisplay);
		}
		fclose(outfp);
		free(data);
		return 0;
	}
	else
	{
		CString errorDisplay;
		errorDisplay.Format(_T("Error:%s"), _T("Faild Convert PNG to TM2"));
		AfxMessageBox(errorDisplay);
		return -1;
	}
}

void Cpngtotm2Dlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	UINT length = DragQueryFile(hDropInfo, -1, NULL, 0);
	CString pngpath , dirpath;
	DWORD error;
	for (size_t i = 0; i < length; i++)
	{
		DragQueryFile(hDropInfo, i, pngpath.GetBuffer(MAX_PATH), MAX_PATH + 1);
		pngpath.ReleaseBuffer();
		dirpath = pngpath.Left(pngpath.ReverseFind('\\'));
		error = Cpngtotm2Dlg::convertpng2tm2(pngpath, dirpath);
	}

	
	
	CDialogEx::OnDropFiles(hDropInfo);

}