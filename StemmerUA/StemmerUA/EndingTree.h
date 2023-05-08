#pragma once

#include <iterator>
#include <string>
#include <vector>
#include <memory>
#include <optional>

class EndingTree
{
public:
	EndingTree();
	void build(const std::vector<std::wstring>& endings);
	std::optional<std::wstring> checkWord(const std::wstring& word) const;

private:
	EndingTree(wchar_t leter);
	void addBranch(const std::wstring& ending);
	EndingTree* findChild(wchar_t leter) const;
	EndingTree* addChild(wchar_t leter);
	void sortBranches();

private:
	std::vector<std::unique_ptr<EndingTree>> children;
	wchar_t leter;
};

