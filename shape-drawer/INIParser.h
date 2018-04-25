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

    bool LoadFile(const char* _filename);
    bool SaveFile();

    bool AddValue(const char* _section, const char* _key, const char* _value);
    std::string GenerateMapKey(const char* _section, const char* _key);

    int GetSectionCount() const;

    template<typename T>
    bool GetValue(const char* _section, const char* _key, T& _value);

private:
    void FillValue(std::string& _key, std::string _value);
    void FillValue(int& _key, std::string _value);
    void FillValue(float& _key, std::string _value);
    void FillValue(bool& _key, std::string _value);

private:
    std::map<std::string, std::string> mapPairs;
    int sectionCount;
};

// Method Name: Getvalue
// Description: Populates a variable 'T' based on the key in a section
// author: Juan Alejandro Rodriguez Morais
// param _section: The section to look for
// param _key: The key that will fill _value
// param _value: The value reference to fill up
// return: boolean
template<typename T>
inline bool INIParser::GetValue(const char* _section, const char* _key, T& _value)
{
    std::string mapKey = GenerateMapKey(_section, _key);
    std::map<std::string, std::string>::const_iterator it;
    it = mapPairs.find(mapKey);

    if (it != mapPairs.end())
    {
        FillValue(_value, it->second);
        return true;
    }

    return false;
}