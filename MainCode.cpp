// The actual updater code

#include "stdafx.h"
#include "Global.h"
#include "Registry.h"
#include "FileManagement.h"
#include "MainCode.h"
#include "GUIDraw.h"

int MainCodeClass::mainCode(HWND hProgressBar, HWND hWnd, wchar_t *hProgressText)
{
	Sleep(2000);
	if(MainObjects.driveletter == "") {
		MessageBoxW(NULL, AppResStringsObjects.NotInstalled.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
		exit(0);
	}
	RegistryClass::Init();
	wchar_t tempfolder[16] = { 0 };
	wcsncpy_s(tempfolder, MainObjects.driveletterW, sizeof(tempfolder));
	wcsncat_s(tempfolder, L"gr7updatefld", sizeof(tempfolder));
	int percentageCounter = 0;
	SetCurrentDirectoryW(tempfolder);
	percentageCounter = percentageCounter + 10;
	GUIDrawClass::updateProgressBar(percentageCounter, hProgressBar, hWnd, hProgressText);

	// We load and parse the config file
	// We have to do a diarrhea way of doing this, not proud of this one, there is likely a better way but i was very angry at the time that it didnt work so i went with this.
	std::wstring UpdateConfigFile = MainObjects.driveletterW;
	UpdateConfigFile.append(L"gr7updatefld\\Update.conf");
	std::ifstream ifs(UpdateConfigFile.c_str());

	std::string updateID = "UpdateID=";
	std::string arch = "arch=";
	std::string requiredupdate = "requiredupdate=";
	std::string OScmd = "OScommands=";
	std::string newUpdateLevel = "newUpdateLevel=";
	std::string newPatchLevel = "newPatchLevel=";
	std::string newBuildString = "newBuildString=";
	std::string UpdInfoFile = "InfoFile=";
	std::string cmdEnable = "commandsEnabled=";
	std::string cmdShow = "commandlineShow=";
	std::string unloadSoftRegOnCmd = "unloadSoftRegOnCmd=";
	std::string sysreg = "loadSysReg=";
	std::string defaultreg = "loadDefaultReg=";
	std::string sysuserreg = "loadSystemUserReg=";

	std::regex updateids(updateID + "\\b");
	std::regex archs(arch + "\\b");
	std::regex requiredupdates(requiredupdate + "\\b");
	std::regex OScmden(OScmd + "\\b");
	std::regex newUpdateLevelS(newUpdateLevel + "\\b");
	std::regex newPatchLevelS(newPatchLevel + "\\b");
	std::regex newBuildStringS(newBuildString + "\\b");
	std::regex updinfofile1(UpdInfoFile + "\\b");
	std::regex cmden(cmdEnable + "\\b");
	std::regex cmdsh(cmdShow + "\\b");
	std::regex unloadSoftRegOnCmdEnable(unloadSoftRegOnCmd + "\\b");
	std::regex sys(sysreg + "\\b");
	std::regex defaultr(defaultreg + "\\b");
	std::regex sysuser(sysuserreg + "\\b");

	std::string lineUpdateID;
	std::string lineArch;
	std::string lineRequiredupdate;
	std::string lineOScommands;
	std::string linenewUpdateLevel;
	std::string linenewPatchLevel;
	std::string linenewBuildString;
	std::string lineUpdInfoFile;
	std::string lineCmdEnable;
	std::string lineCmdShow;
	std::string lineUnloadRegSoftOnCmd;
	std::string lineSysReg;
	std::string lineDefaultReg;
	std::string lineSystemUserReg;

	percentageCounter = percentageCounter + 10;
	GUIDrawClass::updateProgressBar(percentageCounter, hProgressBar, hWnd, hProgressText);

	getline(ifs, lineUpdateID);
	if (regex_search(lineUpdateID, updateids)) {
		std::size_t pos = lineUpdateID.find("=");
		if (pos != std::string::npos)
		{
			lineUpdateID = lineUpdateID.substr(pos + 1);
		}
	}

	getline(ifs, lineArch);
	if (regex_search(lineArch, archs)) {
		std::size_t pos = lineArch.find("=");
		if (pos != std::string::npos)
		{
			lineArch = lineArch.substr(pos + 1);
		}
	}
	lineArch.clear();

	getline(ifs, lineRequiredupdate);
	if (regex_search(lineRequiredupdate, requiredupdates)) {
		std::size_t pos = lineRequiredupdate.find("=");
		if (pos != std::string::npos)
		{
			lineRequiredupdate = lineRequiredupdate.substr(pos + 1);
		}
	}
	lineRequiredupdate.clear();

	int enableOScommands = 0;
	getline(ifs, lineOScommands);
	if (regex_search(lineOScommands, OScmden)) {
		if (lineOScommands.find("true") != std::string::npos) {
			enableOScommands = 1;
		}
	}
	lineOScommands.clear();

	getline(ifs, linenewUpdateLevel);
	if (regex_search(linenewUpdateLevel, newUpdateLevelS)) {
		std::size_t pos = linenewUpdateLevel.find("=");
		if (pos != std::string::npos)
		{
			linenewUpdateLevel = linenewUpdateLevel.substr(pos + 1);
		}
	}
	getline(ifs, linenewPatchLevel);

	if (regex_search(linenewPatchLevel, newPatchLevelS)) {
		std::size_t pos = linenewPatchLevel.find("=");
		if (pos != std::string::npos)
		{
			linenewPatchLevel = linenewPatchLevel.substr(pos + 1);
		}
	}
	getline(ifs, linenewBuildString);

	if (regex_search(linenewBuildString, newBuildStringS)) {
		std::size_t pos = linenewBuildString.find("=");
		if (pos != std::string::npos)
		{
			linenewBuildString = linenewBuildString.substr(pos + 1);
		}
	}
	getline(ifs, lineUpdInfoFile);

	if (regex_search(lineUpdInfoFile, updinfofile1)) {
		std::size_t pos = lineUpdInfoFile.find("=");
		if (pos != std::string::npos)
		{
			lineUpdInfoFile = lineUpdInfoFile.substr(pos + 1);
		}
	}

	int enableCmd = 0;
	getline(ifs, lineCmdEnable);
	if (regex_search(lineCmdEnable, cmden)) {
		if (lineCmdEnable.find("true") != std::string::npos) {
			enableCmd = 1;
		}
	}
	lineCmdEnable.clear();

	int showCmd = 0;
	getline(ifs, lineCmdShow);
	if (regex_search(lineCmdShow, cmdsh)) {
		if (lineCmdShow.find("true") != std::string::npos) {
			showCmd = 1;
		}
	}
	lineCmdShow.clear();

	int UnloadSoftRegOnCmd = 0;
	getline(ifs, lineUnloadRegSoftOnCmd);
	if (regex_search(lineUnloadRegSoftOnCmd, unloadSoftRegOnCmdEnable)) {
		if (lineUnloadRegSoftOnCmd.find("true") != std::string::npos) {
			UnloadSoftRegOnCmd = 1;
		}
	}
	lineUnloadRegSoftOnCmd.clear();

	int loadgr7SysHive = 0;
	getline(ifs, lineSysReg);
	if (regex_search(lineSysReg, sys)) {
		if (lineSysReg.find("true") != std::string::npos) {
			loadgr7SysHive = 1;
		}
	}
	lineSysReg.clear();

	int loadgr7DefaultHive = 0;
	getline(ifs, lineDefaultReg);
	if (regex_search(lineDefaultReg, defaultr)) {
		if (lineDefaultReg.find("true") != std::string::npos) {
			loadgr7DefaultHive = 1;
		}
	}
	lineDefaultReg.clear();

	int loadgr7SystemUserHive = 0;
	getline(ifs, lineSystemUserReg);
	if (regex_search(lineSystemUserReg, sysuser)) {
		if (lineSystemUserReg.find("true") != std::string::npos) {
			loadgr7SystemUserHive = 1;
		}
	}
	lineSystemUserReg.clear();

	ifs.close();

	updateID.clear();
	arch.clear();
	requiredupdate.clear();
	OScmd.clear();
	newUpdateLevel.clear();
	newPatchLevel.clear();
	newBuildString.clear();
	UpdInfoFile.clear();
	cmdEnable.clear();
	cmdShow.clear();
	unloadSoftRegOnCmd.clear();
	sysreg.clear();
	defaultreg.clear();
	sysuserreg.clear();

	// Registry related stuff.

	if (RegistryClass::loadSoftwareHive() != ERROR_SUCCESS) {
		MessageBoxW(NULL, AppResStringsObjects.SoftwareHiveLoadError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
		exit(0);
	}

	HKEY hkey1d;

	LONG lResult1 = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"gr7Software\\Grass7\\CurrentVersion", 0, KEY_WRITE, &hkey1d);
	if (lResult1 != ERROR_SUCCESS)
	{
		MessageBoxW(NULL, AppResStringsObjects.FailToOpenRegistryKey.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
		linenewUpdateLevel.clear();
		linenewPatchLevel.clear();
		linenewBuildString.clear();
		exit(0);
	}

	if (linenewUpdateLevel.find("none") == std::string::npos) {
		LPCTSTR dat1 = Grass7API::Convert::convertchartoLPCWSTR(linenewUpdateLevel.c_str());
		RegSetValueExW(hkey1d, L"UpdateLevel", 0, REG_SZ, (LPBYTE)dat1, 256);
	}

	if (linenewPatchLevel.find("none") == std::string::npos) {
		LPCTSTR dat2 = Grass7API::Convert::convertchartoLPCWSTR(linenewPatchLevel.c_str());
		RegSetValueExW(hkey1d, L"PatchLevel", 0, REG_SZ, (LPBYTE)dat2, 256);
	}

	if (linenewBuildString.find("none") == std::string::npos) {
		LPCTSTR dat3 = Grass7API::Convert::convertchartoLPCWSTR(linenewBuildString.c_str());
		RegSetValueExW(hkey1d, L"BuildString", 0, REG_SZ, (LPBYTE)dat3, 256);
		std::string newBuildStr = linenewBuildString.substr(0, linenewBuildString.find("."));
		LPCTSTR dat4 = Grass7API::Convert::convertchartoLPCWSTR(newBuildStr.c_str());
		RegSetValueExW(hkey1d, L"CurrentBuild", 0, REG_SZ, (LPBYTE)dat4, 256);
	}

	RegCloseKey(hkey1d);

	linenewUpdateLevel.clear();
	linenewPatchLevel.clear();
	linenewBuildString.clear();

	if (loadgr7SysHive == 1) {
		if (RegistryClass::loadSystemHive() != ERROR_SUCCESS) {
			MessageBoxW(NULL, AppResStringsObjects.SystemHiveLoadError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
			exit(0);
		}
	}
	if (loadgr7DefaultHive == 1) {
		if (RegistryClass::loadDefaultHive() != ERROR_SUCCESS) {
			MessageBoxW(NULL, AppResStringsObjects.DefaultUserHiveLoadError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
			exit(0);
		}
	}
	if (loadgr7SystemUserHive == 1) {
		if (RegistryClass::loadSystemUserHive() != ERROR_SUCCESS) {
			MessageBoxW(NULL, AppResStringsObjects.SystemUserHiveLoadError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
			exit(0);
		}
	}

	if (UnloadSoftRegOnCmd == 1) {
		if (RegistryClass::unloadSoftwareHive() != 0) {
			MessageBoxW(NULL, AppResStringsObjects.SoftwareHiveUnloadError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONWARNING);
		}
	}

	if (enableCmd == 1) {
		std::wstring cmddlol = MainObjects.driveletterW;
		cmddlol.append(L"gr7updatefld\\commands.bat");

		SHELLEXECUTEINFO ShExecInfo;
		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		ShExecInfo.hwnd = NULL;
		ShExecInfo.lpVerb = L"open";
		ShExecInfo.lpFile = cmddlol.c_str();
		ShExecInfo.lpParameters = L"";
		ShExecInfo.lpDirectory = MainObjects.driveletterW;

		if (showCmd == 1) {
			ShExecInfo.nShow = SW_SHOW;
		}
		if (showCmd == 0) {
			ShExecInfo.nShow = SW_HIDE;
		}

		ShExecInfo.hInstApp = NULL;
		ShellExecuteExW(&ShExecInfo);
		WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
		CloseHandle(ShExecInfo.hProcess);
	}

	if (UnloadSoftRegOnCmd == 1) {
		if (RegistryClass::loadSoftwareHive() != ERROR_SUCCESS) {
			MessageBoxW(NULL, AppResStringsObjects.SoftwareHiveLoadError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
			exit(0);
		}
	}

	char *dr1;
	std::string line;
	char updatefilecnf[33] = { 0 };

	strncpy_s(updatefilecnf, MainObjects.driveletter, sizeof(updatefilecnf));
	strncat_s(updatefilecnf, "gr7updatefld\\UpdateFiles.conf", sizeof(updatefilecnf));
	std::ifstream file(updatefilecnf);
	memset(updatefilecnf, 0, sizeof(updatefilecnf));
	if (file.is_open()) {
		while (getline(file, line)) {
			dr1 = _strdup(MainObjects.driveletter);
			std::string destination1 = line;
			std::size_t pos = destination1.find(" - ");
			if (pos != std::string::npos) {
				destination1 = destination1.substr(pos+3);
			}
			std::string source1 = line.substr(0, line.find(" - "));
			std::wstring wide_string = std::wstring(destination1.begin(), destination1.end());
			std::wstring wide_string1 = std::wstring(source1.begin(), source1.end());
			destination1.clear();
			source1.clear();
			std::string bla1 = Grass7API::Convert::WStringToString(wide_string);
			wide_string.clear();
			std::string bla2 = Grass7API::Convert::WStringToString(wide_string1);
			wide_string1.clear();
			bla1.insert(0,"\\\\");
			bla2.insert(0,"\\\\");
			dr1[strlen(dr1) - 1] = 0;
			bla1.insert(0,dr1);
			bla2.insert(0,dr1);
			std::wstring dst1 = std::wstring(bla1.begin(), bla1.end());
			std::wstring src1 = std::wstring(bla2.begin(), bla2.end());
			bla1.clear();
			bla2.clear();

			const wchar_t* destination = dst1.c_str();
			const wchar_t* source = src1.c_str();

			CopyFileW(source,destination,false);
			dst1.clear();
			src1.clear();
			memset(dr1, 0, sizeof(dr1));
			if(percentageCounter != 40) {
				percentageCounter = percentageCounter + 1;
				GUIDrawClass::updateProgressBar(percentageCounter, hProgressBar, hWnd, hProgressText);
			}
		}
		file.close();
		line.clear();
	}
	else { 
		MessageBoxW(NULL, AppResStringsObjects.UpdateFileListAccessError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONERROR);
		exit(0);
	}

	percentageCounter = percentageCounter + 20;
	GUIDrawClass::updateProgressBar(percentageCounter, hProgressBar, hWnd, hProgressText);

	percentageCounter = percentageCounter + 20;
	GUIDrawClass::updateProgressBar(percentageCounter, hProgressBar, hWnd, hProgressText);

	std::wstring bufferreg = L"gr7Software\\Grass7\\CurrentVersion\\Updates\\";
	bufferreg.append(Grass7API::Convert::convertchar(lineUpdateID.c_str()));

	std::wstring UpdateFolder = MainObjects.driveletterW;
	UpdateFolder.append(L"Windows\\Grass7Update\\");

	if(Grass7API::FileManagement::dirExists(UpdateFolder.c_str()) != 1) {
		CreateDirectoryW(UpdateFolder.c_str(),NULL);
	}
	UpdateFolder.append(Grass7API::Convert::convertchar(lineUpdateID.c_str()));
	UpdateFolder.append(L".txt");

	std::wstring BufferFile = MainObjects.driveletterW;
	BufferFile.append(L"gr7updatefld\\");
	BufferFile.append(Grass7API::Convert::convertchar(lineUpdInfoFile.c_str()));

	LPCWSTR data = UpdateFolder.c_str();
	CopyFileW(BufferFile.c_str(),data,false);
	HKEY hkey;
	lineUpdateID.clear();
	if(RegCreateKeyExW(HKEY_LOCAL_MACHINE, bufferreg.c_str(), 0, NULL, 0, KEY_WRITE, NULL, &hkey, NULL) == ERROR_SUCCESS) {
		RegSetValueExW(hkey, L"InfoFile", 0, REG_SZ, (LPBYTE)data, 256);
		RegCloseKey(hkey);
	}

	if(loadgr7SysHive == 1) {
		if(RegistryClass::unloadSystemHive() != 0) {
			MessageBoxW(NULL, AppResStringsObjects.SystemHiveUnloadError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONWARNING);
		}
	}
	if(loadgr7DefaultHive == 1) {
		if(RegistryClass::unloadDefaultHive() != 0) {
			MessageBoxW(NULL, AppResStringsObjects.DefaultUserHiveLoadError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONWARNING);
		}
	}
	if(loadgr7SystemUserHive == 1) {
		if(RegistryClass::unloadSystemUserHive() != 0) {
			MessageBoxW(NULL, AppResStringsObjects.SystemUserHiveUnloadError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONWARNING);
		}
	}

	if (RegistryClass::unloadSoftwareHive() != 0) {
		MessageBoxW(NULL, AppResStringsObjects.SoftwareHiveUnloadError.c_str(), AppResStringsObjects.OSName.c_str(), MB_OK | MB_ICONWARNING);
	}

	percentageCounter = 100;
	GUIDrawClass::updateProgressBar(percentageCounter, hProgressBar, hWnd, hProgressText);

	// We clean our mess up.
	std::wstring system32dir = MainObjects.driveletterW;
	system32dir.append(L"Windows\\System32");

	SetCurrentDirectoryW(system32dir.c_str());
	Grass7API::FileManagement::DeleteDirectory(tempfolder);
	memset(tempfolder, 0, sizeof(tempfolder));
	memset(hProgressText, 0, sizeof(hProgressText));
	Sleep(2000); // Here to make it look like its doing something, program runs way too fast, usually
	exit(0);

	return 0;
}
