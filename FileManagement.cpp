#include "stdafx.h"
#include "FileManagement.h"
#include "GUIDraw.h"

void FileManagement::Getgr7DriveLetter(std::wstring &DriveLetter)
{
	std::fstream fileStream;

	std::wstring driveList(MAX_PATH, 0);
	driveList.resize((size_t)GetLogicalDriveStringsW((int)driveList.size(), &driveList[0]));
	if (!driveList.empty())
	{
		std::wstring drive = driveList;
		while (!drive.empty())
		{
			std::wstring checkpath = &drive[0];
			checkpath.append(L"Windows\\System32\\identifier");
			fileStream.open(checkpath);
			if (!fileStream.fail()) {
				DriveLetter = &drive[0];
				drive.clear();
			}

			fileStream.close();
			std::wstring string1 = &drive[0];
			drive.erase(0, string1.size() + 1);
		}
	}
}

BOOL FileManagement::ProcessFileList(std::wstring &FileList, int &percentageCounter)
{
	std::wifstream file(FileList);

	if (!file.is_open()) {
		return 1;
	}

	std::wstring line;
	while (std::getline(file, line))
	{
		std::wstring destination = line;
		std::size_t pos = destination.find(L" - ");
		if (pos != std::wstring::npos) {
			destination = destination.substr(pos + 3);
		}
		std::wstring source = line.substr(0, line.find(L" - "));
		destination.insert(0, L"\\");
		source.insert(0, L"\\");
		destination.insert(0, MainObjects.driveletter);
		source.insert(0, MainObjects.driveletter);

		CopyFileW(source.c_str(), destination.c_str(), false);
		if (percentageCounter != 40) {
			percentageCounter = percentageCounter + 1;
			RedrawWindow(MainObjects.hWndMainWindow, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		}
	}
	file.close();
	return 0;
}