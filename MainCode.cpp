#include "stdafx.h"
#include "Registry.h"
#include "FileManagement.h"
#include "MainCode.h"
#include "GUIDraw.h"
#include "ConfigManager.h"

MainCode MainCodeObjects;

void MainCode::mainCode()
{
	Sleep(2000);
	Registry::Init();
	std::wstring tempfolder = MainObjects.driveletter;
	tempfolder.append(L"gr7updatefld");
	SetCurrentDirectoryW(tempfolder.c_str());
	MainObjects.InstallPercentage = MainObjects.InstallPercentage + 10;
	RedrawWindow(MainObjects.hWndMainWindow, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	MainCodeObjects.UpdateConfigFile.append(MainObjects.driveletter);
	MainCodeObjects.UpdateConfigFile.append(L"gr7updatefld\\Update.conf");
	if (ConfigManager::LoadConfig(MainCodeObjects.UpdateConfigFile)) {
		MessageBoxW(MainObjects.hWndMainWindow, AppResStringsObjects.ConfigAccessError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
		exit(1);
	}

	MainObjects.InstallPercentage = MainObjects.InstallPercentage + 10;
	RedrawWindow(MainObjects.hWndMainWindow, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	if (Registry::loadSoftwareHive() != ERROR_SUCCESS) {
		MessageBoxW(MainObjects.hWndMainWindow, AppResStringsObjects.SoftwareHiveLoadError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
		exit(1);
	}

	HKEY hKeyGr7CurrentVersion;

	if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"gr7Software\\Grass7\\CurrentVersion", 0, KEY_WRITE, &hKeyGr7CurrentVersion) != ERROR_SUCCESS)
	{
		MessageBoxW(MainObjects.hWndMainWindow, AppResStringsObjects.FailToOpenRegistryKey.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
		exit(1);
	}

	if (ConfigObjects.NewUpdateLevel.compare(L"none")) {
		LPCTSTR dat1 = ConfigObjects.NewUpdateLevel.c_str();
		RegSetValueExW(hKeyGr7CurrentVersion, L"UpdateLevel", 0, REG_SZ, (LPBYTE)dat1, 256);
	}

	if (ConfigObjects.NewPatchLevel.compare(L"none")) {
		LPCTSTR dat2 = ConfigObjects.NewPatchLevel.c_str();
		RegSetValueExW(hKeyGr7CurrentVersion, L"PatchLevel", 0, REG_SZ, (LPBYTE)dat2, 256);
	}

	if (ConfigObjects.NewBuildString.compare(L"none")) {
		LPCTSTR dat3 = ConfigObjects.NewBuildString.c_str();
		RegSetValueExW(hKeyGr7CurrentVersion, L"BuildString", 0, REG_SZ, (LPBYTE)dat3, 256);
		std::wstring newBuildStr = ConfigObjects.NewBuildString.substr(0, ConfigObjects.NewBuildString.find(L"."));
		LPCTSTR dat4 = newBuildStr.c_str();
		RegSetValueExW(hKeyGr7CurrentVersion, L"CurrentBuild", 0, REG_SZ, (LPBYTE)dat4, 256);
	}

	RegCloseKey(hKeyGr7CurrentVersion);

	if (ConfigObjects.LoadSysReg == TRUE) {
		if (Registry::loadSystemHive() != ERROR_SUCCESS) {
			MessageBoxW(MainObjects.hWndMainWindow, AppResStringsObjects.SystemHiveLoadError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
			exit(1);
		}
	}
	if (ConfigObjects.LoadDefaultReg == TRUE) {
		if (Registry::loadDefaultHive() != ERROR_SUCCESS) {
			MessageBoxW(MainObjects.hWndMainWindow, AppResStringsObjects.DefaultUserHiveLoadError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
			exit(1);
		}
	}
	if (ConfigObjects.LoadSystemUserReg == TRUE) {
		if (Registry::loadSystemUserHive() != ERROR_SUCCESS) {
			MessageBoxW(MainObjects.hWndMainWindow, AppResStringsObjects.SystemUserHiveLoadError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
			exit(1);
		}
	}

	if (ConfigObjects.UnloadSoftRegOnCmd == TRUE) {
		if (Registry::unloadSoftwareHive() != 0) {
			MessageBoxW(MainObjects.hWndMainWindow, AppResStringsObjects.SoftwareHiveUnloadError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONWARNING);
		}
	}

	if (ConfigObjects.CommandsEnabled == 1) {
		std::wstring cmddlol = MainObjects.driveletter;
		cmddlol.append(L"gr7updatefld\\commands.bat");

		SHELLEXECUTEINFO ShExecInfo;
		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		ShExecInfo.hwnd = nullptr;
		ShExecInfo.lpVerb = L"open";
		ShExecInfo.lpFile = cmddlol.c_str();
		ShExecInfo.lpParameters = L"";
		ShExecInfo.lpDirectory = MainObjects.driveletter.c_str();

		if (ConfigObjects.CommandlineShow == 1) {
			ShExecInfo.nShow = SW_SHOW;
		}
		if (ConfigObjects.CommandlineShow == 0) {
			ShExecInfo.nShow = SW_HIDE;
		}

		ShExecInfo.hInstApp = nullptr;
		ShellExecuteExW(&ShExecInfo);
		WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
		CloseHandle(ShExecInfo.hProcess);
	}

	if (ConfigObjects.UnloadSoftRegOnCmd == TRUE) {
		if (Registry::loadSoftwareHive() != ERROR_SUCCESS) {
			MessageBoxW(MainObjects.hWndMainWindow, AppResStringsObjects.SoftwareHiveLoadError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
			exit(1);
		}
	}

	std::wstring updatefilecnf = MainObjects.driveletter;
	updatefilecnf.append(L"gr7updatefld\\UpdateFiles.conf");

	if (FileManagement::ProcessFileList(updatefilecnf, MainObjects.InstallPercentage)) {
		MessageBoxW(MainObjects.hWndMainWindow, AppResStringsObjects.UpdateFileListAccessError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
		exit(1);
	}

	MainObjects.InstallPercentage = MainObjects.InstallPercentage + 40;
	RedrawWindow(MainObjects.hWndMainWindow, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	std::wstring bufferreg = L"gr7Software\\Grass7\\CurrentVersion\\Updates\\";
	bufferreg.append(ConfigObjects.UpdateID);

	std::wstring UpdateFolder = MainObjects.driveletter;
	UpdateFolder.append(L"Windows\\Grass7Update\\");

	if(Grass7API::FileManagement::dirExists(UpdateFolder.c_str()) != 1) {
		CreateDirectoryW(UpdateFolder.c_str(), nullptr);
	}
	UpdateFolder.append(ConfigObjects.UpdateID + L".txt");

	std::wstring BufferFile = MainObjects.driveletter;
	BufferFile.append(L"gr7updatefld\\");
	BufferFile.append(ConfigObjects.InfoFile);

	LPCWSTR data = UpdateFolder.c_str();
	CopyFileW(BufferFile.c_str(),data,false);
	HKEY hkey;
	if (RegCreateKeyExW(HKEY_LOCAL_MACHINE, bufferreg.c_str(), 0, nullptr, 0, KEY_WRITE, nullptr, &hkey, nullptr) == ERROR_SUCCESS) {
		RegSetValueExW(hkey, L"InfoFile", 0, REG_SZ, (LPBYTE)data, 256);
		RegCloseKey(hkey);
	}

	if (ConfigObjects.LoadSysReg == TRUE) {
		if(Registry::unloadSystemHive() != 0) {
			MessageBoxW(MainObjects.hWndMainWindow, AppResStringsObjects.SystemHiveUnloadError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONWARNING);
		}
	}
	if (ConfigObjects.LoadDefaultReg == TRUE) {
		if(Registry::unloadDefaultHive() != 0) {
			MessageBoxW(MainObjects.hWndMainWindow, AppResStringsObjects.DefaultUserHiveLoadError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONWARNING);
		}
	}
	if (ConfigObjects.LoadSystemUserReg == TRUE) {
		if (Registry::unloadSystemUserHive() != 0) {
			MessageBoxW(MainObjects.hWndMainWindow, AppResStringsObjects.SystemUserHiveUnloadError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONWARNING);
		}
	}

	if (Registry::unloadSoftwareHive() != 0) {
		MessageBoxW(MainObjects.hWndMainWindow, AppResStringsObjects.SoftwareHiveUnloadError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONWARNING);
	}

	MainObjects.InstallPercentage = 100;
	RedrawWindow(MainObjects.hWndMainWindow, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	std::wstring system32dir = MainObjects.driveletter;
	system32dir.append(L"Windows\\System32");

	SetCurrentDirectoryW(system32dir.c_str());
	Grass7API::FileManagement::DeleteDirectory(tempfolder.c_str());
	Sleep(2000); // Here to make it look like its doing something
	exit(0);
}