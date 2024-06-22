// winRE part of the Grass7 Updater

#include "stdafx.h"
#include "Global.h"
#include "Registry.h"
#include "FileManagement.h"
#include "MainCode.h"
#include "GUIDraw.h"
#include "ResourceLoader.h"
#include "Global.h"
#include <sdkddkver.h>
#include <vector>
#include <thread>

GlobalMain MainObjects;
GlobalAppResStrings AppResStringsObjects;

TCHAR wcs[MAX_PATH];

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				GUIDrawClass::DrawValues(hdc, wcs);
				EndPaint(hWnd, &ps);
			}
			break;

	case WM_DESTROY:
		::PostQuitMessage(0);
		break;

	default:
		return ::DefWindowProcW(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	MainObjects.hInst = hInstance;
	ResourceLoader::LoadStrings();
    if (!SUCCEEDED(Grass7API::Privilege::ModifyPrivilege(SE_RESTORE_NAME, TRUE, GetCurrentProcess()))) {
		MessageBoxW(NULL, AppResStringsObjects.PrivilageError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
		exit(0);
	}

    if (!SUCCEEDED(Grass7API::Privilege::ModifyPrivilege(SE_BACKUP_NAME, TRUE, GetCurrentProcess()))) {
		MessageBoxW(NULL, AppResStringsObjects.PrivilageError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
		exit(0);
	}

	// Get drive letter of the Grass7 install to apply the update to.
	MainObjects.driveletter = FileManagementClass::Getgr7DriveLetter();
	MainObjects.driveletterW = FileManagementClass::Getgr7DriveLetterW();
	if(MainObjects.driveletter == "") {
		MessageBoxW(NULL, AppResStringsObjects.NotInstalled.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
		exit(0);
	}

	std::wstring UpdateFilesFolder = MainObjects.driveletterW;
	UpdateFilesFolder.append(L"gr7updatefld");

	if(Grass7API::FileManagement::dirExists(UpdateFilesFolder.c_str()) != 1) {
		PROCESS_INFORMATION processInfo;
		STARTUPINFO info = { sizeof(info) };
		std::wstring recoveryexe = L"\"X:\\sources\\recovery\\recenv.exe\"";
		if (CreateProcessW(NULL, &recoveryexe[0], NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
		{
			WaitForSingleObject(processInfo.hProcess, INFINITE);
			CloseHandle(processInfo.hProcess);
			CloseHandle(processInfo.hThread);
		}
		exit(0);
	}

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
	wcex.lpszClassName = L"GRASS7UPDATER";
	wcex.hbrBackground = hb;
	wcex.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;

	if (!RegisterClassExW(&wcex))
		return 1;

	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HWND hWnd = ::CreateWindowExW(
		0,
		L"GRASS7UPDATER",
		AppResStringsObjects.OSName.c_str(),
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

	hSmoothProgressCtrl = ::CreateWindowExW(
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

	wcsncat_s(wcs, AppResStringsObjects.Installing.c_str(), sizeof(wcs));
	wcsncat_s(wcs, L"0%", sizeof(wcs));
	::SendMessageW(hSmoothProgressCtrl, PBM_SETPOS, (WPARAM)(INT)0, 0);
	::ShowWindow(hWnd, SW_SHOWDEFAULT);
	::UpdateWindow(hWnd);
	std::thread MainCodeThread(MainCodeClass::mainCode, std::ref(hSmoothProgressCtrl), std::ref(hWnd), std::ref(wcs));
	MainCodeThread.detach();

	MSG msg;
	while (::GetMessageW(&msg, hWnd, 0, 0) > 0)
		::DispatchMessageW(&msg);

	::UnregisterClassW(wcex.lpszClassName, hInstance);

	return (int)msg.wParam;
}