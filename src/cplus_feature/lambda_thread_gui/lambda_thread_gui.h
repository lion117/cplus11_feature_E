
// lambda_thread_gui.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// Clambda_thread_guiApp: 
// 有关此类的实现，请参阅 lambda_thread_gui.cpp
//

class Clambda_thread_guiApp : public CWinApp
{
public:
	Clambda_thread_guiApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern Clambda_thread_guiApp theApp;