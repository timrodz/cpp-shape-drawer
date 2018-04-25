//
//  File Name: INIParser.h
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Header file for the .ini parser class
//

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

    bool LoadIniFile(const char* _pcFilename);
    bool SaveIniFile();
    bool AddValue(const char* _pcSection, const char* _pcKey, const char* _pcValue);
    std::string GenerateMapKey(const char* _pcSection, const char* _pcKey);

    int GetSectionCount() const;

    bool GetStringValue(const char* _pcSection, const char* _pcKey, std::string& _value);
    bool GetIntValue(const char* _pcSection, const char* _pcKey, int& _value);
    bool GetFloatValue(const char* _pcSection, const char* _pcKey, float& _value);
    bool GetBoolValue(const char* _pcSection, const char* _pcKey, bool& _value);

private:
    std::map<std::string, std::string> mapPairs;
    int sectionCount;
};