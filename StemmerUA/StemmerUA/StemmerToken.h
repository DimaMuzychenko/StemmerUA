#pragma once

#include <string>

#include "PartOfSpeach.h"

class StemmerToken
{
public:
	StemmerToken();

	std::wstring originalForm;
	std::wstring dictionaryForm;
	std::wstring stem;
	PartOfSpeech pos;
};

