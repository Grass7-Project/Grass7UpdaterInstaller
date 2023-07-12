// Functions related to file-management

#include "stdafx.h"
#include "FileManagement.h"
#include <io.h>

struct stat info;

const char *Getgr7DriveLetter()
{
	const char *driveletter;
	std::fstream fileStream;
	// I had no other way of doing this in my way so we have to do this terrible solution, but it works for now.
	// TODO: rewrite this peice of code to be better than this ugly mess.
	fileStream.open("C:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "C:\\";
	}
	fileStream.open("D:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "D:\\";
	}
	fileStream.open("E:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "E:\\";
	}
	fileStream.open("F:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "F:\\";
	}
	fileStream.open("G:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "G:\\";
	}
	fileStream.open("H:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "H:\\";
	}
	fileStream.open("I:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "I:\\";
	}
	fileStream.open("J:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "J:\\";
	}
	fileStream.open("K:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "K:\\";
	}
	fileStream.open("L:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "L:\\";
	}
	fileStream.open("M:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "M:\\";
	}
	fileStream.open("N:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "N:\\";
	}
	fileStream.open("O:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "O:\\";
	}
	fileStream.open("P:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "P:\\";
	}
	fileStream.open("Q:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "Q:\\";
	}
	fileStream.open("R:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "R:\\";
	}
	fileStream.open("S:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "S:\\";
	}
	fileStream.open("T:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "T:\\";
	}
	fileStream.open("U:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "U:\\";
	}
	fileStream.open("V:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "V:\\";
	}
	fileStream.open("W:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "W:\\";
	}
	fileStream.open("Y:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "Y:\\";
	}
	fileStream.open("Z:\\Windows\\System32\\identifier");
	if (fileStream.fail()) {
	} else {
		driveletter = "Z:\\";
	}
	fileStream.close();

	return driveletter;
}