// GUI Drawing functions

#include "stdafx.h"
#include "GUIDraw.h"

void OnSomeActionToRefreshValues(HWND hWnd, wchar_t *wcs)
{
    HDC hdc = ::GetDC(hWnd);
    DrawValues(hdc, wcs);
    ReleaseDC(hWnd,hdc);
}

void DrawValues(HDC hdc, wchar_t *wcs)
{
	HFONT hFont,hTmp;
	hFont=CreateFont(18,0,0,0,FW_LIGHT,0,0,0,0,0,0,2,0,_T("Segoe UI"));
	hTmp=(HFONT)SelectObject(hdc,hFont);
	size_t size = wcslen(wcs);
	int convertsize = static_cast<int>(size);
    TextOut(hdc, 10, 10, wcs, convertsize);
}

void updateProgressBar(int percentageCounter, HWND hProgressBar, HWND hWnd,wchar_t *hProgressText)
{
	TCHAR percantage[5];
	TCHAR ProgressText[24];
	
	memset(hProgressText, 0, sizeof(hProgressText));
	swprintf_s(percantage, L"%d", percentageCounter);
	wcsncat_s(percantage, _T("%"), 5);
	::SendMessage(hProgressBar, PBM_SETPOS, (WPARAM)(INT)percentageCounter, 0);
	wcscpy_s(ProgressText, hProgressText);
	wcsncat_s(ProgressText, gr7::LoadStringToW(GetModuleHandle(NULL),IDS_INSTALLING), 24);
	wcsncat_s(ProgressText, percantage, 256);
	OnSomeActionToRefreshValues(hWnd, ProgressText);
	::UpdateWindow(hWnd);
}