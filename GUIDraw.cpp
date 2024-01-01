// GUI Drawing functions

#include "stdafx.h"
#include "GUIDraw.h"
#include "Global.h"

void GUIDrawClass::OnSomeActionToRefreshValues(HWND hWnd, wchar_t *wcs)
{
    HDC hdc = ::GetDC(hWnd);
    DrawValues(hdc, wcs);
    ReleaseDC(hWnd,hdc);
}

void GUIDrawClass::DrawValues(HDC hdc, wchar_t *wcs)
{
	HFONT hFont,hTmp;
	hFont=CreateFontW(18,0,0,0,FW_LIGHT,0,0,0,0,0,0,2,0,L"Segoe UI");
	hTmp=(HFONT)SelectObject(hdc,hFont);
	size_t size = wcslen(wcs);
	int convertsize = static_cast<int>(size);
    TextOutW(hdc, 10, 10, wcs, convertsize);
}

void GUIDrawClass::updateProgressBar(int percentageCounter, HWND hProgressBar, HWND hWnd,wchar_t *hProgressText)
{
	TCHAR percantage[5] = { 0 };
	TCHAR ProgressText[24] = { 0 };
	
	memset(hProgressText, 0, sizeof(hProgressText));
	swprintf_s(percantage, L"%d", percentageCounter);
	wcsncat_s(percantage, L"%", 5);
	::SendMessageW(hProgressBar, PBM_SETPOS, (WPARAM)(INT)percentageCounter, 0);
	wcscpy_s(ProgressText, hProgressText);
	wcsncat_s(ProgressText, AppResStringsObjects.Installing, 24);
	wcsncat_s(ProgressText, percantage, 256);
	OnSomeActionToRefreshValues(hWnd, ProgressText);
	::UpdateWindow(hWnd);
}

void GUIDrawClass::LoadStrings()
{
	AppResStringsObjects.OSName = gr7::LoadStringToW(MainObjects.hInst, IDS_OSNAME);
	AppResStringsObjects.PrivilageError = gr7::LoadStringToW(MainObjects.hInst, IDS_PRIVILAGE_ERROR);
	AppResStringsObjects.NotInstalled = gr7::LoadStringToW(MainObjects.hInst, IDS_NOT_INSTALLED);
	AppResStringsObjects.Installing = gr7::LoadStringToW(MainObjects.hInst, IDS_INSTALLING);
	AppResStringsObjects.SoftwareHiveLoadError = gr7::LoadStringToW(MainObjects.hInst, IDS_SOFT_HIVE_LOAD_ERROR);
	AppResStringsObjects.SystemHiveLoadError = gr7::LoadStringToW(MainObjects.hInst, IDS_SYS_HIVE_LOAD_ERROR);
	AppResStringsObjects.DefaultUserHiveLoadError = gr7::LoadStringToW(MainObjects.hInst, IDS_DEF_HIVE_LOAD_ERROR);
	AppResStringsObjects.SystemUserHiveLoadError = gr7::LoadStringToW(MainObjects.hInst, IDS_SYS_USR_HIVE_ERROR);
	AppResStringsObjects.SoftwareHiveUnloadError = gr7::LoadStringToW(MainObjects.hInst, IDS_SOFT_HIVE_UNLOAD_ERROR);
	AppResStringsObjects.DefaultUserHiveUnloadError = gr7::LoadStringToW(MainObjects.hInst, IDS_DEF_HIVE_UNLOAD_ERROR);
	AppResStringsObjects.SystemHiveUnloadError = gr7::LoadStringToW(MainObjects.hInst, IDS_SYS_HIVE_UNLOAD_ERROR);
	AppResStringsObjects.UpdateFileListAccessError = gr7::LoadStringToW(MainObjects.hInst, IDS_FILE_LIST_ACCESS_ERROR);
	AppResStringsObjects.FailToOpenRegistryKey = gr7::LoadStringToW(MainObjects.hInst, IDS_FAIL_OPEN_KEY);
}