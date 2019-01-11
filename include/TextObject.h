// ---------------------------------------------------------------------------
// Project Name	:	Alpha Engine
// File Name		:	TextObject.h
// Author				:	Jeremy Kings
// Creation Date	:	2017/03/14
// Purpose			:	Game object that displays text.
// History			: 
// - 
// ---------------------------------------------------------------------------
#pragma once

#include "AEEngine.h"
#include "TextManager.h"
#include <string>
#include "FontTypes.h"

class TextObject
{
public:
	////////////////////////////////////////////////////////////////////////////////////
	// Constructor for TextObject. Needs an object name, the text to display, and the //
	// font type to use for the text.                                                 //
	////////////////////////////////////////////////////////////////////////////////////
	TextObject(std::string name, std::string text, FontTypes font);

	////////////////////////////////////////////////////////////////////////////////////
	// Destructor for TextObject. Frees mesh for text object.                         //
	////////////////////////////////////////////////////////////////////////////////////
	~TextObject();

	////////////////////////////////////////////////////////////////////////////////////
	// Marks text object as ready for deletion. Will be deleted by TextManager during //
	// the next update.                                                               //
	////////////////////////////////////////////////////////////////////////////////////
	void Kill();

	// Accessors
	boolean IsDead() const;
	const std::string& GetText() const;
	AEVec2 GetPosition() const;
	AEVec2 GetScale() const;
	const float* GetColor() const;
	const std::string& GetName() const;

	// Mutators
	void SetText(std::string text);
	void SetPosition(AEVec2 position);
	void SetPosition(float x, float y);
	void SetScale(float x, float y);
	void SetColor(float r, float g, float b, float a);
	
	// Helper accessors - client shouldn't need to use these
	AEGfxVertexList* GetMesh() const;
	FontTypes GetFontType() const;

private:
	// Private helper functions
	void ChangeText();

	boolean isDead;
	float modulationColor[4];
	AEVec2 pos;
	AEVec2 scale;

	std::string text;

	float width = 0.0f;
	float height = 0.0f;

	FontTypes fontType;
	AEGfxVertexList* mesh;
	std::string name;
};
