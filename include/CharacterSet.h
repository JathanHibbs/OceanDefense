// ---------------------------------------------------------------------------
// Project Name	:	Alpha Engine
// File Name		:	CharacterSet.h
// Author				:	Jeremy Kings
// Creation Date	:	2017/03/14
// Purpose			:	Represents all characters for a given font.
// History			: 
// - 
// ---------------------------------------------------------------------------
#pragma once

#include <map>
#include <string>

typedef std::map<int, int> Kernings;

struct CharacterInfo
{
	int x;
	int y;
	int width;
	int height;
	int xOffset;
	int yOffset;
	int xAdvance;
	Kernings kernings;
};

class CharacterSet
{
public:
	CharacterSet(std::string fontFileName_);
	const CharacterInfo& at(unsigned index) const;

	int GetTextureHeight() const;
	int GetTextureWidth() const;
	int GetLineHeight() const;
	const std::string& GetTextureName() const;

private:
	std::string name;
	int renderSize;
	int lineHeight;
	int textureHeight;
	int textureWidth;
	CharacterInfo characters[256];
	std::string textureName;
};
