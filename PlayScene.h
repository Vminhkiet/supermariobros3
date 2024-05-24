#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "TileMap.h"
#include "Grid.h"
//#include "Koopas.h"

class CPlayScene : public CScene
{
protected:
    LPGAMEOBJECT player;
    LPTILEMAP tileMap;
    LPGRID grid;
    vector<LPGAMEOBJECT> objects;
    void _ParseSection_SPRITES(string line);
    void _ParseSection_ANIMATIONS(string line);

    void _ParseSection_ASSETS(string line);
    void _ParseSection_OBJECTS(string line);

    void LoadAssets(LPCWSTR assetFile);

public:
    CPlayScene(int id, LPCWSTR filePath);

    virtual void Load();
    virtual void LoadResource(string s);
    virtual void Update(DWORD dt);
    virtual void Render();
    virtual void Unload();

    LPGAMEOBJECT GetPlayer() { return player; }
    void AddObject(LPGAMEOBJECT obj, LPGAMEOBJECT referenceObj = nullptr);
    void Clear();
    void PurgeDeletedObjects();

    static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;
