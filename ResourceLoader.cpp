#include "stdafx.h"
#include "ResourceLoader.h"

void ResourceLoader::LoadStrings()
{
	InternalLoadString(AppResStringsObjects.OSName, IDS_OSNAME);
	InternalLoadString(AppResStringsObjects.PrivilageError, IDS_PRIVILAGE_ERROR);
	InternalLoadString(AppResStringsObjects.NotInstalled, IDS_NOT_INSTALLED);
	InternalLoadString(AppResStringsObjects.Installing, IDS_INSTALLING);
	InternalLoadString(AppResStringsObjects.SoftwareHiveLoadError, IDS_SOFT_HIVE_LOAD_ERROR);
	InternalLoadString(AppResStringsObjects.SystemHiveLoadError, IDS_SYS_HIVE_LOAD_ERROR);
	InternalLoadString(AppResStringsObjects.DefaultUserHiveLoadError, IDS_DEF_HIVE_LOAD_ERROR);
	InternalLoadString(AppResStringsObjects.SystemUserHiveLoadError, IDS_SYS_USR_HIVE_ERROR);
	InternalLoadString(AppResStringsObjects.SoftwareHiveUnloadError, IDS_SOFT_HIVE_UNLOAD_ERROR);
	InternalLoadString(AppResStringsObjects.DefaultUserHiveUnloadError, IDS_DEF_HIVE_UNLOAD_ERROR);
	InternalLoadString(AppResStringsObjects.SystemHiveUnloadError, IDS_SYS_HIVE_UNLOAD_ERROR);
	InternalLoadString(AppResStringsObjects.UpdateFileListAccessError, IDS_FILE_LIST_ACCESS_ERROR);
	InternalLoadString(AppResStringsObjects.FailToOpenRegistryKey, IDS_FAIL_OPEN_KEY);
	InternalLoadString(AppResStringsObjects.ConfigAccessError, IDS_CONFIG_ACCESS_ERROR);
}

void ResourceLoader::InternalLoadString(std::wstring &strReturn, UINT uID)
{
	std::wstring strTemp(MAX_PATH, 0);
	strTemp.resize((size_t)LoadStringW(MainObjects.hInst, uID, &strTemp[0], (int)strTemp.size()));
	strReturn = strTemp;
	strTemp.clear();
}