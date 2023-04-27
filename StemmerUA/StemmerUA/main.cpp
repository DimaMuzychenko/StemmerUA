#include <locale>

#include "TextPreprocessor.h"
#include "Constants.h"

int main()
{
	std::locale::global(std::locale("uk_UA"));
	TextPreprocessor::process(L"Test.txt");
	return 0;
}