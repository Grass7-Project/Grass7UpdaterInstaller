// Functions related to file-management

#include "stdafx.h"
#include "FileManagement.h"
#include "Global.h"
#include <io.h>

const char *FileManagementClass::Getgr7DriveLetter()
{
	const char *driveletter;
	std::fstream fileStream;
	// I had no other way of doing this in my way so we have to do this terrible solution, but it works for now.
	// TODO: rewrite this peice of code to be better than this ugly mess.
	fileStream.open(L"C:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "C:\\";
	}
	fileStream.open(L"D:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "D:\\";
	}
	fileStream.open(L"E:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "E:\\";
	}
	fileStream.open(L"F:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "F:\\";
	}
	fileStream.open(L"G:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "G:\\";
	}
	fileStream.open(L"H:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "H:\\";
	}
	fileStream.open(L"I:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "I:\\";
	}
	fileStream.open(L"J:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "J:\\";
	}
	fileStream.open(L"K:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "K:\\";
	}
	fileStream.open(L"L:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "L:\\";
	}
	fileStream.open(L"M:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "M:\\";
	}
	fileStream.open(L"N:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "N:\\";
	}
	fileStream.open(L"O:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "O:\\";
	}
	fileStream.open(L"P:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "P:\\";
	}
	fileStream.open(L"Q:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "Q:\\";
	}
	fileStream.open(L"R:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "R:\\";
	}
	fileStream.open(L"S:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "S:\\";
	}
	fileStream.open(L"T:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "T:\\";
	}
	fileStream.open(L"U:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "U:\\";
	}
	fileStream.open(L"V:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "V:\\";
	}
	fileStream.open(L"W:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "W:\\";
	}
	fileStream.open(L"Y:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "Y:\\";
	}
	fileStream.open(L"Z:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "Z:\\";
	}
	fileStream.close();

	return driveletter;
}

const wchar_t *FileManagementClass::Getgr7DriveLetterW()
{
	wchar_t *driveletter;
	std::fstream fileStream;
	// I had no other way of doing this in my way so we have to do this terrible solution, but it works for now.
	// TODO: rewrite this peice of code to be better than this ugly mess.
	fileStream.open(L"C:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"C:\\";
	}
	fileStream.open(L"D:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"D:\\";
	}
	fileStream.open(L"E:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"E:\\";
	}
	fileStream.open(L"F:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"F:\\";
	}
	fileStream.open(L"G:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"G:\\";
	}
	fileStream.open(L"H:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"H:\\";
	}
	fileStream.open(L"I:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"I:\\";
	}
	fileStream.open(L"J:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"J:\\";
	}
	fileStream.open(L"K:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"K:\\";
	}
	fileStream.open(L"L:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"L:\\";
	}
	fileStream.open(L"M:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"M:\\";
	}
	fileStream.open(L"N:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"N:\\";
	}
	fileStream.open(L"O:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"O:\\";
	}
	fileStream.open(L"P:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"P:\\";
	}
	fileStream.open(L"Q:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"Q:\\";
	}
	fileStream.open(L"R:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"R:\\";
	}
	fileStream.open(L"S:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"S:\\";
	}
	fileStream.open(L"T:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"T:\\";
	}
	fileStream.open(L"U:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"U:\\";
	}
	fileStream.open(L"V:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"V:\\";
	}
	fileStream.open(L"W:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"W:\\";
	}
	fileStream.open(L"Y:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"Y:\\";
	}
	fileStream.open(L"Z:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	}
	else {
		driveletter = L"Z:\\";
	}
	fileStream.close();

	return driveletter;
}