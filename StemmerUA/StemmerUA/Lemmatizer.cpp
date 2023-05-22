#include "Lemmatizer.h"
#include "Utility.h"

#include <stdexcept>

Lemmatizer::Lemmatizer()
{
}

Wordforms NounLemmatizer::getWordforms(const std::wstring& word, Gender gender, Plurality plurality) 
{
	Wordforms wordforms;

	if (isFirstWordformGroup(word, gender))
		wordforms = getWordformsForFirstGroup(word, plurality);
	else if (isSecondWordformGroup(word, gender))
		wordforms = getWordformsForSecondGroup(word, gender, plurality);

	return wordforms;
}

int NounLemmatizer::getWordformGroup(const std::wstring& word, Gender gender) 
{
	int wordformGroup = 4;
	if (isFirstWordformGroup(word, gender))
		wordformGroup = 1;
	else if (isSecondWordformGroup(word, gender))
		wordformGroup = 2;
	else if (isThirdWordformGroup(word, gender))
		wordformGroup = 3;
	return wordformGroup;
}

Wordforms NounLemmatizer::getWordformsForFirstGroup(const std::wstring& word, Plurality plurality) 
{
	Wordforms wordforms;
	std::wstring stem = getStem(word);
	// Soft group
	if (isSoftGroup(word))
	{
		if (isSoftGroupWithYot(word))
		{
			wordforms[0] = word + L"";
			wordforms[1] = stem + L"¿";
			wordforms[2] = stem + L"¿";
			wordforms[3] = stem + L"þ";
			wordforms[4] = stem + L"ºþ";
			wordforms[5] = stem + L"¿";
			wordforms[6] = stem + L"º";
		}
		else
		{
			wordforms[0] = word + L"";
			wordforms[1] = stem + L"³";
			wordforms[2] = stem + L"³";
			wordforms[3] = stem + L"þ";
			wordforms[4] = stem + L"åþ";
			wordforms[5] = stem + L"³";
			wordforms[6] = stem + L"å";
		}
	}
	// Hard group
	else if (isHardGroup(word))
	{
		wordforms[0] = word + L"";
		wordforms[1] = stem + L"è";
		wordforms[2] = stem + L"³";
		wordforms[3] = stem + L"ó";
		wordforms[4] = stem + L"îþ";
		wordforms[5] = stem + L"³";
		wordforms[6] = stem + L"î";
	}
	// Mixed group
	else
	{
		wordforms[0] = word + L"";
		wordforms[1] = stem + L"³";
		wordforms[2] = stem + L"³";
		wordforms[3] = stem + L"ó";
		wordforms[4] = stem + L"åþ";
		wordforms[5] = stem + L"³";
		wordforms[6] = stem + L"å";
	}

	if (wordforms[2].ends_with(L"ã³"))
		wordforms[2][wordforms[2].size() - 2] = L'ç';
	if (wordforms[2].ends_with(L"ê³"))
		wordforms[2][wordforms[2].size() - 2] = L'ö';
	if (wordforms[2].ends_with(L"õ³"))
		wordforms[2][wordforms[2].size() - 2] = L'ñ';

	if (wordforms[5].ends_with(L"ã³"))
		wordforms[5][wordforms[5].size() - 2] = L'ç';
	if (wordforms[5].ends_with(L"ê³"))
		wordforms[5][wordforms[5].size() - 2] = L'ö';
	if (wordforms[5].ends_with(L"õ³"))
		wordforms[5][wordforms[5].size() - 2] = L'ñ';

	return wordforms;
}

Wordforms NounLemmatizer::getWordformsForSecondGroup(const std::wstring& word, Gender gender, Plurality plurality) 
{
	Wordforms wordforms;
	std::wstring stem = getStem(word);
	// Soft group
	if (isSoftGroup(word))
	{
		if (isSoftGroupWithYot(word))
		{
			wordforms[0] = word + L"";
			wordforms[1] = stem + L"þ";
			wordforms[2] = stem + L"ºâ³";
			wordforms[3] = wordforms[1];
			wordforms[4] = stem + L"ºì";
			wordforms[5] = stem + L"þ";
			wordforms[6] = stem + L"þ";
		}
		else
		{
			wordforms[0] = word + L"";
			wordforms[1] = stem + L"ÿ";
			wordforms[2] = stem + L"þ";
			wordforms[3] = wordforms[1];
			wordforms[4] = stem + L"åì";
			wordforms[5] = stem + L"³";
			wordforms[6] = stem + L"þ";
		}
	}
	// Hard group
	else if (isHardGroup(word))
	{
		wordforms[0] = word + L"";
		wordforms[1] = stem + L"à";
		wordforms[2] = stem + L"ó";
		wordforms[3] = wordforms[1];
		wordforms[4] = stem + L"îì";
		wordforms[5] = stem + L"îâ³";
		wordforms[6] = stem + L"ó";
	}
	// Mixed group
	else
	{
		wordforms[0] = word + L"";
		wordforms[1] = stem + L"à";
		wordforms[2] = stem + L"ó";
		wordforms[3] = wordforms[1];
		wordforms[4] = stem + L"åì";
		wordforms[5] = stem + L"³";
		wordforms[6] = stem + L"ó";
	}

	if (wordforms[5].ends_with(L"ã³"))
		wordforms[5][wordforms[5].size() - 2] = L'ç';
	if (wordforms[5].ends_with(L"ê³"))
		wordforms[5][wordforms[5].size() - 2] = L'ö';
	if (wordforms[5].ends_with(L"õ³"))
		wordforms[5][wordforms[5].size() - 2] = L'ñ';

	return wordforms;
}

bool NounLemmatizer::isFirstWordformGroup(const std::wstring& word, Gender gender) 
{
	bool isFirstGroup = false;
	if (gender == Gender::Masculine || gender == Gender::Feminine)
		isFirstGroup = word.back() == L'à' || word.back() == L'ÿ';
	return isFirstGroup;
}

bool NounLemmatizer::isSecondWordformGroup(const std::wstring& word, Gender gender) 
{
	bool isSecondGroup = false;
	if (gender == Gender::Masculine)
	{
		isSecondGroup = ConsonantLetters.find(word.ends_with(L'ü') ? word[word.size() - 2] : word.back()) != std::wstring::npos;
		isSecondGroup |= word.ends_with(L"î");
	}
	else if (gender == Gender::Neuter)
		isSecondGroup = word.ends_with(L"î") || word.ends_with(L"å") || word.ends_with(L"ÿ");
	return isSecondGroup;
}

bool NounLemmatizer::isThirdWordformGroup(const std::wstring& word, Gender gender) 
{
	bool isThirdGroup = false;
	if (gender == Gender::Feminine)
		isThirdGroup = ConsonantLetters.find(word.ends_with(L'ü') ? word[word.size() - 2] : word.back()) != std::wstring::npos;
	return isThirdGroup;
}

bool NounLemmatizer::isHardGroup(const std::wstring& word) 
{
	std::wstring stem = getRidOfVowelEnding(word);
	bool hasHardGrupFeature = HardLetters.find(stem.back()) != std::wstring::npos;
	return !isSoftGroup(word) && hasHardGrupFeature;
}

bool NounLemmatizer::isSoftGroup(const std::wstring& word) 
{
	return SoftingLetters.find(word.back()) != std::wstring::npos;
}

bool NounLemmatizer::isSoftGroupWithYot(const std::wstring& word) 
{
	std::wstring stem = getStem(word);
	return isSoftGroup(word) && !(HardLetters.find(stem.back()) != std::wstring::npos && stem.back() != L'é');
}

bool NounLemmatizer::isMixedGroup(const std::wstring& word) 
{
	return !isSoftGroup(word) && !isHardGroup(word);
}

std::wstring NounLemmatizer::getStem(const std::wstring& word)
{
	std::wstring stem = getRidOfVowelEnding(word);
	if (stem.back() == L'ü' || stem.back() == L'é')
		stem.resize(stem.size() - 1);
	return stem;
}

std::wstring getRidOfVowelEnding(const std::wstring& word)
{
	std::wstring resultWord = word;
	if(!resultWord.empty() && VowelLetters.find(resultWord.back()) != std::wstring::npos)
		resultWord.resize(resultWord.size() - 1);
	return resultWord;
}

Lemma::Lemma(const std::wstring& word) : pos(PartOfSpeech::None), gender(Gender::Masculine), plurality(Plurality::Singular)
{
	if (word.empty())
		throw std::runtime_error("Cannot create a lemma for empty word");
	wordforms[0] = word;
	stem = NounLemmatizer::getStem(word);
}

const std::wstring& Lemma::getWordform(Wordform vidminok) const
{
	return wordforms.at((int)vidminok);
}

const Wordforms& Lemma::getWordforms() const
{
	return wordforms;
}

const std::wstring& Lemma::getStem() const
{
	return stem;
}

PartOfSpeech Lemma::getPos() const
{
	return pos;
}

void Lemma::setPos(PartOfSpeech pos)
{
	this->pos = pos;
}

Gender Lemma::getGender() const
{
	return gender;
}

void Lemma::setGender(Gender gender)
{
	this->gender = gender;
}

Plurality Lemma::getPlurality() const
{
	return plurality;
}

void Lemma::setPlurality(Plurality plurality)
{
	this->plurality = plurality;
}

void Lemma::generateWordforms()
{
	switch (pos)
	{
	case PartOfSpeech::None:
		break;
	case PartOfSpeech::Adverb:
		break;
	case PartOfSpeech::ActiveParticle:
		break;
	case PartOfSpeech::Adjective:
		break;
	case PartOfSpeech::Verb:
		break;
	case PartOfSpeech::Participle:
		break;
	case PartOfSpeech::Noun:
		wordforms = NounLemmatizer::getWordforms(wordforms[0], gender, plurality);
		break;
	case PartOfSpeech::Number:
		break;
	case PartOfSpeech::Service:
		break;
	default:
		break;
	}
}

rapidjson::Value Lemma::toJsonObject(rapidjson::Document::AllocatorType& allocator) const
{
	rapidjson::Value obj(rapidjson::kObjectType);
	rapidjson::Value wordformsArray(rapidjson::kArrayType);

	// Convert wordforms to UTF8 and add to array
	for (const auto& wordform : wordforms) {
		rapidjson::Value wordformValue;
		std::string wordformUtf8 = Utils::wstring_to_string(wordform);
		wordformValue.SetString(wordformUtf8.c_str(), wordformUtf8.length(), allocator);
		wordformsArray.PushBack(wordformValue, allocator);
	}

	// Add wordforms to object
	obj.AddMember("wordforms", wordformsArray, allocator);

	// Add other members
	std::string stemUtf8 = Utils::wstring_to_string(stem);
	obj.AddMember("stem", rapidjson::Value().SetString(stemUtf8.c_str(), stemUtf8.length(), allocator), allocator);

	obj.AddMember("partOfSpeech", rapidjson::Value().SetInt(static_cast<int>(pos)), allocator);
	obj.AddMember("gender", rapidjson::Value().SetInt(static_cast<int>(gender)), allocator);
	obj.AddMember("plurality", rapidjson::Value().SetInt(static_cast<int>(plurality)), allocator);

	return obj;
}
