
// lambda_thread_gui.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Clambda_thread_guiApp: 
// �йش����ʵ�֣������ lambda_thread_gui.cpp
//

class Clambda_thread_guiApp : public CWinApp
{
public:
	Clambda_thread_guiApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Clambda_thread_guiApp theApp;