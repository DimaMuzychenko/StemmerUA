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
	StemmerToken lemma1 = tagger.getStem(L"�������");
	if (lemma1.originalForm != L"�������" || lemma1.stem != L"����" || lemma1.pos != PartOfSpeech::Noun) {
		std::cerr << "Error in getPos test case 1: unexpected output\n";
	}

	// Test case 2: Verb
	StemmerToken lemma2 = tagger.getStem(L"���");
	if (lemma2.originalForm != L"���" || lemma2.stem != L"��" || lemma2.pos != PartOfSpeech::Verb) {
		std::cerr << "Error in getPos test case 2: unexpected output\n";
	}

	// Test case 3: Adjective
	StemmerToken lemma3 = tagger.getStem(L"��������");
	if (lemma3.originalForm != L"��������" || lemma3.stem != L"������" || lemma3.pos != PartOfSpeech::Adjective) {
		std::cerr << "Error in getPos test case 3: unexpected output\n";
	}

	// Test case 4: Adverb
	StemmerToken lemma4 = tagger.getStem(L"������");
	if (lemma4.originalForm != L"������" || lemma4.stem != L"�����" || lemma4.pos != PartOfSpeech::Adverb) {
		std::cerr << "Error in getPos test case 4: unexpected output\n";
	}

	// Test case 5: Active Participle
	StemmerToken lemma5 = tagger.getStem(L"�������");
	if (lemma5.originalForm != L"�������" || lemma5.stem != L"����" || lemma5.pos != PartOfSpeech::ActiveParticle) {
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

	std::wstring word = L"�����";
	if (!tree.checkWord(word))
		std::wcerr << "Error in checkWord: unexpected output with " << word << "\n";

	word = L"���";
	if (!tree.checkWord(word))
		std::wcerr << "Error in checkWord: unexpected output with " << word << "\n";

	word = L"��";
	if (!tree.checkWord(word))
		std::wcerr << "Error in checkWord: unexpected output with " << word << "\n";

	word = L"���";
	if (!tree.checkWord(word))
		std::wcerr << "Error in checkWord: unexpected output with " << word << "\n";

	word = L"�";
	if (!tree.checkWord(word))
		std::wcerr << "Error in checkWord: unexpected output with " << word << "\n";

	word = L"����";
	if (tree.checkWord(word))
		std::wcerr << "Error in checkWord: unexpected output with " << word << "\n";

}


void stemmingDemo()
{
	std::wstring originalText = L"����� ����� ����� �������� �� ��������� � �������� �������� ������� �� ��� ������. ���� ����� � ������������� ��� ������� �������� � ���������� �����. ��� ������� ���������� ����� ����� ���� ����������, ��������� ������� ������ ����� ������, �� ������ �����. ��� ����� 䳿 ������� ������ ����� ����������. ���� ����� ����� ������ ���� � ������ ��� �������� �������. ���������� ��������� �������� ��������� ���������� ��� ������� ���� ����� �� ���������� ��������� ����������-������� � ���������� ������� ��������� ������.";
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
	std::vector<std::wstring> testNouns = { L"������",L"��������",L"��������",L"������",L"���",L"����",L"������",L"������",L"����",L"�������", };
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
	std::vector<std::wstring> testNouns = { L"������",L"��������",L"��������",L"������",L"���",L"����",L"������",L"������",L"����",L"�������", };
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