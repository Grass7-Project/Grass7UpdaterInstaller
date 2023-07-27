// Registry related functions

#include "stdafx.h"
#include "Registry.h"
#include "FileManagement.h"

const char *driveletter = Getgr7DriveLetter();
const wchar_t *lpSystemKey = L"gr7System";
const wchar_t *lpSoftwareKey = L"gr7Software";
const wchar_t *lpDefaultKey = L"gr7Default";
const wchar_t *lpSystemUserKey = L"gr7SystemUser";

LONG loadSystemHive()
{
	wchar_t *HiveFile = L"Windows\\System32\\config\\SYSTEM";
	wchar_t lpSysHiveFile[MAX_PATH] = { 0 };
	wcsncpy_s(lpSysHiveFile, gr7::convertchar(driveletter), sizeof(lpSysHiveFile));
	wcsncat_s(lpSysHiveFile, HiveFile, sizeof(lpSysHiveFile));
	LONG   hSystemKey;
	hSystemKey = RegLoadKeyW(HKEY_LOCAL_MACHINE,lpSystemKey,lpSysHiveFile);
	memset(lpSysHiveFile, 0, sizeof(lpSysHiveFile));
	return hSystemKey;
}

LONG loadSoftwareHive()
{
#ifdef _DEBUG
	wchar_t *HiveFile = L"FF1\\SOFTWARE";
#else
	wchar_t *HiveFile = L"Windows\\System32\\config\\SOFTWARE";
#endif
	wchar_t lpSoftwareHiveFile[MAX_PATH] = { 0 };
	wcsncpy_s(lpSoftwareHiveFile, gr7::convertchar(driveletter), sizeof(lpSoftwareHiveFile));
	wcsncat_s(lpSoftwareHiveFile, HiveFile, sizeof(lpSoftwareHiveFile));
	LONG   hSoftwareKey;
	hSoftwareKey = RegLoadKeyW(HKEY_LOCAL_MACHINE,lpSoftwareKey,lpSoftwareHiveFile);
	memset(lpSoftwareHiveFile, 0, sizeof(lpSoftwareHiveFile));
	return hSoftwareKey;
}

LONG loadDefaultHive()
{
	wchar_t *HiveFile = L"Windows\\System32\\config\\DEFAULT";
	wchar_t lpDefaultHiveFile[MAX_PATH] = { 0 };
	wcsncpy_s(lpDefaultHiveFile, gr7::convertchar(driveletter), sizeof(lpDefaultHiveFile));
	wcsncat_s(lpDefaultHiveFile, HiveFile, sizeof(lpDefaultHiveFile));
	LONG   hDefaultKey;
	hDefaultKey = RegLoadKeyW(HKEY_LOCAL_MACHINE,lpDefaultKey,lpDefaultHiveFile);
	memset(lpDefaultHiveFile, 0, sizeof(lpDefaultHiveFile));
	return hDefaultKey;
}

LONG loadSystemUserHive()
{
	wchar_t *HiveFile = L"Windows\\System32\\config\\systemprofile\\ntuser.dat";
	wchar_t lpSystemUserHiveFile[MAX_PATH] = { 0 };
	wcsncpy_s(lpSystemUserHiveFile, gr7::convertchar(driveletter), sizeof(lpSystemUserHiveFile));
	wcsncat_s(lpSystemUserHiveFile, HiveFile, sizeof(lpSystemUserHiveFile));
	LONG   hSystemUserKey;
	hSystemUserKey = RegLoadKeyW(HKEY_LOCAL_MACHINE,lpSystemUserKey,lpSystemUserHiveFile);
	memset(lpSystemUserHiveFile, 0, sizeof(lpSystemUserHiveFile));
	return hSystemUserKey;
}

bool unloadSystemHive()
{
	bool err;
	err = (RegUnLoadKeyW(HKEY_LOCAL_MACHINE,lpSystemKey) != 0);
	return err;
}

bool unloadSoftwareHive()
{
	bool err;
	err = (RegUnLoadKeyW(HKEY_LOCAL_MACHINE,lpSoftwareKey) != 0);
	return err;
}

bool unloadDefaultHive()
{
	bool err;
	err = (RegUnLoadKeyW(HKEY_LOCAL_MACHINE,lpDefaultKey) != 0);
	return err;
}

bool unloadSystemUserHive()
{
	bool err;
	err = (RegUnLoadKeyW(HKEY_LOCAL_MACHINE,lpSystemUserKey) != 0);
	return err;
}