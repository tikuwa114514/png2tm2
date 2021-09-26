
// pngtotm2.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// Cpngtotm2App:
// このクラスの実装については、pngtotm2.cpp を参照してください
//

class Cpngtotm2App : public CWinApp
{
public:
	Cpngtotm2App();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern Cpngtotm2App theApp;
