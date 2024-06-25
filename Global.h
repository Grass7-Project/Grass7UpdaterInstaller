#pragma once

// Main Class
class GlobalMain {
public:
	HWND hWndMainWindow;
	HINSTANCE hInst;
	std::string driveletter;
	std::wstring driveletterW;
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
};

extern GlobalMain MainObjects;
extern GlobalAppResStrings AppResStringsObjects;