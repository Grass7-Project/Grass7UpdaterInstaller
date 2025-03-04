#pragma once

class ConfigManager {
public:
	static BOOL LoadConfig(std::wstring &ConfigFile);
private:
	static void SetValue(std::wstring &Key, std::wstring &Value);

	std::map<std::wstring, int> mapping = { { L"UpdateID", 1 },
	{ L"arch", 2 },
	{ L"requireupdate", 3 },
	{ L"OScommands", 4 },
	{ L"newUpdateLevel", 5 },
	{ L"newPatchLevel", 6 },
	{ L"newBuildString", 7 },
	{ L"InfoFile", 8 },
	{ L"commandsEnabled", 9 },
	{ L"commandlineShow", 10 },
	{ L"unloadSoftRegOnCmd", 11 },
	{ L"loadSysReg", 12 },
	{ L"loadDefaultReg", 13 },
	{ L"loadSystemUserReg", 14 } };
};