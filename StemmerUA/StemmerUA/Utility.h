#pragma once

#include <string>

namespace Utils
{
	std::string wstring_to_string(const std::wstring& wstr);
	std::wstring string_to_wstring(const std::string& str);

	class GraterWstringBySize
	{
	public:
		bool operator()(const std::wstring& l, const std::wstring& r) const;
	};
}
