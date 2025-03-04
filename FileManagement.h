#pragma once

class FileManagement {
public:
	static void Getgr7DriveLetter(std::wstring &DriveLetter);
	static BOOL ProcessFileList(std::wstring &FileList, int &percentageCounter);
};