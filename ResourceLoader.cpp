#include "stdafx.h"
#include "ResourceLoader.h"
#include "Global.h"

void ResourceLoader::LoadStrings()
{
	std::wstring OSName(MAX_PATH, 0);
	std::wstring PrivilageError(MAX_PATH, 0);
	std::wstring NotInstalled(MAX_PATH, 0);
	std::wstring Installing(MAX_PATH, 0);
	std::wstring SoftwareHiveLoadError(MAX_PATH, 0);
	std::wstring SystemHiveLoadError(MAX_PATH, 0);
	std::wstring DefaultUserHiveLoadError(MAX_PATH, 0);
	std::wstring SystemUserHiveLoadError(MAX_PATH, 0);
	std::wstring SoftwareHiveUnloadError(MAX_PATH, 0);
	std::wstring DefaultUserHiveUnloadError(MAX_PATH, 0);
	std::wstring SystemHiveUnloadError(MAX_PATH, 0);
	std::wstring UpdateFileListAccessError(MAX_PATH, 0);
	std::wstring FailToOpenRegistryKey(MAX_PATH, 0);

	OSName.resize((size_t)LoadStringW(MainObjects.hInst, IDS_OSNAME, &OSName[0], (int)OSName.size()));
	PrivilageError.resize((size_t)LoadStringW(MainObjects.hInst, IDS_PRIVILAGE_ERROR, &PrivilageError[0], (int)PrivilageError.size()));
	NotInstalled.resize((size_t)LoadStringW(MainObjects.hInst, IDS_NOT_INSTALLED, &NotInstalled[0], (int)NotInstalled.size()));
	Installing.resize((size_t)LoadStringW(MainObjects.hInst, IDS_INSTALLING, &Installing[0], (int)Installing.size()));
	SoftwareHiveLoadError.resize((size_t)LoadStringW(MainObjects.hInst, IDS_SOFT_HIVE_LOAD_ERROR, &SoftwareHiveLoadError[0], (int)SoftwareHiveLoadError.size()));
	SystemHiveLoadError.resize((size_t)LoadStringW(MainObjects.hInst, IDS_SYS_HIVE_LOAD_ERROR, &SystemHiveLoadError[0], (int)SystemHiveLoadError.size()));
	DefaultUserHiveLoadError.resize((size_t)LoadStringW(MainObjects.hInst, IDS_DEF_HIVE_LOAD_ERROR, &DefaultUserHiveLoadError[0], (int)DefaultUserHiveLoadError.size()));
	SystemUserHiveLoadError.resize((size_t)LoadStringW(MainObjects.hInst, IDS_SYS_USR_HIVE_ERROR, &SystemUserHiveLoadError[0], (int)SystemUserHiveLoadError.size()));
	SoftwareHiveUnloadError.resize((size_t)LoadStringW(MainObjects.hInst, IDS_SOFT_HIVE_UNLOAD_ERROR, &SoftwareHiveUnloadError[0], (int)SoftwareHiveUnloadError.size()));
	DefaultUserHiveUnloadError.resize((size_t)LoadStringW(MainObjects.hInst, IDS_DEF_HIVE_UNLOAD_ERROR, &DefaultUserHiveUnloadError[0], (int)DefaultUserHiveUnloadError.size()));
	SystemHiveUnloadError.resize((size_t)LoadStringW(MainObjects.hInst, IDS_SYS_HIVE_UNLOAD_ERROR, &SystemHiveUnloadError[0], (int)SystemHiveUnloadError.size()));
	UpdateFileListAccessError.resize((size_t)LoadStringW(MainObjects.hInst, IDS_FILE_LIST_ACCESS_ERROR, &UpdateFileListAccessError[0], (int)UpdateFileListAccessError.size()));
	FailToOpenRegistryKey.resize((size_t)LoadStringW(MainObjects.hInst, IDS_FAIL_OPEN_KEY, &FailToOpenRegistryKey[0], (int)FailToOpenRegistryKey.size()));

	AppResStringsObjects.OSName = OSName;
	AppResStringsObjects.PrivilageError = PrivilageError;
	AppResStringsObjects.NotInstalled = NotInstalled;
	AppResStringsObjects.Installing = Installing;
	AppResStringsObjects.SoftwareHiveLoadError = SoftwareHiveLoadError;
	AppResStringsObjects.SystemHiveLoadError = SystemHiveLoadError;
	AppResStringsObjects.DefaultUserHiveLoadError = DefaultUserHiveLoadError;
	AppResStringsObjects.SystemUserHiveLoadError = SystemUserHiveLoadError;
	AppResStringsObjects.SoftwareHiveUnloadError = SoftwareHiveUnloadError;
	AppResStringsObjects.DefaultUserHiveUnloadError = DefaultUserHiveUnloadError;
	AppResStringsObjects.SystemHiveUnloadError = SystemHiveUnloadError;
	AppResStringsObjects.UpdateFileListAccessError = UpdateFileListAccessError;
	AppResStringsObjects.FailToOpenRegistryKey = FailToOpenRegistryKey;
}