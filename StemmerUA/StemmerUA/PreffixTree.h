#pragma once

#include <string>
#include <vector>
#include <memory>
#include <optional>

class PreffixTree
{
public:
	PreffixTree();
	void build(const std::vector<std::wstring>& preffixes);
	std::optional<std::wstring> checkWord(const std::wstring& word) const;

private:
	PreffixTree(wchar_t leter);
	void addBranch(const std::wstring& preffix);
	PreffixTree* findChild(wchar_t leter) const;
	PreffixTree* addChild(wchar_t leter);

private:
	std::vector<std::unique_ptr<PreffixTree>> children;
	wchar_t leter;
};

