#include "ConstantsHelper.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include "Utility.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

ConstantsHelper& ConstantsHelper::getInstance()
{
    static ConstantsHelper instance;
    return instance;
}

// Function to load constants from a file
void ConstantsHelper::loadConstants(const std::wstring& filename)
{
    std::ifstream inFile(filename);
    auto loc = inFile.getloc().name();

    // Check if the file was opened successfully
    if (!inFile)
        throw std::runtime_error("Error opening constants file for reading.");

    std::string line;
    std::string currentKey;
    while (std::getline(inFile, line))
    {
        if (line.empty())
            continue;
        // Check if this line is a key
        if (line[0] == '[' && line[line.size() - 1] == ']')
        {
            currentKey = line.substr(1, line.size() - 2);
            constants[Utils::string_to_wstring(currentKey)] = std::vector<std::wstring>();
        }
        else
            // This line is a value, add it to the current key
            constants[Utils::string_to_wstring(currentKey)].push_back(Utils::string_to_wstring(line));
    }

    inFile.close();
}

void ConstantsHelper::loadConstantsFromJson(const std::wstring& filename)
{
    std::wifstream file(filename, std::ios::binary);
    std::wstringstream buffer;
    buffer << file.rdbuf();
    std::string json = Utils::wstring_to_string(buffer.str());

    rapidjson::Document doc;
    doc.Parse(json.c_str());

    for (auto& member : doc.GetObject()) {
        if (member.value.IsObject())
        {
            for (auto& lemma : member.value.GetObject())
            {
                std::vector<std::wstring> vec;
                for (auto& val : lemma.value.GetArray()) {
                    vec.emplace_back(Utils::string_to_wstring(val.GetString()));
                }
                lemmas.insert({ Utils::string_to_wstring(lemma.name.GetString()), vec });
            }
        }
        else if (member.value.IsArray())
        {
            std::vector<std::wstring> vec;
            for (auto& val : member.value.GetArray()) {
                vec.push_back(Utils::string_to_wstring(val.GetString()));
            }
            constants.insert({ Utils::string_to_wstring(member.name.GetString()), vec });
        }        
    }
}

void ConstantsHelper::saveConstantsToJson(const std::wstring& filename) const
{
    rapidjson::Document document;
    document.SetObject();

    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    for (const auto& pair : constants) {
        rapidjson::Value key(Utils::wstring_to_string(pair.first).c_str(), allocator);
        rapidjson::Value array(rapidjson::kArrayType);
        for (const auto& elem : pair.second) {
            rapidjson::Value strValue;
            strValue.SetString(Utils::wstring_to_string(elem).c_str(), allocator);
            array.PushBack(strValue, allocator);
        }
        document.AddMember(key, array, allocator);
    }

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    std::wofstream file(filename, std::ios::binary);
    auto loc = file.getloc().name();
    if (file.is_open()) {
        file << buffer.GetString();
    }
    file.close();
}

// Function to get a constant vector by its name
std::vector<std::wstring> ConstantsHelper::getConstants(const std::wstring& name) const
{
    if (constants.find(name) != constants.end())
        return constants.at(name);
    else
        // Return an empty vector if the constant doesn't exist
        return std::vector<std::wstring>();
}

std::wstring ConstantsHelper::getConstant(const std::wstring& name) const
{
    return getConstants(name)[0];
}

const std::unordered_map<Word, ValueArray>& ConstantsHelper::getAllLemmas() const
{
    return lemmas;
}
