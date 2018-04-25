#include "INIParser.h"

#include <algorithm>
#include <direct.h>
#include <iostream>
#include <fstream>
#include <string>

using std::string;

INIParser::INIParser()
{}


INIParser::~INIParser()
{}

bool INIParser::SaveIniFile()
{
    std::ofstream file;
    _mkdir("../Resources");
    file.open("../Resources/saveFile.ini");

    string currentSection = "";
    string lastSection = currentSection;

    if (file.is_open())
    {

        std::cout << "Ini file saved\n";

        std::map<string, string>::const_iterator it;
        it = m_mapPairs.begin();

        for (int i = 0; i < m_mapPairs.size(); i++)
        {
            std::cout << it->first << " = " << it->second << "\n";
            it++;
        }

        it = m_mapPairs.begin();

        while (it != m_mapPairs.end())
        {

            string tempSection = "";
            string tempKey = "";
            string tempValue = "";

            std::size_t findBar = it->first.find("|");

            tempSection = it->first.substr(0, findBar);
            currentSection = tempSection;

            tempKey = it->first.substr(findBar + 1, it->first.back());
            tempValue = it->second;

            if (currentSection != lastSection)
            {

                file << "[" << currentSection << "]\n";
                lastSection = currentSection;

            }

            file << tempKey << " = " << tempValue << "\n";

            it++;

        }

        // Organize the sections

        file.close();
        return true;

    }

    return false;

}

// Load an INI file.
// Populates the map with keys and values using
// the add value function.
bool INIParser::LoadIniFile(const char* _file)
{
    std::ifstream file;
    string sFile = _file;
    string line;
    file.open("../Resources/" + sFile + ".ini");

    if (file.is_open())
    {
        string currentSection = "";
        string lastSection = currentSection;

        while (file.good())
        {
            string tempSection;
            string tempKey;
            string tempValue;

            // Find the section
            std::getline(file, line);

            if (line.empty())
            {
                return false;
            }

            if (line.at(0) == '[' && line.at(line.length() - 1) == ']')
            {
                std::size_t findSectionStart = line.find("[");
                std::size_t findSectionEnd = line.find("]");
                if (line.front() == line.at(findSectionStart) && line.back() == line.at(findSectionEnd))
                {
                    tempSection = line.substr(findSectionStart + 1, findSectionEnd - 1);
                    currentSection = tempSection;
                    std::getline(file, line);
                    sectionCount++;
                }
            }
            else
            {
                if (currentSection == lastSection)
                {
                    tempSection = currentSection;
                }
            }

            // Find the key and its value to assign
            std::size_t findEqual = line.find("=");
            if (findEqual != string::npos)
            {
                tempKey = line.substr(0, findEqual - 1);
                tempValue = line.substr(findEqual + 2, line.back());
                std::cout << "Found = at " << findEqual << " - " << tempValue << "\n";
            }

            if (tempSection != "\0" && tempKey != "\0" && tempValue != "\0")
            {
                lastSection = currentSection;
                AddValue(tempSection.c_str(), tempKey.c_str(), tempValue.c_str());
            }
        }

        file.close();
        return true;
    }

    return false;
}

// Adds a value to the map.
// Combines the _pcSection, with _pcKey to create a
// key for the map.
bool INIParser::AddValue(const char* _pcSection, const char* _pcKey, const char* _pcValue)
{
    string mapKey = GenerateMapKey(_pcSection, _pcKey);
    string val = _pcValue;

    if (GetStringValue(_pcSection, _pcKey, string(_pcValue)) == false)
    {
        m_mapPairs.insert(std::make_pair(mapKey, _pcValue));
        return true;
    }

    return false;
}

// GetStringValue
// Returns true if the value was found.
// _rStrValue will be populated with the correct data if // the key is found in the map.
bool INIParser::GetStringValue(const char* _pcSection, const char* _pcKey, std::string& _rStrValue)
{
    string mapKey = GenerateMapKey(_pcSection, _pcKey);
    std::map<string, string>::const_iterator it;
    it = m_mapPairs.find(mapKey);

    if (it != m_mapPairs.end())
    {
        _rStrValue = it->second;
        return true;
    }

    return false;
}

// GetIntValue
// Returns true if the value was found.
// _riValue will be populated with the correct data if
// the key is found in the map.
bool INIParser::GetIntValue(const char* _pcSection, const char* _pcKey, int& _riValue)
{
    string mapKey = GenerateMapKey(_pcSection, _pcKey);
    std::map<string, string>::const_iterator it;
    it = m_mapPairs.find(mapKey);

    if (it != m_mapPairs.end())
    {
        _riValue = std::stoi(it->second);
        return true;
    }
    return false;
}

// GetFloatValue
// Returns true if the value was found.
// _rfValue will be populated with the correct data if
// the key is found in the map.
bool INIParser::GetFloatValue(const char* _pcSection, const char* _pcKey, float& _rfValue)
{
    string mapKey = GenerateMapKey(_pcSection, _pcKey);
    std::map<string, string>::const_iterator it;
    it = m_mapPairs.find(mapKey);

    if (it != m_mapPairs.end())
    {
        _rfValue = std::stof(it->second);
        return true;
    }

    return false;
}

// GetBoolValue
// Returns true if the value was found.
// _rbValue will be populated with the correct data if
// the key is found in the map.
bool INIParser::GetBoolValue(const char* _pcSection, const char* _pcKey, bool& _rbValue)
{
    string mapKey = GenerateMapKey(_pcSection, _pcKey);
    std::map<string, string>::const_iterator it;
    it = m_mapPairs.find(mapKey);

    if (it != m_mapPairs.end())
    {
        if (it->second == "true" || it->second == "1")
        {
            _rbValue = 1;
            return true;
        }
        else if (it->second == "false" || it->second == "0")
        {
            _rbValue = 0;
            return true;
        }
    }

    return false;
}

std::string INIParser::GenerateMapKey(const char* _pcSection, const char* _pcKey)
{
    string toGenerate;
    string strSection = _pcSection;
    string strKey = _pcKey;
    toGenerate = strSection + "|" + strKey;
    return toGenerate;
}

int INIParser::GetSectionCount() const
{
    return (sectionCount);
}
