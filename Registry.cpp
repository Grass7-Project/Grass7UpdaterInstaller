#include "stdafx.h"
#include "Registry.h"
#include "FileManagement.h"

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
	std::wstring SysHiveFile = MainObjects.driveletterW;
	SysHiveFile.append(L"Windows\\System32\\config\\SYSTEM");
	LONG   hSystemKey;
	hSystemKey = RegLoadKeyW(HKEY_LOCAL_MACHINE, RegistryObjects.lpSystemKey, SysHiveFile.c_str());
	return hSystemKey;
}

LONG RegistryClass::loadSoftwareHive()
{
	std::wstring SoftwareHiveFile = MainObjects.driveletterW;
#ifdef _DEBUG
	SoftwareHiveFile.append(L"FF1\\SOFTWARE");
#else
	SoftwareHiveFile.append(L"Windows\\System32\\config\\SOFTWARE");
#endif
	LONG   hSoftwareKey;
	hSoftwareKey = RegLoadKeyW(HKEY_LOCAL_MACHINE, RegistryObjects.lpSoftwareKey, SoftwareHiveFile.c_str());
	return hSoftwareKey;
}

LONG RegistryClass::loadDefaultHive()
{
	std::wstring DefaultHiveFile = MainObjects.driveletterW;
	DefaultHiveFile.append(L"Windows\\System32\\config\\DEFAULT");
	LONG   hDefaultKey;
	hDefaultKey = RegLoadKeyW(HKEY_LOCAL_MACHINE, RegistryObjects.lpDefaultKey, DefaultHiveFile.c_str());
	return hDefaultKey;
}

LONG RegistryClass::loadSystemUserHive()
{
	std::wstring SystemUserHiveFile = MainObjects.driveletterW;
	SystemUserHiveFile.append(L"Windows\\System32\\config\\systemprofile\\ntuser.dat");
	LONG   hSystemUserKey;
	hSystemUserKey = RegLoadKeyW(HKEY_LOCAL_MACHINE, RegistryObjects.lpSystemUserKey, SystemUserHiveFile.c_str());
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