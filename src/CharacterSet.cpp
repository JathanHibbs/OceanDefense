// ---------------------------------------------------------------------------
// Project Name	:	Alpha Engine
// File Name		:	CharacterSet.cpp
// Author				:	Jeremy Kings
// Creation Date	:	2017/03/14
// Purpose			:	Represents all characters for a given font.
// History			: 
// - 
// ---------------------------------------------------------------------------
#include "CharacterSet.h"

#include <fstream>
#include <vector>
#include "TextManager.h"

enum empties_t
{
	empties_ok,
	no_empties
};

void StringSplit(
	std::vector<std::string>& result,
	const std::string& s,
	const std::string& delimiters,
	unsigned empties = no_empties)
{
	if (s.size() == 0)
		return;

	result.clear();
	size_t current;
	size_t next = -1;
	do
	{
		if (empties == no_empties)
		{
			next = s.find_first_not_of(delimiters, next + 1);
			if (next == std::string::npos) break;
			next -= 1;
		}
		current = next + 1;
		next = s.find_first_of(delimiters, current);
		result.push_back(s.substr(current, next - current));
	} 
	while (next != std::string::npos);
}

CharacterSet::CharacterSet(std::string fontFileName_)
{
	std::string filePath = TextManager::GetPrefix() + fontFileName_;

	std::ifstream s(filePath);

	name = fontFileName_;

	std::string line = "";

	while (s.good())
	{
		//AESysPrintf("this is a test");
		std::getline(s, line);

		// Split using regular expression
		std::vector<std::string> tokens;
		StringSplit(tokens, line, " =\"");

		if (tokens.size() > 0)
		{

			if (tokens[0] == "info")
			{
				for (unsigned i = 1; i < tokens.size(); ++i)
				{
					if (tokens[i] == "size")
					{
						renderSize = atoi(tokens[i + 1].c_str());
					}
				}
			}
			else if (tokens[0] == "common")
			{
				for (unsigned i = 1; i < tokens.size(); ++i)
				{
					if (tokens[i] == "lineHeight")
					{
						lineHeight = atoi(tokens[i + 1].c_str());
					}
					else if (tokens[i] == "scaleW")
					{
						textureWidth = atoi(tokens[i + 1].c_str());
					}
					else if (tokens[i] == "scaleH")
					{
						textureHeight = atoi(tokens[i + 1].c_str());
					}
				}
			}
			else if (tokens[0] == "page")
			{
				for (unsigned i = 1; i < tokens.size(); ++i)
				{
					if (tokens[i] == "file")
					{
						std::string filename = tokens[i + 1];
						textureName = filename;
						break;
					}
				}
			}
			else if (tokens[0] == "char")
			{
				int index = 0;
				for (unsigned i = 1; i < tokens.size(); ++i)
				{

					if (tokens[i] == "id")
						index = atoi(tokens[i + 1].c_str());
					if (tokens[i] == "x")
						characters[index].x = atoi(tokens[i + 1].c_str());
					if (tokens[i] == "y")
						characters[index].y = atoi(tokens[i + 1].c_str());
					if (tokens[i] == "width")
						characters[index].width = atoi(tokens[i + 1].c_str());
					if (tokens[i] == "height")
						characters[index].height = atoi(tokens[i + 1].c_str());
					if (tokens[i] == "xoffset")
						characters[index].xOffset = atoi(tokens[i + 1].c_str());
					if (tokens[i] == "yoffset")
						characters[index].yOffset = atoi(tokens[i + 1].c_str());
					if (tokens[i] == "xadvance")
						characters[index].xAdvance = atoi(tokens[i + 1].c_str());
				}
			}
			else if (tokens[0] == "kerning")
			{
				int index = 0;
				int first = 0;
				int amount = 0;
				for (unsigned i = 1; i < tokens.size(); ++i)
				{
					if (tokens[i] == "first")
						first = atoi(tokens[i + 1].c_str());
					if (tokens[i] == "second")
						index = atoi(tokens[i + 1].c_str());
					if (tokens[i] == "amount")
						amount = atoi(tokens[i + 1].c_str());
				}
				characters[index].kernings[first] = amount;
			}
		}
	}
	s.close();
}

const CharacterInfo& CharacterSet::at(unsigned index) const
{
	return characters[index];
}

int CharacterSet::GetTextureHeight() const
{
	return textureHeight;
}

int CharacterSet::GetTextureWidth() const
{
	return textureWidth;
}

int CharacterSet::GetLineHeight() const
{
	return lineHeight;
}

const std::string& CharacterSet::GetTextureName() const
{
	return textureName;
}
