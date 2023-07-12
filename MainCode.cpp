// The actual updater code

#include "stdafx.h"
#include "Registry.h"
#include "FileManagement.h"
#include "MainCode.h"
#include "GUIDraw.h"

int mainCode(HWND hProgressBar, HWND hWnd, wchar_t *hProgressText)
{
	Sleep(2000);
	const char *driveletter = Getgr7DriveLetter();
	if(driveletter == "") {
		MessageBox(NULL, gr7::LoadStringToW(GetModuleHandle(NULL),IDS_NOT_INSTALLED), gr7::LoadStringToW(GetModuleHandle(NULL),IDS_OSNAME), MB_OK | MB_ICONERROR);
		exit(0);
	}
	char tempfolder[16];
	strncpy_s(tempfolder, driveletter, sizeof(tempfolder));
	strncat_s(tempfolder, "gr7updatefld", sizeof(tempfolder));
	int percentageCounter = 0;
	std::string line;
	char updatefilecnf[33];
	strncpy_s(updatefilecnf, driveletter, sizeof(updatefilecnf));
	strncat_s(updatefilecnf, "gr7updatefld\\UpdateFiles.conf", sizeof(updatefilecnf));
	SetCurrentDirectory(gr7::convertchar(tempfolder));
	char *dr1;
	percentageCounter = percentageCounter + 10;
	updateProgressBar(percentageCounter, hProgressBar, hWnd, hProgressText);
	std::ifstream file(updatefilecnf);
	memset(updatefilecnf, 0, sizeof(updatefilecnf));
	if (file.is_open()) {
		while (getline(file, line)) {
			dr1 = _strdup(driveletter);
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
			std::string bla1 = gr7::WStringToString(wide_string);
			wide_string.clear();
			std::string bla2 = gr7::WStringToString(wide_string1);
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

			CopyFile(source,destination,false);
			dst1.clear();
			src1.clear();
			memset(dr1, 0, sizeof(dr1));
			if(percentageCounter != 40) {
				percentageCounter = percentageCounter + 1;
				updateProgressBar(percentageCounter, hProgressBar, hWnd, hProgressText);
			}
		}
		file.close();
		line.clear();
	}
	else { 
		MessageBox(NULL, gr7::LoadStringToW(GetModuleHandle(NULL),IDS_FILE_LIST_ACCESS_ERROR), gr7::LoadStringToW(GetModuleHandle(NULL),IDS_OSNAME), MB_OK | MB_ICONERROR);
		exit(0);
	}
	if (loadSoftwareHive() != ERROR_SUCCESS) {
		MessageBox(NULL, gr7::LoadStringToW(GetModuleHandle(NULL),IDS_SOFT_HIVE_LOAD_ERROR), gr7::LoadStringToW(GetModuleHandle(NULL),IDS_OSNAME), MB_OK | MB_ICONERROR);
		exit(0);
	}
	// We load and parse the config file
	// We have to do a diarrhea way of doing this, not proud of this one, there is likely a better way but i was very angry at the time that it didnt work so i did diarrhea.
	char bufferpf[28];
	strncpy_s(bufferpf, driveletter, sizeof(bufferpf));
	strncat_s(bufferpf, "gr7updatefld\\Update.conf", sizeof(bufferpf));
	std::ifstream ifs(bufferpf);
	memset(bufferpf, 0, sizeof(bufferpf));
	std::string updateID = "UpdateID=";
	std::string arch = "arch=";
	std::string requiredupdate = "requiredupdate=";
	std::string newUpdateLevel = "newUpdateLevel=";
	std::string newPatchLevel = "newPatchLevel=";
	std::string newBuildString = "newBuildString=";
	std::string UpdInfoFile = "InfoFile=";
	std::string cmdEnable = "commandsEnabled=";
	std::string sysreg = "loadSysReg=";
	std::string defaultreg = "loadDefaultReg=";
	std::string sysuserreg = "loadSystemUserReg=";
	std::regex sys (sysreg + "\\b");
	std::regex defaultr (defaultreg + "\\b");
	std::regex sysuser (sysuserreg + "\\b");
	std::regex updateids (updateID + "\\b");
	std::regex archs (arch + "\\b");
	std::regex updinfofile1 (UpdInfoFile + "\\b");
	std::regex cmden (cmdEnable + "\\b");
	std::regex requiredupdates(requiredupdate + "\\b");
	std::regex newUpdateLevelS(newUpdateLevel + "\\b");
	std::regex newPatchLevelS(newPatchLevel + "\\b");
	std::regex newBuildStringS(newBuildString + "\\b");

	std::string lineUpdateID;
	std::string lineArch;
	std::string lineUpdInfoFile;
	std::string lineCmdEnable;
	std::string lineSysReg;
	std::string lineDefaultReg;
	std::string lineSystemUserReg;
	std::string lineRequiredupdate;
	std::string linenewUpdateLevel;
	std::string linenewPatchLevel;
	std::string linenewBuildString;

	percentageCounter = percentageCounter + 10;
	updateProgressBar(percentageCounter, hProgressBar, hWnd, hProgressText);

	getline(ifs, lineUpdateID );
	if( regex_search( lineUpdateID, updateids) ) {
		std::size_t pos = lineUpdateID.find("=");
		if(pos != std::string::npos)
		{
			lineUpdateID = lineUpdateID.substr(pos+1);
		}
	}
	getline(ifs, lineArch );
	if( regex_search( lineArch, archs) ) {
		std::size_t pos = lineArch.find("=");
		if(pos != std::string::npos)
		{
			lineArch = lineArch.substr(pos+1);
		}
	}
	lineArch.clear();
	getline(ifs, lineRequiredupdate );
	if( regex_search( lineRequiredupdate, requiredupdates) ) {
		std::size_t pos = lineRequiredupdate.find("=");
		if(pos != std::string::npos)
		{
			lineRequiredupdate = lineRequiredupdate.substr(pos+1);
		}
	}
	lineRequiredupdate.clear();
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
	getline(ifs, lineUpdInfoFile );
	if( regex_search( lineUpdInfoFile, updinfofile1) ) {
		std::size_t pos = lineUpdInfoFile.find("=");
		if(pos != std::string::npos)
		{
			lineUpdInfoFile = lineUpdInfoFile.substr(pos+1);
		}
	}
	int enableCmd = 0;
	getline(ifs, lineCmdEnable );
	if( regex_search( lineCmdEnable, cmden) ) {
		if(lineCmdEnable.find("true") != std::string::npos) {
			enableCmd = 1;
		}
	}
	lineCmdEnable.clear();
	int loadgr7SysHive = 0;
	getline(ifs, lineSysReg );
	if ( regex_search( lineSysReg, sys) ) {
		if (lineSysReg.find("true") != std::string::npos) {
			loadgr7SysHive = 1;
		}
	}
	lineSysReg.clear();
	int loadgr7DefaultHive = 0;
	getline(ifs, lineDefaultReg );
	if ( regex_search( lineDefaultReg, defaultr) ) {
		if (lineDefaultReg.find("true") != std::string::npos) {
			loadgr7DefaultHive = 1;
		}
	}
	lineDefaultReg.clear();
	int loadgr7SystemUserHive = 0;
	getline(ifs, lineSystemUserReg );
	if ( regex_search( lineSystemUserReg, sysuser) ) {
		if (lineSystemUserReg.find("true") != std::string::npos) {
			loadgr7SystemUserHive = 1;
		}
	}
	lineSystemUserReg.clear();
	ifs.close();

	updateID.clear();
	arch.clear();
	requiredupdate.clear();
	UpdInfoFile.clear();
	cmdEnable.clear();
	sysreg.clear();
	defaultreg.clear();
	sysuserreg.clear();
	newUpdateLevel.clear();
	newPatchLevel.clear();
	newBuildString.clear();

	percentageCounter = percentageCounter + 20;
	updateProgressBar(percentageCounter, hProgressBar, hWnd, hProgressText);

	// Registry related stuff.

	HKEY hkey1d;

	LONG lResult1 = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("gr7Software\\Grass7\\CurrentVersion"), 0, KEY_WRITE, &hkey1d);
	if (lResult1 != ERROR_SUCCESS)
	{
		MessageBox(NULL, gr7::LoadStringToW(GetModuleHandle(NULL), IDS_FAIL_OPEN_KEY), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_OSNAME), MB_OK | MB_ICONERROR);
		linenewUpdateLevel.clear();
		linenewPatchLevel.clear();
		linenewBuildString.clear();
		exit(0);
	}

	if (linenewUpdateLevel.find("none") == std::string::npos) {
		LPCTSTR dat1 = gr7::convertchartoLPCWSTR(linenewUpdateLevel.c_str());
		RegSetValueEx(hkey1d, _T("UpdateLevel"), 0, REG_SZ, (LPBYTE)dat1, 256);
	}

	if (linenewPatchLevel.find("none") == std::string::npos) {
		LPCTSTR dat2 = gr7::convertchartoLPCWSTR(linenewPatchLevel.c_str());
		RegSetValueEx(hkey1d, _T("PatchLevel"), 0, REG_SZ, (LPBYTE)dat2, 256);
	}

	if (linenewBuildString.find("none") == std::string::npos) {
		LPCTSTR dat3 = gr7::convertchartoLPCWSTR(linenewBuildString.c_str());
		RegSetValueEx(hkey1d, _T("BuildString"), 0, REG_SZ, (LPBYTE)dat3, 256);
		std::string newBuildStr = linenewBuildString.substr(0, linenewBuildString.find("."));
		LPCTSTR dat4 = gr7::convertchartoLPCWSTR(newBuildStr.c_str());
		RegSetValueEx(hkey1d, _T("CurrentBuild"), 0, REG_SZ, (LPBYTE)dat4, 256);
	}

	RegCloseKey(hkey1d);

	linenewUpdateLevel.clear();
	linenewPatchLevel.clear();
	linenewBuildString.clear();

	if(loadgr7SysHive == 1) {
		if (loadSystemHive() != ERROR_SUCCESS) {
			MessageBox(NULL, gr7::LoadStringToW(GetModuleHandle(NULL),IDS_SYS_HIVE_LOAD_ERROR), gr7::LoadStringToW(GetModuleHandle(NULL),IDS_OSNAME), MB_OK | MB_ICONERROR);
			exit(0);
		}
	}
	if(loadgr7DefaultHive == 1) {
		if (loadDefaultHive() != ERROR_SUCCESS) {
			MessageBox(NULL, gr7::LoadStringToW(GetModuleHandle(NULL),IDS_DEF_HIVE_LOAD_ERROR), gr7::LoadStringToW(GetModuleHandle(NULL),IDS_OSNAME), MB_OK | MB_ICONERROR);
			exit(0);
		}
	}
	if(loadgr7SystemUserHive == 1) {
		if (loadSystemUserHive() != ERROR_SUCCESS) {
			MessageBox(NULL, gr7::LoadStringToW(GetModuleHandle(NULL),IDS_SYS_USR_HIVE_ERROR), gr7::LoadStringToW(GetModuleHandle(NULL),IDS_OSNAME), MB_OK | MB_ICONERROR);
			exit(0);
		}
	}
	if(enableCmd == 1) {
		char bufferpf5[256];
		strncpy_s(bufferpf5, "cd ", sizeof(bufferpf5));
		strncat_s(bufferpf5, driveletter, sizeof(bufferpf5));
		strncat_s(bufferpf5, "gr7updatefld\\commands.bat", sizeof(bufferpf5));
		wchar_t * cmddlol = (wchar_t *)gr7::convertchartoLPCWSTR(bufferpf5);
		memset(bufferpf5, 0, sizeof(bufferpf5));
		ShellExecute(NULL, NULL, _T("cmd.exe"), cmddlol, NULL, SW_HIDE);
	}

	percentageCounter = percentageCounter + 20;
	updateProgressBar(percentageCounter, hProgressBar, hWnd, hProgressText);

	char bufferreg[256];
	char bufferreg2[256];
	char bufferfile1[31];

	strncpy_s(bufferreg, "gr7Software\\Grass7\\CurrentVersion\\Updates\\", sizeof(bufferreg));
	strncat_s(bufferreg, lineUpdateID.c_str(), sizeof(bufferreg));
	strncpy_s(bufferreg2, driveletter, sizeof(bufferreg2));
	strncat_s(bufferreg2, "Windows\\Grass7Update\\", sizeof(bufferreg2));
	if(gr7::dirExists(bufferreg2) != 1) {
		CreateDirectory(gr7::convertchartoLPCWSTR(bufferreg2),NULL);
	}
	strncat_s(bufferreg2, lineUpdateID.c_str(), sizeof(bufferreg2));
	strncat_s(bufferreg2, ".txt", sizeof(bufferreg2));
	strncpy_s(bufferfile1, driveletter, sizeof(bufferfile1));
	strncat_s(bufferfile1, "gr7updatefld", sizeof(bufferfile1));
	strncat_s(bufferfile1, "\\", sizeof(bufferfile1));
	strncat_s(bufferfile1, lineUpdInfoFile.c_str(), sizeof(bufferfile1));
	LPCTSTR data = gr7::convertchartoLPCWSTR(bufferreg2);
	memset(bufferreg2, 0, sizeof(bufferreg2));
	CopyFile(gr7::convertchartoLPCWSTR(bufferfile1),data,false);
	memset(bufferfile1, 0, sizeof(bufferfile1));
	HKEY hkey;
	lineUpdateID.clear();
	if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, gr7::convertchartoLPCWSTR(bufferreg), 0, NULL, 0, KEY_WRITE, NULL, &hkey, NULL) == ERROR_SUCCESS) {
		RegSetValueEx(hkey, _T("InfoFile"), 0, REG_SZ, (LPBYTE)data, 256);
		RegCloseKey(hkey);
	}
	memset(bufferreg, 0, sizeof(bufferreg));

	if(loadgr7SysHive == 1) {
		if(unloadSystemHive() != 0) {
			MessageBox(NULL, gr7::LoadStringToW(GetModuleHandle(NULL),IDS_SYS_HIVE_UNLOAD_ERROR), gr7::LoadStringToW(GetModuleHandle(NULL),IDS_OSNAME), MB_OK | MB_ICONWARNING);
		}
	}
	if(loadgr7DefaultHive == 1) {
		if(unloadDefaultHive() != 0) {
			MessageBox(NULL, gr7::LoadStringToW(GetModuleHandle(NULL),IDS_DEF_HIVE_UNLOAD_ERROR), gr7::LoadStringToW(GetModuleHandle(NULL),IDS_OSNAME), MB_OK | MB_ICONWARNING);
		}
	}
	if(loadgr7SystemUserHive == 1) {
		if(unloadSystemUserHive() != 0) {
			MessageBox(NULL, gr7::LoadStringToW(GetModuleHandle(NULL),IDS_SYS_USR_HIVE_UNLOAD_ERROR), gr7::LoadStringToW(GetModuleHandle(NULL),IDS_OSNAME), MB_OK | MB_ICONWARNING);
		}
	}

	if (unloadSoftwareHive() != 0) {
		MessageBox(NULL, gr7::LoadStringToW(GetModuleHandle(NULL), IDS_SOFT_HIVE_UNLOAD_ERROR), gr7::LoadStringToW(GetModuleHandle(NULL), IDS_OSNAME), MB_OK | MB_ICONWARNING);
	}

	percentageCounter = 100;
	updateProgressBar(percentageCounter, hProgressBar, hWnd, hProgressText);

	// We clean our mess up.
	char bufferpg[20];
	strncpy_s(bufferpg, driveletter, sizeof(bufferpg));
	strncat_s(bufferpg, "Windows\\System32", sizeof(bufferpg));
	SetCurrentDirectory(gr7::convertchar(bufferpg));
	memset(bufferpg, 0, sizeof(bufferpg));
	gr7::DeleteDirectory(gr7::convertchar(tempfolder));
	memset(tempfolder, 0, sizeof(tempfolder));
	memset(hProgressText, 0, sizeof(hProgressText));
	Sleep(2000); // Here to make it look like its doing something, program runs way too fast.
	exit(0);

	return 0;
}
