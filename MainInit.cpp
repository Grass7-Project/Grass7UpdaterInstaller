#include "stdafx.h"
#include "MainInit.h"
#include "FileManagement.h"
#include "ResourceLoader.h"
#include "MainGUI.h"

int MainInit::Init(HINSTANCE &hInstance)
{
	MainObjects.hInst = hInstance;
	ResourceLoader::LoadStrings();
	if (!SUCCEEDED(Grass7API::Privilege::ModifyPrivilege(SE_RESTORE_NAME, TRUE, GetCurrentProcess()))) {
		MessageBoxW(nullptr, AppResStringsObjects.PrivilageError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
		return 1;
	}

	if (!SUCCEEDED(Grass7API::Privilege::ModifyPrivilege(SE_BACKUP_NAME, TRUE, GetCurrentProcess()))) {
		MessageBoxW(nullptr, AppResStringsObjects.PrivilageError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
		return 1;
	}

	FileManagement::Getgr7DriveLetter(MainObjects.driveletter);
	if (MainObjects.driveletter == L"") {
		MessageBoxW(nullptr, AppResStringsObjects.NotInstalled.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
		return 1;
	}

	std::wstring UpdateFilesFolder = MainObjects.driveletter;
	UpdateFilesFolder.append(L"gr7updatefld");

	if (Grass7API::FileManagement::dirExists(UpdateFilesFolder.c_str()) != 1) {
		PROCESS_INFORMATION processInfo;
		STARTUPINFO info = { sizeof(info) };
		std::wstring recoveryexe = L"\"X:\\sources\\recovery\\recenv.exe\"";
		if (CreateProcessW(nullptr, &recoveryexe[0], nullptr, nullptr, TRUE, 0, nullptr, nullptr, &info, &processInfo))
		{
			WaitForSingleObject(processInfo.hProcess, INFINITE);
			CloseHandle(processInfo.hProcess);
			CloseHandle(processInfo.hThread);
		}
		return 0;
	}

	return MainGUI::Init();
}