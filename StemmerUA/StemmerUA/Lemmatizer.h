#pragma once

#include <array>

#include "ConstantsHelper.h"
#include "StemmerToken.h"

#include <rapidjson/document.h>

const std::vector<std::wstring> PershaVidminaEndings = {L"�",L"�",L"�",L"�",L"�",L"�",L"�",L"��",L"��",L"��",L"�",L"�",L"�"};
const std::vector<std::wstring> PershaVidminaHardEndings = {L"�",L"�",L"�",L"�",L"��",L"�"};
const std::vector<std::wstring> PershaVidminaSoftEndings = {L"�",L"�",L"�",L"�",L"��",L"��",L"�",L"�"};
const std::vector<std::wstring> PershaVidminaMixedEndings = {L"�",L"�",L"�",L"��",L"�"};
const std::wstring HardLetters = L"�������������";
const std::wstring MixedLetters = L"���";
const std::wstring SoftingLetters = L"�������";
const std::wstring YotLetters = L"����";
const std::wstring ConsonantLetters = L"���������������������";
const std::wstring VowelLetters = L"��賿����";

using Wordforms = std::array<std::wstring, 7>;

enum class Wordform
{
	Naming,
	Birthing,
	Giving,
	Finding,
	Handling,
	Placing,
	Calling
};

enum class Gender
{
	Masculine,
	Feminine,
	Neuter
};

enum class Plurality
{
	Singular,
	Plural
};

std::wstring getRidOfVowelEnding(const std::wstring& word);

class NounLemmatizer
{
public:
	static Wordforms getWordforms(const std::wstring& word, Gender gender, Plurality plurality);
	static int getWordformGroup(const std::wstring& word,  Gender gender);
	static Wordforms getWordformsForFirstGroup(const std::wstring& word, Plurality plurality);
	static Wordforms getWordformsForSecondGroup(const std::wstring& word, Gender gender, Plurality plurality);
	static bool isFirstWordformGroup(const std::wstring& word, Gender gender);
	static bool isSecondWordformGroup(const std::wstring& word, Gender gender);
	static bool isThirdWordformGroup(const std::wstring& word, Gender gender);
	static bool isHardGroup(const std::wstring& word);
	static bool isSoftGroup(const std::wstring& word);
	static bool isSoftGroupWithYot(const std::wstring& word);
	static bool isMixedGroup(const std::wstring& word);
	static std::wstring getStem(const std::wstring& word);
};

class Lemmatizer
{
public:
	Lemmatizer();
	
};

class Lemma
{
public:
	Lemma(const std::wstring& word);
	const std::wstring& getWordform(Wordform vidminok) const;
	const Wordforms& getWordforms() const;
	const std::wstring& getStem() const;
	PartOfSpeech getPos() const;
	void setPos(PartOfSpeech pos);
	Gender getGender() const;
	void setGender(Gender gender);
	Plurality getPlurality() const;
	void setPlurality(Plurality plurality);
	void generateWordforms();
	rapidjson::Value toJsonObject(rapidjson::Document::AllocatorType& allocator) const;

private:
	std::wstring stem;
	Wordforms wordforms;
	PartOfSpeech pos;
	Gender gender;
	Plurality plurality;
};