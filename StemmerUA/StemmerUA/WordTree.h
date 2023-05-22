#pragma once

#include <iterator>
#include <string>
#include <vector>
#include <memory>
#include <optional>

class WordTree
{
public:
	WordTree();
	void build(const std::vector<std::wstring>& endings);
	std::optional<std::wstring> checkWord(const std::wstring& word) const;

private:
	WordTree(wchar_t leter);
	std::optional<std::wstring> checkWordRecursively(const std::wstring& word) const;
	void addBranch(const std::wstring& ending);
	WordTree* findChild(wchar_t leter) const;
	WordTree* addChild(wchar_t leter);

private:
	std::vector<std::unique_ptr<WordTree>> children;
	wchar_t letter;
};

