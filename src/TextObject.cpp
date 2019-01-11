// ---------------------------------------------------------------------------
// Project Name	:	Alpha Engine
// File Name		:	TextObject.cpp
// Author				:	Jeremy Kings
// Creation Date	:	2017/03/14
// Purpose			:	Game object that displays text.
// History			: 
// - 
// ---------------------------------------------------------------------------
#include "TextObject.h"

#include <cstdlib>
#include "CharacterSet.h"
#include "FontTypes.h"
#include "TextManager.h"

const unsigned NO_COLOR = 0xFF000000;

TextObject::TextObject(std::string name, std::string text, FontTypes font)
	: text(text), name(name), fontType(font), mesh(NULL), isDead(false), width(0.0f), height(0.0f)
{
	// Create mesh
	ChangeText();

	// Set defaults
	SetPosition(0.0f, 0.0f);
	SetScale(1.0f, 1.0f);
	SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Register with text manager
	TextManager::AddTextObject(this);
}

TextObject::~TextObject()
{
	AEGfxMeshFree(mesh);
}

void TextObject::Kill()
{
	isDead = true;
}

boolean TextObject::IsDead() const
{
	return isDead;
}

const std::string& TextObject::GetText() const
{
	return text;
}

void TextObject::SetText(std::string text)
{
	if (IsDead())
		return;

	this->text = text;
	ChangeText();
}

void TextObject::SetPosition(AEVec2 position)
{
	SetPosition(position.x, position.y);
}

void TextObject::SetPosition(float x, float y)
{
	AEVec2Set(&pos, x, y);
}

AEVec2 TextObject::GetPosition() const
{
	return pos;
}

void TextObject::SetScale(float x, float y)
{
	AEVec2Set(&scale, x, y);
}

void TextObject::SetColor(float r, float g, float b, float a)
{
	modulationColor[0] = r;
	modulationColor[1] = g;
	modulationColor[2] = b;
	modulationColor[3] = a;
}

const float* TextObject::GetColor() const
{
	return modulationColor;
}

AEVec2 TextObject::GetScale() const
{
	return scale;
}

const std::string& TextObject::GetName() const
{
	return name;
}

void TextObject::ChangeText()
{
	const CharacterSet* characterSet = TextManager::GetCharacterSet(fontType);

	if (characterSet == NULL)
	{
		return;
	}

	if (mesh != NULL)
	{
		AEGfxMeshFree(mesh);
		mesh = NULL;
	}

	unsigned numFloats = text.length() * 24;
	float* points = new float[numFloats];
	memset(points, 0, 0);

	width = 0;
	height = 0;

	for (unsigned i = 0, j = 0; i < text.length(); ++i, j += 24)
	{
		if (text.at(i) == '\n')
		{
			width = 0;
			height += characterSet->GetLineHeight();
			continue;
		}

		float tu_start = (float)characterSet->at(text.at(i)).x / (float)characterSet->GetTextureWidth();
		float tu_end = (float)(characterSet->at(text.at(i)).x + characterSet->at(text.at(i)).width) / (float)characterSet->GetTextureWidth();
		float tv_start = (float)characterSet->at(text.at(i)).y / (float)characterSet->GetTextureHeight();
		float tv_end = (float)(characterSet->at(text.at(i)).y + characterSet->at(text.at(i)).height) / (float)characterSet->GetTextureHeight();

		float finalXOffset = width + characterSet->at(text.at(i)).xOffset;

		if (i > 0)
		{
			if (characterSet->at(text.at(i)).kernings.size() > 0)
			{
				const CharacterInfo* info = &characterSet->at(text.at(i));
				Kernings::const_iterator it = info->kernings.find(text.at(i - 1));

				// If kernings contains the thing
				if (it != info->kernings.end())
				{
					finalXOffset += it->second;
				}
			}
		}

		points[j] = finalXOffset;
		points[j + 1] = -(height + characterSet->at(text.at(i)).height);
		points[j + 2] = tu_start;
		points[j + 3] = tv_end;

		points[j + 4] = characterSet->at(text.at(i)).width + finalXOffset;
		points[j + 5] = -(height + characterSet->at(text.at(i)).height);
		points[j + 6] = tu_end;
		points[j + 7] = tv_end;

		points[j + 8] = finalXOffset;
		points[j + 9] = -(height);
		points[j + 10] = tu_start;
		points[j + 11] = tv_start;

		points[j + 12] = characterSet->at(text.at(i)).width + finalXOffset;
		points[j + 13] = -(height + characterSet->at(text.at(i)).height);
		points[j + 14] = tu_end;
		points[j + 15] = tv_end;

		points[j + 16] = characterSet->at(text.at(i)).width + finalXOffset;
		points[j + 17] = -(height);
		points[j + 18] = tu_end;
		points[j + 19] = tv_start;

		points[j + 20] = finalXOffset;
		points[j + 21] = -height;
		points[j + 22] = tu_start;
		points[j + 23] = tv_start;

		width += characterSet->at(text.at(i)).xAdvance;
	}

	AEGfxMeshStart();

	for (unsigned i = 0; (i + 23) < numFloats; i += 24)
	{
		AEGfxTriAdd(points[i], points[i + 1], NO_COLOR, points[i + 2], points[i + 3],
			points[i + 4], points[i + 5], NO_COLOR, points[i + 6], points[i + 7],
			points[i + 8], points[i + 9], NO_COLOR, points[i + 10], points[i + 11]);
		AEGfxTriAdd(points[i + 12], points[i + 13], NO_COLOR, points[i + 14], points[i + 15],
			points[i + 16], points[i + 17], NO_COLOR, points[i + 18], points[i + 19],
			points[i + 20], points[i + 21], NO_COLOR, points[i + 22], points[i + 23]);
	}
	mesh = AEGfxMeshEnd();

	delete points;
}

FontTypes TextObject::GetFontType() const
{
	return fontType;
}

AEGfxVertexList* TextObject::GetMesh() const
{
	return mesh;
}
