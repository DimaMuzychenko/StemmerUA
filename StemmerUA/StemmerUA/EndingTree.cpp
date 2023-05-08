#include "EndingTree.h"
#include "Constants.h"

EndingTree::EndingTree() : leter(EMPTY_END)
{
}

void EndingTree::build(const std::vector<std::wstring>& endings)
{
	for (const auto& ending : endings)
		addBranch(ending);
	sortBranches();
}

std::optional<std::wstring> EndingTree::checkWord(const std::wstring& word) const
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

EndingTree::EndingTree(wchar_t leter) : leter(leter)
{
}

void EndingTree::addBranch(const std::wstring& ending)
{
	wchar_t lastLeter = ending.empty() ? EMPTY_END : ending.back();
	EndingTree* child = findChild(lastLeter);
	if (!child)
		child = addChild(lastLeter);
	if(!ending.empty())
		child->addBranch(ending.substr(0, ending.size() - 1));
}

EndingTree* EndingTree::findChild(wchar_t leter) const
{
	EndingTree* result = nullptr;
	for (auto& child : children)
	{
		if (child->leter == leter)
			result = child.get();
	}
	return result;
}

EndingTree* EndingTree::addChild(wchar_t leter)
{
	return children.emplace_back(new EndingTree(leter)).get();
}

void EndingTree::sortBranches()
{
	for (auto& child : children)
	{
		if (child->leter == EMPTY_END)
			std::swap(child, children.back());
		child->sortBranches();
	}
}
