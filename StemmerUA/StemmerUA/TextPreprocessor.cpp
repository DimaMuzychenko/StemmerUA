#include <stdexcept>
#include <codecvt>
#include <cwctype>

#include "TextPreprocessor.h"
#include "Constants.h"

TextPreprocessor::TextPreprocessor() : _lastResult(PreprocessorResult::Ok)
{

}

TextPreprocessor& TextPreprocessor::getInstance()
{
	static TextPreprocessor instance;
	return instance;
}

PreprocessorResult TextPreprocessor::lastResult()
{
	return PreprocessorResult();
}

std::vector<std::wstring> TextPreprocessor::process(const std::wstring filename)
{
	std::vector<std::wstring> words;
	std::wifstream file(filename, std::ios::binary);
	if (!file.is_open())
	{
		TextPreprocessor::getInstance()._lastResult = PreprocessorResult::FileOpeningError;
		return words;
	}
	std::wstring word;
	while (word = readWord(file), !word.empty())
		words.emplace_back(word);
 	return words;
}

std::wstring TextPreprocessor::readWord(std::wifstream& file)
{
	std::wstring word;
	std::streampos pos = file.tellg();
	while (!file.eof())
	{
		wchar_t ch = std::towlower(file.seekg(pos).peek());
		if (isValidChar(pos, file))
			word += ch;
		else if (!word.empty())
			break;

		pos += std::streampos(1);
	}
	return word;
}

bool TextPreprocessor::isValidChar(std::streampos pos, std::wifstream& file)
{

	bool result = false;
	wchar_t ch = file.seekg(pos).peek();
	if (std::iswalpha(ch))
		result = true;
	else if (VALID_MID_WORD_MARKS.find(ch) != std::wstring::npos)
	{
		bool isLastCharAlpha = pos > 0 && std::iswalpha(file.seekg(pos - std::streampos(1)).peek());
		bool isNextCharAlpha = std::iswalpha(file.seekg(pos + std::streampos(1)).peek());
		if (isLastCharAlpha && isNextCharAlpha)
			result = true;
	}
	return result;
}
