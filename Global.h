#pragma once

// Main Class
class GlobalMain {
public:
	HWND hWndMainWindow;
	HINSTANCE hInst;
	std::wstring driveletter;
	int InstallPercentage;
};

// Application Resource Strings
class GlobalAppResStrings {
public:
	std::wstring OSName;
	std::wstring PrivilageError;
	std::wstring NotInstalled;
	std::wstring Installing;
	std::wstring SystemHiveLoadError;
	std::wstring DefaultUserHiveLoadError;
	std::wstring SystemUserHiveLoadError;
	std::wstring SystemHiveUnloadError;
	std::wstring DefaultUserHiveUnloadError;
	std::wstring SystemUserHiveUnloadError;
	std::wstring SoftwareHiveLoadError;
	std::wstring SoftwareHiveUnloadError;
	std::wstring UpdateFileListAccessError;
	std::wstring FailToOpenRegistryKey;
	std::wstring ConfigAccessError;
};

class GlobalConfig {
public:
	std::wstring UpdateID;
	std::wstring Architecture;
	std::wstring RequiredUpdate;
	int OSCommands;
	std::wstring NewUpdateLevel;
	std::wstring NewPatchLevel;
	std::wstring NewBuildString;
	std::wstring InfoFile;
	int CommandsEnabled;
	int CommandlineShow;
	int UnloadSoftRegOnCmd;
	int LoadSysReg;
	int LoadDefaultReg;
	int LoadSystemUserReg;
};

extern GlobalMain MainObjects;
extern GlobalAppResStrings AppResStringsObjects;
extern GlobalConfig ConfigObjects;