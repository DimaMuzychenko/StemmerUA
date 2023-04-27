#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <memory>

enum class PreprocessorResult
{
	Ok,
	FileOpeningError,
	FIleReadingError,
};

class TextPreprocessor
{
public:

	// Returns words of a text from the given .txt file without punctuation marks and stop-words
	static std::vector<std::wstring> process(const std::wstring filename);

	// Returns a result of the previous file processing 
	static PreprocessorResult lastResult();

private:
	TextPreprocessor();
	TextPreprocessor(const TextPreprocessor&);

	static TextPreprocessor& getInstance();
	static std::wstring readWord(std::wifstream& file);
	static bool isValidChar(std::streampos pos, std::wifstream& file);

private:
	PreprocessorResult _lastResult;
};

