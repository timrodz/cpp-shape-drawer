//
//  File Name: INIParser.cpp
//  Author: Juan Alejandro Rodriguez Morais
//  Email: timrodz@icloud.com
//
//  Reads and writes to an .ini file
//

#include "INIParser.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

using std::string;

INIParser::INIParser() {}

INIParser::~INIParser() {}

// Method Name: SaveFile
// Description: Saves the generated map keys into a file
// author: Juan Alejandro Rodriguez Morais
// return: boolean
bool INIParser::SaveFile()
{
    std::ofstream file;
    file.open("resources/SaveFile.ini");

    string currentSection = "";
    string lastSection = currentSection;

    if (file.is_open())
    {
        std::cout << "Ini file saved\n";

        std::map<string, string>::const_iterator it;
        it = this->mapPairs.begin();

        for (unsigned int i = 0; i < this->mapPairs.size(); ++i)
        {
            std::cout << it->first << " = " << it->second << "\n";
            it++;
        }

        it = this->mapPairs.begin();

        while (it != this->mapPairs.end())
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

// Method Name: LoadFile
// Description: Loads an .ini file (It must be located under the resources folder)
// And populates the map 
// author: Juan Alejandro Rodriguez Morais
// param _file: The file to load
// return: boolean
bool INIParser::LoadFile(const char* _file)
{
    std::ifstream file;
    string sFile = _file;
    string line;
    file.open("resources/" + sFile + ".ini");

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

            // If the line is empty, return - File is corrupted
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
                    this->sectionCount++;

                    std::streampos previousLinePosition = file.tellg();

                    std::getline(file, line);

                    // If line is another section, Find a new one
                    if (line.at(0) == '[' && line.at(line.length() - 1) == ']')
                    {
                        // Check for duplicate sections, this occurs at the end of the file
                        size_t duplicateSection = line.find(tempSection);
                        if (duplicateSection == std::string::npos)
                        {
                            this->sectionCount++;
                        }
                    }
                    else
                    {
                        file.seekg(previousLinePosition);
                    }
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

// Method Name: AddValue
// Description: Adds a value to the map
// author: Juan Alejandro Rodriguez Morais
// param _section: The section to look for
// param _key: The key that will fill _value
// param _value: The value reference to fill up
// return: boolean
bool INIParser::AddValue(const char* _section, const char* _key, const char* _value)
{
    string mapKey = GenerateMapKey(_section, _key);
    string val = _value;

    if (GetValue<string>(_section, _key, string(_value)) == false)
    {
        this->mapPairs.insert(std::make_pair(mapKey, _value));
        return true;
    }

    return false;
}

// Method Name: GenerateMapKey
// Description: Creates a map key inside a section
// author: Juan Alejandro Rodriguez Morais
// param _section: The section to look for
// param _key: The key that will fill _value
// return: string
std::string INIParser::GenerateMapKey(const char* _section, const char* _key)
{
    string strSection = _section;
    string strKey = _key;
    string toGenerate = strSection + "|" + strKey;
    return toGenerate;
}

// Method Name: GetSectionCount
// Description: Returns the amount of sections found in the file
// author: Juan Alejandro Rodriguez Morais
// return: int
int INIParser::GetSectionCount() const
{
    return this->sectionCount;
}

// Method Name: FillValue
// Description: Populates a key given a string value
// author: Juan Alejandro Rodriguez Morais
// param _key: The value to populate
// return: void
void INIParser::FillValue(std::string& _key, std::string _value)
{
    _key = _value;
}

// Method Name: FillValue
// Description: Populates a key given a string value
// author: Juan Alejandro Rodriguez Morais
// param _key: The value to populate
// return: void
void INIParser::FillValue(int& _key, std::string _value)
{
    _key = std::stoi(_value);
}

// Method Name: FillValue
// Description: Populates a key given a string value
// author: Juan Alejandro Rodriguez Morais
// param _key: The value to populate
// return: void
void INIParser::FillValue(float& _key, std::string _value)
{
    _key = std::stof(_value);
}

// Method Name: FillValue
// Description: Populates a key given a string value
// author: Juan Alejandro Rodriguez Morais
// param _key: The value to populate
// return: void
void INIParser::FillValue(bool& _key, std::string _value)
{
    if (_value == "true" || _value == "1")
    {
        _key = true;
    }
    else if (_value == "false" || _value == "0")
    {
        _key = false;
    }
}