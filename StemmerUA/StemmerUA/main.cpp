#include <locale>
#include <fstream>
#include <unordered_set>
#include <iostream>
#include <fcntl.h>
#include <io.h>

#include<stdio.h>
#include<windows.h>

#include "TextPreprocessor.h"
#include "SuffixTree.h"
#include "Constants.h"
#include "ConstantsHelper.h"
#include "PartOfSpeechTagger.h"
#include "WordTree.h"
#include "Lemmatizer.h"

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

void testGetPos() {

	PartOfSpeechTagger tagger;

	// Test case 1: Noun
	StemmerToken lemma1 = tagger.getStem(L"книгами");
	if (lemma1.originalForm != L"книгами" || lemma1.stem != L"книг" || lemma1.pos != PartOfSpeech::Noun) {
		std::cerr << "Error in getPos test case 1: unexpected output\n";
	}

	// Test case 2: Verb
	StemmerToken lemma2 = tagger.getStem(L"бігає");
	if (lemma2.originalForm != L"бігає" || lemma2.stem != L"біг" || lemma2.pos != PartOfSpeech::Verb) {
		std::cerr << "Error in getPos test case 2: unexpected output\n";
	}

	// Test case 3: Adjective
	StemmerToken lemma3 = tagger.getStem(L"красивий");
	if (lemma3.originalForm != L"красивий" || lemma3.stem != L"красив" || lemma3.pos != PartOfSpeech::Adjective) {
		std::cerr << "Error in getPos test case 3: unexpected output\n";
	}

	// Test case 4: Adverb
	StemmerToken lemma4 = tagger.getStem(L"швидко");
	if (lemma4.originalForm != L"швидко" || lemma4.stem != L"швидк" || lemma4.pos != PartOfSpeech::Adverb) {
		std::cerr << "Error in getPos test case 4: unexpected output\n";
	}

	// Test case 5: Active Participle
	StemmerToken lemma5 = tagger.getStem(L"читаючи");
	if (lemma5.originalForm != L"читаючи" || lemma5.stem != L"чита" || lemma5.pos != PartOfSpeech::ActiveParticle) {
		std::cerr << "Error in getPos test case 5: unexpected output\n";
	}

	// Add more test cases as needed
}

void testStemming(const std::wstring& originalTextFile, const std::wstring& stemmedTextFile)
{
	PartOfSpeechTagger tagger;
	auto originalTokens = TextPreprocessor::process(originalTextFile);
	auto sampleTokens = TextPreprocessor::process(stemmedTextFile);
	std::vector<StemmerToken> resultLemmas;
	int correctlyStemmed = 0;
	for (int tokenNo = 0; tokenNo < originalTokens.size(); ++tokenNo)
	{
		StemmerToken lemma = tagger.getStem(originalTokens[tokenNo]);
		if (lemma.stem == sampleTokens[tokenNo])
			++correctlyStemmed;
		else
			std::wcout << "Original: " << originalTokens[tokenNo] << ", stem: " << sampleTokens[tokenNo] << ", result: " << lemma.stem << std::endl;
	}
	std::wcout << "Score " << correctlyStemmed << "/" << originalTokens.size() << " or (" << (float)correctlyStemmed / originalTokens.size() * 100 << "%)" << std::endl;
}

void testWordTree()
{
	WordTree tree;
	tree.build(ConstantsHelper::getInstance().getConstants(SERVICE_WORDS));

	std::wstring word = L"тільки";
	if (!tree.checkWord(word))
		std::wcerr << "Error in checkWord: unexpected output with " << word << "\n";

	word = L"але";
	if (!tree.checkWord(word))
		std::wcerr << "Error in checkWord: unexpected output with " << word << "\n";

	word = L"бо";
	if (!tree.checkWord(word))
		std::wcerr << "Error in checkWord: unexpected output with " << word << "\n";

	word = L"для";
	if (!tree.checkWord(word))
		std::wcerr << "Error in checkWord: unexpected output with " << word << "\n";

	word = L"і";
	if (!tree.checkWord(word))
		std::wcerr << "Error in checkWord: unexpected output with " << word << "\n";

	word = L"ален";
	if (tree.checkWord(word))
		std::wcerr << "Error in checkWord: unexpected output with " << word << "\n";

}


void stemmingDemo()
{
	std::wstring originalText = L"Якість поділу сміття залежить від активності і свідомості учасників процесу на всіх етапах. Поділ сміття є відповідальністю всіх свідомих громадян і громадянок країни. Щоб система вибіркового збору сміття була ефективною, необхідна активна участь кожної людини, що викидає сміття. Без цього дії місцевих органів влади неефективні. Поділ сміття також вимагає часу і зусиль для навчання громади. Сортування передбачає наявність відповідних контейнерів для кожного виду сміття на спеціально виділеному майданчику-стоянці і регулярний розподіл побутових відходів.";
	std::wstring stemmedText;
	auto words = TextPreprocessor::processStr(originalText);
	PartOfSpeechTagger tagger;
	for (const auto& word : words)
		stemmedText += tagger.getStem(word).stem + L' ';
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	std::wcout << originalText << L"\n\n" << stemmedText << L"\n\n";
}

void lemmatizerDemo()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	std::vector<std::wstring> testNouns = { L"машина",L"перемога",L"староста",L"задача",L"мрія",L"степ",L"батько",L"нежить",L"край",L"товариш", };
	std::vector<Gender> nounGenders = { Gender::Feminine, Gender::Feminine, Gender::Masculine,Gender::Feminine,Gender::Feminine, Gender::Masculine, Gender::Masculine, Gender::Masculine,Gender::Masculine,Gender::Masculine };
	for (int i = 0; i < testNouns.size(); ++i)
	{
		Lemma lemma(testNouns[i]);
		lemma.setGender(nounGenders[i]);
		lemma.setPos(PartOfSpeech::Noun);
		lemma.generateWordforms();
		std::wcout << L"[ ";
		for (int j = 0; j < 7; ++j)
			std::wcout << lemma.getWordform(static_cast<Wordform>(j)) << L", ";
		std::wcout << L" ]\n";
	}
}

void testStemmerWithLemmatizer()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	PartOfSpeechTagger tagger;	
	std::vector<std::wstring> testNouns = { L"машина",L"перемога",L"староста",L"задача",L"мрія",L"степ",L"батько",L"нежить",L"край",L"товариш", };
	std::vector<Gender> nounGenders = { Gender::Feminine, Gender::Feminine, Gender::Masculine,Gender::Feminine,Gender::Feminine, Gender::Masculine, Gender::Masculine, Gender::Masculine,Gender::Masculine,Gender::Masculine };
	int score = 0;
	for (int i = 0; i < testNouns.size(); ++i)
	{
		Lemma lemma(testNouns[i]);
		lemma.setGender(nounGenders[i]);
		lemma.setPos(PartOfSpeech::Noun);
		lemma.generateWordforms();
		std::wcout << L"[ ";
		for (const auto& wordform : lemma.getWordforms())
		{
			auto stem = tagger.getStem(wordform).stem;
			std::wcout << wordform << L" -> " << stem << L", ";
			if (lemma.getStem() == stem) ++score;
		}
		std::wcout << L" ]\n";
	}
	std::wcout << "Score " << score << "/" << testNouns.size() * 7 << " or (" << (float)score / (testNouns.size() * 7) * 100 << "%)" << std::endl;
}

int main()
{
	std::locale::global(std::locale("uk_UA"));
	ConstantsHelper::getInstance().loadConstantsFromJson(L"ConstantsJson.json");


	stemmingDemo();
	lemmatizerDemo();
	testStemmerWithLemmatizer();



	testStemming(L"TestData\\Test1_original.txt", L"TestData\\Test1_stemmed.txt");
	testStemming(L"TestData\\Test2_original.txt", L"TestData\\Test2_stemmed.txt");
	return 0;
}