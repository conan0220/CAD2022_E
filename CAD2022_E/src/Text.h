#pragma once

#include <fstream>

#include "DataStructure/Vector.h"

class Text
{
public:
	// constructor
	Text();
	Text(const std::string filePath);
	~Text();

	// useful function
	const Vector<std::string>& GetText() { return text; }
	const Vector<float>& GetFloatInLine(const int& line) { return GetFloatInString(text[line]); }
	const int& FindCharacterIndex(const char& character, const int& line_index = 0, const int& begin = 0) const;   // when ch not in string return -1

	bool IsStringInLine(const std::string& str, const int& line) const;

	void ReadFile(std::string filePath);	// read .txt file and write in the text

	void PushBack(const std::string& text);

	// operator
	void operator += (const std::string& text) { PushBack(text); }
	std::string& operator [] (const int& line) { return text[line]; }

private:
	const int& CharToInt(const char& ch) const;

	const Vector<float>& GetFloatInString(const std::string& str) const;

	const bool& IsCharInt(const char& ch) const;	// is char int?
	bool IsStringInString(const std::string& str, const std::string& strTarget) const;

	// data
	std::string filePath = "";
	Vector<std::string> text = NULL;
};