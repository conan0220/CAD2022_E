#include <iostream>
#include <string>

#include "Text.h"
#include "DataStructure/Vector.h"

Text::Text() {}

Text::Text(const std::string file_path)
	: file_path(file_path)
{
	ReadFile(file_path);
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

bool Text::IsStringInLine(const std::string& str_target, const int& line) const
{
	return IsStringInString(text[line], str_target);
}

void Text::ReadFile(std::string file_path)
{
	this->file_path = file_path;
	std::ifstream file(file_path);
	std::string line_text = "";
	text.Resize(0);
	if (file.is_open())
	{
		while (std::getline(file, line_text))
		{
			text += line_text;
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
	static Vector<float> float_arr;
	float_arr.RemoveAll();
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
			float_arr += std::stof(temp);
			temp.clear();
		}
	}
	if (!temp.empty())
	{
		float_arr += std::stof(temp);
		temp.clear();
	}
	return float_arr;
}

const bool& Text::IsCharInt(const char& ch) const
{
	return 48 <= static_cast<int>(ch) && static_cast<int>(ch) <= 57 ? true : false;
}

bool Text::IsStringInString(const std::string& str, const std::string& str_target) const
{
	return str.find(str_target) != std::string::npos;
}
