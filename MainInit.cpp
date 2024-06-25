#include "stdafx.h"
#include "MainInit.h"
#include "FileManagement.h"
#include "ResourceLoader.h"
#include "MainGUI.h"

int MainInit::Init(MSG &msg, HINSTANCE &hInstance, HINSTANCE &hPrevInstance, LPTSTR &lpCmdLine, int &nCmdShow)
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
	if (MainObjects.driveletter == "") {
		MessageBoxW(NULL, AppResStringsObjects.NotInstalled.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
		exit(0);
	}

	std::wstring UpdateFilesFolder = MainObjects.driveletterW;
	UpdateFilesFolder.append(L"gr7updatefld");

	if (Grass7API::FileManagement::dirExists(UpdateFilesFolder.c_str()) != 1) {
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

	if (!MainGUI::Init(MainObjects.hWndMainWindow, MainObjects.hInst)) {
		return FALSE;
	}

	return 0;
}