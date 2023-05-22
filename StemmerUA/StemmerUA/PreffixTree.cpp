#include "PreffixTree.h"
#include "ConstantsHelper.h"
#include "Utility.h"

#include <forward_list>

PreffixTree::PreffixTree() : leter(EMPTY_END)
{
}

void PreffixTree::build(const std::vector<std::wstring>& preffixes)
{
	std::forward_list<std::wstring> sortedEndings(preffixes.cbegin(), preffixes.cend());
	sortedEndings.sort(Utils::GraterWstringBySize());
	for (const auto& preffix : sortedEndings)
		addBranch(preffix);
}

std::optional<std::wstring> PreffixTree::checkWord(const std::wstring& word) const
{
	if (word.empty())
		return {};
	if (children.empty())
		return { L"" };

	std::wstring preffix;
	bool isError = true;
	for (const auto& child : children)
	{
		if (child->leter == EMPTY_END)
		{
			isError = false;
			break;
		}
		if (word.starts_with(child->leter))
		{
			auto result = child->checkWord(word.substr(1));
			isError = !result.has_value();
			if (!isError)
				preffix = child->leter + result.value();
			else
				break;
		}
	}
	return isError ? std::optional<std::wstring>{} : preffix;
}

PreffixTree::PreffixTree(wchar_t leter) : leter(leter)
{
}

void PreffixTree::addBranch(const std::wstring& preffix)
{
	wchar_t firstLetter = preffix.empty() ? EMPTY_END : preffix.front();
	PreffixTree* child = findChild(firstLetter);
	if (!child)
		child = addChild(firstLetter);
	if (!preffix.empty())
		child->addBranch(preffix.substr(1));
}

PreffixTree* PreffixTree::findChild(wchar_t leter) const
{
	PreffixTree* result = nullptr;
	for (auto& child : children)
	{
		if (child->leter == leter)
			result = child.get();
	}
	return result;
}

PreffixTree* PreffixTree::addChild(wchar_t leter)
{
	return children.emplace_back(new PreffixTree(leter)).get();
}
