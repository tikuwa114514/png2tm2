
// pngtotm2Dlg.h : ヘッダー ファイル
//

#pragma once

// Cpngtotm2Dlg ダイアログ
class Cpngtotm2Dlg : public CDialogEx
{
// コンストラクション
public:
	Cpngtotm2Dlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PNGTOTM2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedselectpng();
	CEdit PNGPath;
	CEdit DirPath;
	afx_msg void OnBnClickedselectdir();
	afx_msg void OnBnClickedconvert();
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
