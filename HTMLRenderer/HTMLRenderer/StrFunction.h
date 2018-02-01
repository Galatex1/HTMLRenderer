#pragma once
#include <string>
#include <vector>

using namespace std;

vector<string> split(const string& str, const string& delim);
vector<string> split(const string& str, const string& delim, bool keepDelimiter);
bool replace(std::string& str, const std::string& from, const std::string& to);
void replaceAll(std::string& str, const std::string& from, const std::string& to);
vector<vector<string>> getLines(vector<string> texts);
