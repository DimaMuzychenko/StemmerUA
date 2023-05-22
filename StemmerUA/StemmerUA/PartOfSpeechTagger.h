#pragma once

#include "SuffixTree.h"
#include "WordTree.h"
#include "PreffixTree.h"
#include "StemmerToken.h"

class PartOfSpeechTagger
{
public:
	PartOfSpeechTagger();
	StemmerToken getStem(const std::wstring& word) const;

private:
	bool removePosEnding(std::wstring& word, const SuffixTree* endingTree) const;
	bool removeReflexiveEnding(std::wstring& word) const;
	bool removeActiveParticipleEnding(std::wstring& word) const;
	bool removeAdverbEnding(std::wstring& word) const;
	bool removeAdjectiveEnding(std::wstring& word) const;
	bool removeVerbEnding(std::wstring& word) const;
	bool removeParticiplesufix(std::wstring& word) const;
	bool removeNounEnding(std::wstring& word) const;
	bool removeWovelEnding(std::wstring& word) const;
	bool removeHigherComparativeEnding(std::wstring& word) const;
	bool removeDoubleLetterEnding(std::wstring& word) const;
	bool removeSoftSignEnding(std::wstring& word) const;
	bool isServiceWord(const std::wstring& word) const;
	bool isNumberWord(const std::wstring& word) const;

private:
	SuffixTree reflexiveTree;
	SuffixTree activeParticipleTree;
	SuffixTree adverbTree;
	SuffixTree adjectiveTree;
	SuffixTree verbTree;
	SuffixTree participleTree;
	SuffixTree nounTree;
	WordTree serviceWordTree;
	PreffixTree numberTree;

	std::vector<std::pair<WordTree, std::wstring>> lemmas;
};

