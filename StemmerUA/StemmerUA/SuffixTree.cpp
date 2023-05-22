#include "SuffixTree.h"
#include "ConstantsHelper.h"
#include "Utility.h"

#include <forward_list>


SuffixTree::SuffixTree() : leter(EMPTY_END)
{
}

void SuffixTree::build(const std::vector<std::wstring>& endings)
{
	std::forward_list<std::wstring> sortedEndings(endings.cbegin(), endings.cend());
	sortedEndings.sort(Utils::GraterWstringBySize());
	for (const auto& ending : sortedEndings)
		addBranch(ending);
}

std::optional<std::wstring> SuffixTree::checkWord(const std::wstring& word) const
{
	if (word.empty())
		return {};
	if (children.empty())
		return { L"" };

	std::wstring ending;
	bool isError = true;
	for (const auto& child : children)
	{
		if (child->leter == EMPTY_END)
		{
			isError = false;
			break;
		}
		if (word.ends_with(child->leter))
		{
			auto result = child->checkWord(word.substr(0, word.size() - 1));
			isError = !result.has_value();
			if (!isError)
				ending = result.value() + child->leter;
			else
				break;
		}
	}
	return isError ? std::optional<std::wstring>{} : ending;
}

SuffixTree::SuffixTree(wchar_t leter) : leter(leter)
{
}

void SuffixTree::addBranch(const std::wstring& ending)
{
	wchar_t lastLeter = ending.empty() ? EMPTY_END : ending.back();
	SuffixTree* child = findChild(lastLeter);
	if (!child)
		child = addChild(lastLeter);
	if(!ending.empty())
		child->addBranch(ending.substr(0, ending.size() - 1));
}

SuffixTree* SuffixTree::findChild(wchar_t leter) const
{
	SuffixTree* result = nullptr;
	for (auto& child : children)
	{
		if (child->leter == leter)
			result = child.get();
	}
	return result;
}

SuffixTree* SuffixTree::addChild(wchar_t leter)
{
	return children.emplace_back(new SuffixTree(leter)).get();
}

void SuffixTree::sortBranches()
{
	for (auto& child : children)
	{
		if (child->leter == EMPTY_END)
			std::swap(child, children.back());
		child->sortBranches();
	}
}
