#include "stdafx.h"
#include "Registry.h"
#include "FileManagement.h"

Registry RegistryObjects;

void Registry::Init()
{
	RegistryObjects.lpSystemKey = L"gr7System";
	RegistryObjects.lpSoftwareKey = L"gr7Software";
	RegistryObjects.lpDefaultKey = L"gr7Default";
	RegistryObjects.lpSystemUserKey = L"gr7SystemUser";
}

LONG Registry::loadSystemHive()
{
	std::wstring SysHiveFile = MainObjects.driveletter;
	SysHiveFile.append(L"Windows\\System32\\config\\SYSTEM");
	LONG   hSystemKey;
	hSystemKey = RegLoadKeyW(HKEY_LOCAL_MACHINE, RegistryObjects.lpSystemKey, SysHiveFile.c_str());
	return hSystemKey;
}

LONG Registry::loadSoftwareHive()
{
	std::wstring SoftwareHiveFile = MainObjects.driveletter;
#ifdef _DEBUG
	SoftwareHiveFile.append(L"FF1\\SOFTWARE");
#else
	SoftwareHiveFile.append(L"Windows\\System32\\config\\SOFTWARE");
#endif
	LONG   hSoftwareKey;
	hSoftwareKey = RegLoadKeyW(HKEY_LOCAL_MACHINE, RegistryObjects.lpSoftwareKey, SoftwareHiveFile.c_str());
	return hSoftwareKey;
}

LONG Registry::loadDefaultHive()
{
	std::wstring DefaultHiveFile = MainObjects.driveletter;
	DefaultHiveFile.append(L"Windows\\System32\\config\\DEFAULT");
	LONG   hDefaultKey;
	hDefaultKey = RegLoadKeyW(HKEY_LOCAL_MACHINE, RegistryObjects.lpDefaultKey, DefaultHiveFile.c_str());
	return hDefaultKey;
}

LONG Registry::loadSystemUserHive()
{
	std::wstring SystemUserHiveFile = MainObjects.driveletter;
	SystemUserHiveFile.append(L"Windows\\System32\\config\\systemprofile\\ntuser.dat");
	LONG   hSystemUserKey;
	hSystemUserKey = RegLoadKeyW(HKEY_LOCAL_MACHINE, RegistryObjects.lpSystemUserKey, SystemUserHiveFile.c_str());
	return hSystemUserKey;
}

bool Registry::unloadSystemHive()
{
	bool err;
	err = (RegUnLoadKeyW(HKEY_LOCAL_MACHINE, RegistryObjects.lpSystemKey) != 0);
	return err;
}

bool Registry::unloadSoftwareHive()
{
	bool err;
	err = (RegUnLoadKeyW(HKEY_LOCAL_MACHINE, RegistryObjects.lpSoftwareKey) != 0);
	return err;
}

bool Registry::unloadDefaultHive()
{
	bool err;
	err = (RegUnLoadKeyW(HKEY_LOCAL_MACHINE, RegistryObjects.lpDefaultKey) != 0);
	return err;
}

bool Registry::unloadSystemUserHive()
{
	bool err;
	err = (RegUnLoadKeyW(HKEY_LOCAL_MACHINE, RegistryObjects.lpSystemUserKey) != 0);
	return err;
}