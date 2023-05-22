#pragma once

#include <array>

#include "ConstantsHelper.h"
#include "StemmerToken.h"

#include <rapidjson/document.h>

const std::vector<std::wstring> PershaVidminaEndings = {L"à",L"ÿ",L"è",L"³",L"¿",L"ó",L"þ",L"îþ",L"åþ",L"ºþ",L"î",L"å",L"º"};
const std::vector<std::wstring> PershaVidminaHardEndings = {L"à",L"è",L"³",L"ó",L"îþ",L"î"};
const std::vector<std::wstring> PershaVidminaSoftEndings = {L"ÿ",L"³",L"¿",L"þ",L"åþ",L"ºþ",L"å",L"º"};
const std::vector<std::wstring> PershaVidminaMixedEndings = {L"à",L"³",L"ó",L"åþ",L"å"};
const std::wstring HardLetters = L"áâãäçêëìíïðñò";
const std::wstring MixedLetters = L"æ÷ø";
const std::wstring SoftingLetters = L"³ÿþº¿üé";
const std::wstring YotLetters = L"ÿþº¿";
const std::wstring ConsonantLetters = L"áâã´äæçéêëìíïðñòôõö÷øù";
const std::wstring VowelLetters = L"àåºè³¿îóþÿ";

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