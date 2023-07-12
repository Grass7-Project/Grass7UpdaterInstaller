// Registry related functions

#include "stdafx.h"
#include "Registry.h"
#include "FileManagement.h"

const char *driveletter = Getgr7DriveLetter();
const wchar_t *lpSystemKey = _T("gr7System");
const wchar_t *lpSoftwareKey = _T("gr7Software");
const wchar_t *lpDefaultKey = _T("gr7Default");
const wchar_t *lpSystemUserKey = _T("gr7SystemUser");

LONG loadSystemHive()
{
	const char *HiveFile = "Windows\\System32\\config\\SYSTEM";
	char hivepath[MAX_PATH];
	strncpy_s(hivepath, driveletter, sizeof(hivepath));
	strncat_s(hivepath, HiveFile, sizeof(hivepath));
	LPCWSTR lpSysHiveFile = gr7::convertchartoLPCWSTR(hivepath);
	memset(hivepath, 0, sizeof(hivepath));
	LONG   hSystemKey;
	hSystemKey = RegLoadKey(HKEY_LOCAL_MACHINE,lpSystemKey,lpSysHiveFile);
	return hSystemKey;
}

LONG loadSoftwareHive()
{
#ifdef _DEBUG
	const char *HiveFile = "FF1\\SOFTWARE";
#else
	const char *HiveFile = "Windows\\System32\\config\\SOFTWARE";
#endif
	char hivepath[MAX_PATH];
	strncpy_s(hivepath, driveletter, sizeof(hivepath));
	strncat_s(hivepath, HiveFile, sizeof(hivepath));
	LPCWSTR lpSoftwareHiveFile = gr7::convertchartoLPCWSTR(hivepath);
	memset(hivepath, 0, sizeof(hivepath));
	LONG   hSoftwareKey;
	hSoftwareKey = RegLoadKey(HKEY_LOCAL_MACHINE,lpSoftwareKey,lpSoftwareHiveFile);
	return hSoftwareKey;
}

LONG loadDefaultHive()
{
	const char *HiveFile = "Windows\\System32\\config\\DEFAULT";
	char hivepath[MAX_PATH];
	strncpy_s(hivepath, driveletter, sizeof(hivepath));
	strncat_s(hivepath, HiveFile, sizeof(hivepath));
	LPCWSTR lpDefaultHiveFile = gr7::convertchartoLPCWSTR(hivepath);
	memset(hivepath, 0, sizeof(hivepath));
	LONG   hDefaultKey;
	hDefaultKey = RegLoadKey(HKEY_LOCAL_MACHINE,lpDefaultKey,lpDefaultHiveFile);
	return hDefaultKey;
}

LONG loadSystemUserHive()
{
	const char *HiveFile = "Windows\\System32\\config\\systemprofile\\ntuser.dat";
	char hivepath[MAX_PATH];
	strncpy_s(hivepath, driveletter, sizeof(hivepath));
	strncat_s(hivepath, HiveFile, sizeof(hivepath));
	LPCWSTR lpSystemUserHiveFile = gr7::convertchartoLPCWSTR(hivepath);
	memset(hivepath, 0, sizeof(hivepath));
	LONG   hSystemUserKey;
	hSystemUserKey = RegLoadKey(HKEY_LOCAL_MACHINE,lpSystemUserKey,lpSystemUserHiveFile);
	return hSystemUserKey;
}

bool unloadSystemHive()
{
	bool err;
	err = (RegUnLoadKey(HKEY_LOCAL_MACHINE,lpSystemKey) != 0);
	return err;
}

bool unloadSoftwareHive()
{
	bool err;
	err = (RegUnLoadKey(HKEY_LOCAL_MACHINE,lpSoftwareKey) != 0);
	return err;
}

bool unloadDefaultHive()
{
	bool err;
	err = (RegUnLoadKey(HKEY_LOCAL_MACHINE,lpDefaultKey) != 0);
	return err;
}

bool unloadSystemUserHive()
{
	bool err;
	err = (RegUnLoadKey(HKEY_LOCAL_MACHINE,lpSystemUserKey) != 0);
	return err;
}