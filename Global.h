#pragma once

// Main Class
class GlobalMain {
public:
	HINSTANCE hInst;
};

// Application Resource Strings
class GlobalAppResStrings {
public:
	wchar_t *OSName;
	wchar_t *PrivilageError;
	wchar_t *NotInstalled;
	wchar_t *Installing;
	wchar_t *SystemHiveLoadError;
	wchar_t *DefaultUserHiveLoadError;
	wchar_t *SystemUserHiveLoadError;
	wchar_t *SystemHiveUnloadError;
	wchar_t *DefaultUserHiveUnloadError;
	wchar_t *SystemUserHiveUnloadError;
	wchar_t *SoftwareHiveLoadError;
	wchar_t *SoftwareHiveUnloadError;
	wchar_t *UpdateFileListAccessError;
	wchar_t *FailToOpenRegistryKey;
};

extern GlobalMain MainObjects;
extern GlobalAppResStrings AppResStringsObjects;