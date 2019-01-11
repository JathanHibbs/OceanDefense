// ---------------------------------------------------------------------------
// Project Name	:	Alpha Engine
// File Name		:	TextManager.cpp
// Author				:	Jeremy Kings
// Creation Date	:	2017/03/14
// Purpose			:	Manages and renders all text objects.
// History			: 
// - 
// ---------------------------------------------------------------------------
#include "TextManager.h"

#include <fstream>
#include "TextObject.h"
#include "CharacterSet.h"
#include <algorithm>

TextManager* TextManager::instance = NULL;
std::string TextManager::fontImagePrefix = "";
typedef std::map<FontTypes, CharacterSet*> CharacterSetMap;
CharacterSetMap TextManager::characterSets;
typedef std::map<FontTypes, AEGfxTexture*> TextureMap;
TextureMap TextManager::textures;
std::vector<TextObject*> TextManager::textObjects;

TextManager::TextManager(std::string fontImagePrefix)
{
	AE_ASSERT_MESG(instance == NULL, "ERROR: Can't have more than one TextManager!");

	instance = this;

	TextManager::fontImagePrefix = fontImagePrefix;
}

void TextManager::AddCharacterSet(std::string name, FontTypes type)
{
	CharacterSet* cs = new CharacterSet(name);
	characterSets[type] = cs;
}

void TextManager::Load()
{
	// Load textures for each character set based on font names
	for (CharacterSetMap::iterator it = characterSets.begin(); it != characterSets.end(); ++it)
	{
		std::string textureName = fontImagePrefix + it->second->GetTextureName();
		textures[it->first] = AEGfxTextureLoad(textureName.c_str());
	}
}

void TextManager::Update()
{
	DestroyAllDeadTextObjects();
	Draw();
}

void TextManager::Free()
{
	ClearData();
}

void TextManager::Unload()
{
	for (TextureMap::iterator it = textures.begin(); it != textures.end(); ++it)
		AEGfxTextureUnload(it->second);

	textures.clear();
	characterSets.clear();
}

const std::string& TextManager::GetPrefix()
{
	return fontImagePrefix;
}

void TextManager::AddTextObject(TextObject* textObject) 
{
	textObjects.push_back(textObject);
}

TextObject* TextManager::GetObjectByName(const std::string& name)
{
	std::vector<TextObject*>::iterator it;
	TextObject* obj = NULL;

	for (it = textObjects.begin(); it != textObjects.end(); ++it)
	{
		obj = *it;
		if (obj->GetName() == name)
		{
			return obj;
		}
	}

	return obj;
}

const CharacterSet* TextManager::GetCharacterSet(FontTypes type)
{
	return characterSets.find(type)->second;
}

boolean IsNull(const TextObject* object)
{
	return object == NULL;
}

void TextManager::DestroyAllDeadTextObjects()
{
	// Delete all dead objects
	int count = 0;
	for (std::vector<TextObject*>::iterator it = textObjects.begin(); it != textObjects.end(); ++it)
	{
		if ((*it)->IsDead())
		{
			delete *it;
			*it = NULL;
			count++;
		}
	}

	if (count > 0)
		AESysPrintf("Deleted: %i\n", count);
	// Remove all NULL objects
	std::vector<TextObject*>::iterator newEnd = std::remove_if(textObjects.begin(), textObjects.end(), IsNull);

	// Remove dead objects from array
	textObjects.erase(newEnd, textObjects.end());
}

void TextManager::Draw()
{
	// Make sure transparency is supported
	//AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	unsigned size = textObjects.size();

	for (unsigned i = 0; i < size; ++i)
	{
		// Textures
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEGfxTextureSet(textures.find(textObjects[i]->GetFontType())->second, 0.0f, 0.0f);
		//AESysPrintf("text test");

		// Font color
		const float* color = textObjects[i]->GetColor();
		AEGfxSetBlendColor(color[0], color[1], color[2], color[3]);

		// Object position
		AEGfxSetFullTransform(textObjects[i]->GetPosition().x, textObjects[i]->GetPosition().y, 0.0f,
			textObjects[i]->GetScale().x, textObjects[i]->GetScale().y);

		// Draw using mesh in text object
		AEGfxMeshDraw(textObjects[i]->GetMesh(), AE_GFX_MDM_TRIANGLES);
	}
	AEGfxSetBlendColor(0, 0, 0, 0);
}

void TextManager::ClearData()
{
	RemoveAllTextObjects();
	textObjects.clear();
}

void TextManager::RemoveAllTextObjects()
{
	/*std::vector<TextObject*>::iterator it;

	for (it = textObjects.begin(); it != textObjects.end(); ++it)
	{
		TextObject* obj = *it;
		obj->Kill();
	}*/

	unsigned size = textObjects.size();

	for (unsigned i = 0; i < size; ++i)
		delete textObjects[i];
}
