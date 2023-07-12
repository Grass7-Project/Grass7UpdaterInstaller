// winRE part of the Grass7 Updater

#include "stdafx.h"
#include "Registry.h"
#include "FileManagement.h"
#include "MainCode.h"
#include "GUIDraw.h"
#include <sdkddkver.h>
#include <vector>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

TCHAR wcs[256];

LRESULT
CALLBACK
WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				DrawValues(hdc, wcs);
				EndPaint(hWnd, &ps);
			}
			break;

	case WM_DESTROY:
		::PostQuitMessage(0);
		break;

	default:
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

int
APIENTRY
wWinMain(
HINSTANCE hInstance,
HINSTANCE hPrevInstance,
LPWSTR lpCmdLine,
int nShowCmd)
{
    if (!SUCCEEDED(gr7::ModifyPrivilege(SE_RESTORE_NAME, TRUE, GetCurrentProcess()))) {
        MessageBox(NULL, gr7::LoadStringToW(GetModuleHandle(NULL),IDS_PRIVILAGE_ERROR), gr7::LoadStringToW(GetModuleHandle(NULL),IDS_OSNAME), MB_OK | MB_ICONERROR);
		exit(0);
	}

    if (!SUCCEEDED(gr7::ModifyPrivilege(SE_BACKUP_NAME, TRUE, GetCurrentProcess()))) {
        MessageBox(NULL, gr7::LoadStringToW(GetModuleHandle(NULL),IDS_PRIVILAGE_ERROR), gr7::LoadStringToW(GetModuleHandle(NULL),IDS_OSNAME), MB_OK | MB_ICONERROR);
		exit(0);
	}

	//Get drive letter of the Grass7 install to apply the update to.
	const char *driveletter = Getgr7DriveLetter();
	if(driveletter == "") {
		MessageBox(NULL, gr7::LoadStringToW(GetModuleHandle(NULL),IDS_NOT_INSTALLED), gr7::LoadStringToW(GetModuleHandle(NULL),IDS_OSNAME), MB_OK | MB_ICONERROR);
		exit(0);
	}
	char bufferp[256];
	strncpy_s(bufferp, driveletter, sizeof(bufferp));
	strncat_s(bufferp, "gr7updatefld", sizeof(bufferp));

	if(gr7::dirExists(bufferp) != 1) {
		PROCESS_INFORMATION processInfo;
		STARTUPINFO info={sizeof(info)};
		if ( CreateProcess(NULL, gr7::convertchar(("X:\\sources\\recovery\\recenv.exe")), NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
		{
			WaitForSingleObject(processInfo.hProcess, INFINITE);
			CloseHandle(processInfo.hProcess);
			CloseHandle(processInfo.hThread);
		}
		memset(bufferp, 0, sizeof(bufferp));
		exit(0);
	}
	memset(bufferp, 0, sizeof(bufferp));

	// Window shit

	INITCOMMONCONTROLSEX iccex;
	iccex.dwSize = sizeof(iccex);
	iccex.dwICC = ICC_PROGRESS_CLASS;

	HBRUSH hb = ::CreateSolidBrush(RGB(255,255,255));

	if (!InitCommonControlsEx(&iccex))
		return 1;

	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpszClassName = TEXT("GRASS7UPDATER");
	wcex.hbrBackground = hb;
	wcex.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;

	if (!RegisterClassEx(&wcex))
		return 1;

	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HWND hWnd = ::CreateWindowEx(
		0,
		_T("GRASS7UPDATER"),
		gr7::LoadStringToW(GetModuleHandle(NULL),IDS_OSNAME),
		WS_OVERLAPPED | WS_CAPTION,
		0,
		0,
		386,
		155,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd)
		return 1;

	HWND hSmoothProgressCtrl;

	hSmoothProgressCtrl = ::CreateWindowEx(
		0,
		PROGRESS_CLASS,
		TEXT(""),
		WS_CHILD | WS_VISIBLE | PBS_SMOOTH,
		10,
		40,
		346,
		20,
		hWnd,
		(HMENU)ID_SMOOTHPROGRESSCTRL,
		hInstance,
		NULL);

	wcsncat_s(wcs, gr7::LoadStringToW(GetModuleHandle(NULL),IDS_INSTALLING), 256);
	wcsncat_s(wcs, _T("0%"), 256);
	::SendMessage(hSmoothProgressCtrl, PBM_SETPOS, (WPARAM)(INT)0, 0);
	::ShowWindow(hWnd, SW_SHOWDEFAULT);
	::UpdateWindow(hWnd);
	mainCode(hSmoothProgressCtrl, hWnd, wcs);

	MSG msg;
	while (::GetMessage(&msg, hWnd, 0, 0) > 0)
		::DispatchMessage(&msg);

	::UnregisterClass(wcex.lpszClassName, hInstance);

	return (int)msg.wParam;
}