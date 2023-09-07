
// Labirinth_deep_finding.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CLabirinthdeepfindingApp:
// Сведения о реализации этого класса: Labirinth_deep_finding.cpp
//

class CLabirinthdeepfindingApp : public CWinApp
{
public:
	CLabirinthdeepfindingApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CLabirinthdeepfindingApp theApp;
