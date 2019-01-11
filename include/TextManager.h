// ---------------------------------------------------------------------------
// Project Name	:	Alpha Engine
// File Name		:	TextManager.h
// Author				:	Jeremy Kings
// Creation Date	:	2017/03/14
// Purpose			:	Manages and renders all text objects.
// History			: 
// - 
// ---------------------------------------------------------------------------
#pragma once

#include "AEEngine.h"
#include <stdio.h>
#include <map>
#include <vector>

typedef class TextObject TextObject;
typedef enum FontTypes FontTypes;
typedef class CharacterSet CharacterSet;

class TextManager
{
public:
	////////////////////////////////////////////////////////////////////////////////////
	// Constructor for TextManager. Needs to know where fonts are located relative to //
	// your project directory.                                                        //
	////////////////////////////////////////////////////////////////////////////////////
	TextManager(std::string fontImagePrefix);

	////////////////////////////////////////////////////////////////////////////////////
	// Called during level Load - add character sets before calling TextManager Load. //
	// List of font types can be found in FontTypes.h.                                //
	////////////////////////////////////////////////////////////////////////////////////
	static void AddCharacterSet(std::string name, FontTypes type);

	////////////////////////////////////////////////////////////////////////////////////
	// Called during level Load - loads texture for each character set. Call after    //
	// all character sets are added with AddCharacterSet.                             //
	////////////////////////////////////////////////////////////////////////////////////
	static void Load();

	////////////////////////////////////////////////////////////////////////////////////
	// Removes dead objects and draws any text objects still remaining. Call during   //
	// your engine's draw phase.                                                      //
	////////////////////////////////////////////////////////////////////////////////////
	static void Update();

	////////////////////////////////////////////////////////////////////////////////////
	// Destroys all text objects. Call during level Free.                             //
	////////////////////////////////////////////////////////////////////////////////////
	static void Free();

	////////////////////////////////////////////////////////////////////////////////////
	// Unloads font textures. Call during level Unload.                               //
	////////////////////////////////////////////////////////////////////////////////////
	static void Unload();

	////////////////////////////////////////////////////////////////////////////////////
	// Retrieve an object using its name, returning a pointer to it.                  //
	////////////////////////////////////////////////////////////////////////////////////
	static TextObject* GetObjectByName(const std::string& name);

	// Public helper functions
	static const std::string& GetPrefix(); // Returns the font directory
	static const CharacterSet* GetCharacterSet(FontTypes type); // Called automatically by TextObject::ChangeText
	static void AddTextObject(TextObject* textObject); // Called automatically by TextObject constructor

private:
	// Private helper functions
	static void Draw();
	static void DestroyAllDeadTextObjects();
	static void ClearData();
	static void RemoveAllTextObjects();

	// Private data
	static TextManager* instance;
	static std::vector<TextObject*> textObjects;
	static std::map<FontTypes, CharacterSet*> characterSets;
	static std::map<FontTypes, AEGfxTexture*> textures;
	static std::string fontImagePrefix;
};
