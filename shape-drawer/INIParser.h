#pragma once

#include <map>
#include <algorithm>
#include <direct.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Utils.h"

class INIParser
{

public:
    INIParser();
    ~INIParser();

    bool SaveIniFile();

    bool LoadIniFile(const char* _pcFilename);

    bool AddValue(const char* _pcSection, const char* _pcKey, const char* _pcValue);

    bool GetStringValue(const char* _pcSection, const char* _pcKey, std::string& _value);

    bool GetIntValue(const char* _pcSection, const char* _pcKey, int& _value);

    bool GetFloatValue(const char* _pcSection, const char* _pcKey, float& _value);

    bool GetBoolValue(const char* _pcSection, const char* _pcKey, bool& _value);

    std::string GenerateMapKey(const char* _pcSection, const char* _pcKey);

    int GetSectionCount() const;

private:
    //Create a map member variable to store the ini file.
    std::map<std::string, std::string> m_mapPairs;
    int sectionCount;
};