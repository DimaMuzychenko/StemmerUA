#pragma once

#include <string>
#include <vector>
#include <memory>
#include <optional>

class SuffixTree
{
public:
	SuffixTree();
	void build(const std::vector<std::wstring>& endings);
	std::optional<std::wstring> checkWord(const std::wstring& word) const;

private:
	SuffixTree(wchar_t leter);
	void addBranch(const std::wstring& ending);
	SuffixTree* findChild(wchar_t leter) const;
	SuffixTree* addChild(wchar_t leter);
	void sortBranches();

private:
	std::vector<std::unique_ptr<SuffixTree>> children;
	wchar_t leter;
};

