#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

#include "Constants.h"

using Name = std::wstring;
using Word = std::wstring;
using ValueArray = std::vector<std::wstring>;

class ConstantsHelper
{
public:

    static ConstantsHelper& getInstance();
    void loadConstants(const std::wstring& filename);
    void loadConstantsFromJson(const std::wstring& filename);
    void saveConstantsToJson(const std::wstring& filename) const;
    std::vector<std::wstring> getConstants(const std::wstring& name) const;
    std::wstring getConstant(const std::wstring& name) const;
    const std::unordered_map<Word, ValueArray>& getAllLemmas() const;

protected:
    ConstantsHelper() = default;
    ~ConstantsHelper() = default;
    ConstantsHelper(const ConstantsHelper&) = default;
    ConstantsHelper& operator=(const ConstantsHelper&) = default;

    std::unordered_map<Name, ValueArray> constants;
    std::unordered_map<Word, ValueArray> lemmas;
};

