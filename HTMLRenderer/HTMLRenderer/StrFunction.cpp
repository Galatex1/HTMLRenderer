#include "stdafx.h"
#include "StrFunction.h"

vector<string> split(const string & str, const string & delim)
{
	vector<string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == string::npos) pos = str.length();
		string token = str.substr(prev, pos - prev);
		if (!token.empty()) tokens.push_back(token);
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());
	return tokens;
}

vector<string> split(const string & str, const string & delim, bool keepDelimiter)
{
	vector<string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		bool delimiter = true;
		pos = str.find(delim, prev);

		if (pos == string::npos)
		{
			pos = str.length();
			delimiter = false;
		}

		string token = str.substr(prev, pos - prev);

		if (!token.empty())
		{
			tokens.push_back(token);
		}

		if (keepDelimiter && delimiter)
			tokens.push_back(delim);

		prev = pos + delim.length();

	} while (pos < str.length() && prev < str.length());
	return tokens;
}

bool replace(std::string & str, const std::string & from, const std::string & to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

void replaceAll(std::string & str, const std::string & from, const std::string & to) {
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}


vector<vector<string>> getLines(vector<string> texts)
{
	vector<vector<string>> lines = {};
	for each (string line in texts)
	{
		lines.push_back(split(line, "\n"));
	}
	return lines;
}
wchar_t *CharToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

