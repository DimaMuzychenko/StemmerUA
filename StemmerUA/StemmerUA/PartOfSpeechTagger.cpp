#include "PartOfSpeechTagger.h"
#include "ConstantsHelper.h"

PartOfSpeechTagger::PartOfSpeechTagger()
{
	const ConstantsHelper& constants = ConstantsHelper::getInstance();
	reflexiveTree.build(constants.getConstants(REFLEXIVE_VERB_ENDINGS));
	activeParticipleTree.build(constants.getConstants(ACTIVE_PARTICIPLE_ENDINGS));
	adverbTree.build(constants.getConstants(ADVERB_ENDINGS));
	adjectiveTree.build(constants.getConstants(ADJECTIVE_ENDINGS));
	verbTree.build(constants.getConstants(VERB_ENDINGS));
	participleTree.build(constants.getConstants(PARTICIPLE_SUFFIXES));
	nounTree.build(constants.getConstants(NOUN_ENDINGS));
	serviceWordTree.build(constants.getConstants(SERVICE_WORDS));
	numberTree.build(constants.getConstants(NUMBER_PREFFIXES));

	for (const auto& lemma : constants.getAllLemmas())
	{
		lemmas.emplace_back();
		lemmas.back().first.build(lemma.second);
		lemmas.back().second = lemma.first;
	}
}

StemmerToken PartOfSpeechTagger::getStem(const std::wstring& word) const
{
	if (word.empty())
		return {};

	StemmerToken lemma;
	lemma.originalForm = word;
	lemma.stem = word;
	if (isServiceWord(lemma.originalForm))
	{
		lemma.pos = PartOfSpeech::Service;
		lemma.dictionaryForm = lemma.originalForm;
		return lemma;
	}

	for (const auto& lemmaTree : lemmas)
	{
		if (lemmaTree.first.checkWord(lemma.originalForm))
		{
			lemma.dictionaryForm = lemmaTree.second;
			return lemma;
		}
	}

	removeReflexiveEnding(lemma.stem);
	if (removeActiveParticipleEnding(lemma.stem))
		lemma.pos = PartOfSpeech::ActiveParticle;
	else if (removeAdjectiveEnding(lemma.stem))
	{
		/*if (removeParticiplesufix(lemma.stem))
			lemma.pos = PartOfSpeech::Participle;
		else*/
			lemma.pos = PartOfSpeech::Adjective;
	}
	else if (removeAdverbEnding(lemma.stem))
		lemma.pos = PartOfSpeech::Adverb;
	else if (removeVerbEnding(lemma.stem))
		lemma.pos = PartOfSpeech::Verb;
	else if (removeNounEnding(lemma.stem) || removeWovelEnding(lemma.stem))
		lemma.pos = PartOfSpeech::Noun;

	if (isNumberWord(lemma.originalForm))
		lemma.pos = PartOfSpeech::Number;

	//removeHigherComparativeEnding(lemma.stem);
	removeDoubleLetterEnding(lemma.stem);
	removeSoftSignEnding(lemma.stem);
	
	return lemma;
}

bool PartOfSpeechTagger::removePosEnding(std::wstring& word, const SuffixTree* endingTree) const
{
	auto ending = endingTree->checkWord(word);
	if (ending)
		word.resize(word.size() - ending->size());
	return ending.has_value();
}

bool PartOfSpeechTagger::removeReflexiveEnding(std::wstring& word) const
{
	return removePosEnding(word, &reflexiveTree);
}

bool PartOfSpeechTagger::removeActiveParticipleEnding(std::wstring& word) const
{
	return removePosEnding(word, &activeParticipleTree);
}

bool PartOfSpeechTagger::removeAdverbEnding(std::wstring& word) const
{
	auto ending = adverbTree.checkWord(word);
	if (ending)
		removeWovelEnding(word);
	return ending.has_value();
}

bool PartOfSpeechTagger::removeAdjectiveEnding(std::wstring& word) const
{
	return removePosEnding(word, &adjectiveTree);
}

bool PartOfSpeechTagger::removeVerbEnding(std::wstring& word) const
{
	return removePosEnding(word, &verbTree);
}

bool PartOfSpeechTagger::removeParticiplesufix(std::wstring& word) const
{
	return removePosEnding(word, &participleTree);
}

bool PartOfSpeechTagger::removeNounEnding(std::wstring& word) const
{
	return removePosEnding(word, &nounTree);
}

bool PartOfSpeechTagger::removeWovelEnding(std::wstring& word) const
{
	static const std::wstring Wovels = ConstantsHelper::getInstance().getConstant(WOVEL_LETTERS);
	bool result = false;
	if(!word.empty() && Wovels.find(word.back()) != std::wstring::npos)
	{
		result = true;
		word.resize(word.size() - 1);
	}
	/*while (!word.empty() && Wovels.find(word.back()) != std::wstring::npos)
	{
		result = true;
		word.resize(word.size() - 1);
	}*/
	return result;
}

bool PartOfSpeechTagger::removeHigherComparativeEnding(std::wstring& word) const
{
	static const std::wstring HigherComperativeSuffix = ConstantsHelper::getInstance().getConstant(HIGHER_COMPERATIVE_SUFFIX);
	if (word.empty())
		return false;

	bool result = word.ends_with(HigherComperativeSuffix);
	if (result)
		word.resize(word.size() - HigherComperativeSuffix.size());
	return  result;
}

bool PartOfSpeechTagger::removeDoubleLetterEnding(std::wstring& word) const
{
	if (word.size() < 2)
		return false;

	bool result = word[word.size() - 1] == word[word.size() - 2];
	if (result)
		word.resize(word.size() - 1);
	return result;
}

bool PartOfSpeechTagger::removeSoftSignEnding(std::wstring& word) const
{
	static const std::wstring SoftSign = ConstantsHelper::getInstance().getConstant(SOFT_SIGN);
	if (word.empty())
		return false;

	bool result = word.ends_with(SoftSign);
	if (result)
		word.resize(word.size() - SoftSign.size());
	return result;
}

bool PartOfSpeechTagger::isServiceWord(const std::wstring& word) const
{
	if (word.empty())
		return false;

	return serviceWordTree.checkWord(word).has_value();
}

bool PartOfSpeechTagger::isNumberWord(const std::wstring& word) const
{
	if (word.empty())
		return false;
	return numberTree.checkWord(word).has_value();
}
