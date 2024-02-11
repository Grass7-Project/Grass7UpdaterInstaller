// Registry related functions

#include "stdafx.h"
#include "Registry.h"
#include "FileManagement.h"
#include "Global.h"

RegistryClass RegistryObjects;

void RegistryClass::Init()
{
	RegistryObjects.lpSystemKey = L"gr7System";
	RegistryObjects.lpSoftwareKey = L"gr7Software";
	RegistryObjects.lpDefaultKey = L"gr7Default";
	RegistryObjects.lpSystemUserKey = L"gr7SystemUser";
}

LONG RegistryClass::loadSystemHive()
{
	wchar_t *HiveFile = L"Windows\\System32\\config\\SYSTEM";
	wchar_t lpSysHiveFile[MAX_PATH] = { 0 };
	wcsncpy_s(lpSysHiveFile, MainObjects.driveletterW, sizeof(lpSysHiveFile));
	wcsncat_s(lpSysHiveFile, HiveFile, sizeof(lpSysHiveFile));
	LONG   hSystemKey;
	hSystemKey = RegLoadKeyW(HKEY_LOCAL_MACHINE, RegistryObjects.lpSystemKey,lpSysHiveFile);
	memset(lpSysHiveFile, 0, sizeof(lpSysHiveFile));
	return hSystemKey;
}

LONG RegistryClass::loadSoftwareHive()
{
#ifdef _DEBUG
	wchar_t *HiveFile = L"FF1\\SOFTWARE";
#else
	wchar_t *HiveFile = L"Windows\\System32\\config\\SOFTWARE";
#endif
	wchar_t lpSoftwareHiveFile[MAX_PATH] = { 0 };
	wcsncpy_s(lpSoftwareHiveFile, MainObjects.driveletterW, sizeof(lpSoftwareHiveFile));
	wcsncat_s(lpSoftwareHiveFile, HiveFile, sizeof(lpSoftwareHiveFile));
	LONG   hSoftwareKey;
	hSoftwareKey = RegLoadKeyW(HKEY_LOCAL_MACHINE, RegistryObjects.lpSoftwareKey,lpSoftwareHiveFile);
	memset(lpSoftwareHiveFile, 0, sizeof(lpSoftwareHiveFile));
	return hSoftwareKey;
}

LONG RegistryClass::loadDefaultHive()
{
	wchar_t *HiveFile = L"Windows\\System32\\config\\DEFAULT";
	wchar_t lpDefaultHiveFile[MAX_PATH] = { 0 };
	wcsncpy_s(lpDefaultHiveFile, MainObjects.driveletterW, sizeof(lpDefaultHiveFile));
	wcsncat_s(lpDefaultHiveFile, HiveFile, sizeof(lpDefaultHiveFile));
	LONG   hDefaultKey;
	hDefaultKey = RegLoadKeyW(HKEY_LOCAL_MACHINE, RegistryObjects.lpDefaultKey,lpDefaultHiveFile);
	memset(lpDefaultHiveFile, 0, sizeof(lpDefaultHiveFile));
	return hDefaultKey;
}

LONG RegistryClass::loadSystemUserHive()
{
	wchar_t *HiveFile = L"Windows\\System32\\config\\systemprofile\\ntuser.dat";
	wchar_t lpSystemUserHiveFile[MAX_PATH] = { 0 };
	wcsncpy_s(lpSystemUserHiveFile, MainObjects.driveletterW, sizeof(lpSystemUserHiveFile));
	wcsncat_s(lpSystemUserHiveFile, HiveFile, sizeof(lpSystemUserHiveFile));
	LONG   hSystemUserKey;
	hSystemUserKey = RegLoadKeyW(HKEY_LOCAL_MACHINE, RegistryObjects.lpSystemUserKey,lpSystemUserHiveFile);
	memset(lpSystemUserHiveFile, 0, sizeof(lpSystemUserHiveFile));
	return hSystemUserKey;
}

bool RegistryClass::unloadSystemHive()
{
	bool err;
	err = (RegUnLoadKeyW(HKEY_LOCAL_MACHINE, RegistryObjects.lpSystemKey) != 0);
	return err;
}

bool RegistryClass::unloadSoftwareHive()
{
	bool err;
	err = (RegUnLoadKeyW(HKEY_LOCAL_MACHINE, RegistryObjects.lpSoftwareKey) != 0);
	return err;
}

bool RegistryClass::unloadDefaultHive()
{
	bool err;
	err = (RegUnLoadKeyW(HKEY_LOCAL_MACHINE, RegistryObjects.lpDefaultKey) != 0);
	return err;
}

bool RegistryClass::unloadSystemUserHive()
{
	bool err;
	err = (RegUnLoadKeyW(HKEY_LOCAL_MACHINE, RegistryObjects.lpSystemUserKey) != 0);
	return err;
}