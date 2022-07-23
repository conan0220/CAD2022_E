#include <iostream>
#include <string>

#include "Text.h"
#include "DataStructure/Vector.h"

Text::Text() {}

Text::Text(const std::string filePath)
	: filePath(filePath)
{
	ReadFile(filePath);
}

Text::~Text() {}

const int& Text::FindCharacterIndex(const char& character, const int& line_index, const int& begin) const
{
	for (int i = begin; i < text[line_index].size(); i++)
	{
		if (text[line_index][i] == character)
		{
			return i;
		}
	}
	return -1;
}

bool Text::IsStringInLine(const std::string& strTarget, const int& line) const
{
	return IsStringInString(text[line], strTarget);
}

void Text::ReadFile(std::string filePath)
{
	this->filePath = filePath;
	std::ifstream file(filePath);
	std::string lineText = "";
	text.Resize(0);
	if (file.is_open())
	{
		while (std::getline(file, lineText))
		{
			text += lineText;
		}
	}
	else
	{
		std::cerr << "[Error]: Failed to open file." << std::endl;
		exit(EXIT_FAILURE);
	}
	file.close();
}

void Text::PushBack(const std::string& text)
{
	this->text += text;
}

const int& Text::CharToInt(const char& ch) const
{
	if (!IsCharInt(ch))
	{
		std::cerr << "[Error]: Char is not number" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		return static_cast<int>(ch) - 48;
	}
}

const Vector<float>& Text::GetFloatInString(const std::string& str) const
{
	static Vector<float> floatArr;
	floatArr.RemoveAll();
	std::string temp = "";
	for (int i = 0; i < str.size(); i++)
	{
		char ch = str[i];
		if (ch == '-' && IsCharInt(str[i + 1]) && i < str.size() - 1 && temp.empty())
		{
			temp += ch;
		}
		else if (IsCharInt(ch) || ch == '.')
		{
			temp += ch;
		}
		else if (!temp.empty())
		{
			floatArr += std::stof(temp);
			temp.clear();
		}
	}
	if (!temp.empty())
	{
		floatArr += std::stof(temp);
		temp.clear();
	}
	return floatArr;
}

const bool& Text::IsCharInt(const char& ch) const
{
	return 48 <= static_cast<int>(ch) && static_cast<int>(ch) <= 57 ? true : false;
}

bool Text::IsStringInString(const std::string& str, const std::string& strTarget) const
{
	return str.find(strTarget) != std::string::npos;
}
