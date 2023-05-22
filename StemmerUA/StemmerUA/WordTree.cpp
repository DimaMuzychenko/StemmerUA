#include "WordTree.h"
#include "ConstantsHelper.h"

#include <forward_list>

class GraterWstringBySize
{
public:
	bool operator()(const std::wstring& l, const std::wstring& r) const
	{
		return (l.size() > r.size());
	}
};

WordTree::WordTree() : letter(EMPTY_END)
{
}

void WordTree::build(const std::vector<std::wstring>& endings)
{
	std::forward_list<std::wstring> sortedEndings(endings.cbegin(), endings.cend());
	sortedEndings.sort(GraterWstringBySize());
	for (const auto& word : sortedEndings)
		addBranch(word);
}

std::optional<std::wstring> WordTree::checkWord(const std::wstring& word) const
{
	std::optional<std::wstring> result;
	for (const auto& child : children)
	{
		result = child->checkWordRecursively(word);
		if (result)
			break;
	}
	return result;
}

std::optional<std::wstring> WordTree::checkWordRecursively(const std::wstring& word) const
{
	if (word.empty() && letter == EMPTY_END)
		return { L"" };
	else if (word.empty() || letter == EMPTY_END)
		return {};
	else if (word.front() == letter)
	{
		for (const auto& child : children)
		{
			auto result = child->checkWordRecursively(word.substr(1));
			if (result)
				return letter + result.value();
		}
	}
	return {};
}

WordTree::WordTree(wchar_t leter) : letter(leter)
{
}

void WordTree::addBranch(const std::wstring& word)
{
	wchar_t firstLetter = word.empty() ? EMPTY_END : word.front();
	WordTree* child = findChild(firstLetter);
	if (!child)
		child = addChild(firstLetter);
	if (!word.empty())
		child->addBranch(word.substr(1));
}

WordTree* WordTree::findChild(wchar_t leter) const
{
	WordTree* result = nullptr;
	for (auto& child : children)
	{
		if (child->letter == leter)
			result = child.get();
	}
	return result;
}

WordTree* WordTree::addChild(wchar_t leter)
{
	return children.emplace_back(new WordTree(leter)).get();
}
