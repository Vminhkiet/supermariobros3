#pragma once

#include "Scene.h"

class CSampleKeyHandler: public CSceneKeyHandler
{
	bool a = false;
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CSampleKeyHandler(LPSCENE s) :CSceneKeyHandler(s) {};
};
