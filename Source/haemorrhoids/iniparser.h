// COMP710 GP 2D Framework 2020
#ifndef __INIPARSER_H__
#define __INIPARSER_H__

// Local includes:
#include <cstdio>
#include <string>
#include <iostream>

// Forward Declarations:

class IniParser
{
	//Member Methods:
public:
	IniParser();
	~IniParser();

	bool LoadIniFile(const std::string& filename);
	std::string GetValueAsString(const std::string& iniSection, const std::string& key);
	int GetValueAsInt(const std::string& iniSection, const std::string& key);
	float GetValueAsFloat(const std::string& iniSection, const std::string& key);
	bool GetValueAsBoolean(const std::string& iniSection, const std::string& key);
protected:

private:
	IniParser(const IniParser& ini);
	IniParser& operator=(const IniParser& ini);

	//Member Data:
public:

protected:


private:

};

#endif __INIPARSER_H__
