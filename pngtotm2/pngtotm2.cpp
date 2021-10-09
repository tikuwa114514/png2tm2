
// pngtotm2.cpp : アプリケーションのクラス動作を定義します。
//

#include "pch.h"
#include "framework.h"
#include "pngtotm2.h"
#include "pngtotm2Dlg.h"
#include "util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



int main(int argc, char** argv)
{
	setlocale(LC_CTYPE, "jpn");
	if (argc == 1)
	{
		return wWinMain(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), SW_HIDE);
	}
	else if (argc == 2)
	{
		char* filename = argv[1];
		int codepage = GetConsoleOutputCP();
		int filenamesize = strlen(filename);
		const int wfilenamesize = MultiByteToWideChar(codepage, 0, &filename[0], filenamesize , NULL, 0);
		wchar_t* wfilename = new wchar_t[filenamesize+1] {0};
		MultiByteToWideChar(codepage, 0, &filename[0], filenamesize, wfilename,wfilenamesize );
		std::wstring wstrfilename(wfilename);
		std::wstring dirpath = wstrfilename.substr(0, wstrfilename.find_last_of('\\'));
		int error = convertimage(wstrfilename,dirpath);
		delete wfilename;
		if (error!=0)
		{
			ErrMSG(L"Failed Convert Image");
		}
		return 0;
	}
	else
	{
		ErrMSG(L"invalid argument");
		return -1;
	}
}
// Cpngtotm2App

BEGIN_MESSAGE_MAP(Cpngtotm2App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Cpngtotm2App の構築

Cpngtotm2App::Cpngtotm2App()
{
	// 再起動マネージャーをサポートします
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}


// 唯一の Cpngtotm2App オブジェクト

Cpngtotm2App theApp;


// Cpngtotm2App の初期化

BOOL Cpngtotm2App::InitInstance()
{
	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ダイアログにシェル ツリー ビューまたはシェル リスト ビュー コントロールが
	// 含まれている場合にシェル マネージャーを作成します。
	CShellManager *pShellManager = new CShellManager;

	// MFC コントロールでテーマを有効にするために、"Windows ネイティブ" のビジュアル マネージャーをアクティブ化
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 標準初期化
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: 会社名または組織名などの適切な文字列に
	// この文字列を変更してください。
	SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));

	Cpngtotm2Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//  記述してください。
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <キャンセル> で消された時のコードを
		//  記述してください。
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: ダイアログの作成に失敗しました。アプリケーションは予期せずに終了します。\n");
		TRACE(traceAppMsg, 0, "警告: ダイアログで MFC コントロールを使用している場合、#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS を指定できません。\n");
	}

	// 上で作成されたシェル マネージャーを削除します。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// ダイアログは閉じられました。アプリケーションのメッセージ ポンプを開始しないで
	//  アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}

