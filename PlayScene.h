#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Mario.h"
#include "Goomba.h"
#include "TileMap.h"
#include "Grid.h"
//#include "Koopas.h"

struct Object {
    string name;
    LPGAMEOBJECT obj;
    float x, y;
};

class CPlayScene : public CScene
{
protected:
    LPGAMEOBJECT player;
    LPTILEMAP tileMap;
    LPGRID grid;
    vector<LPGAMEOBJECT> objects;
    vector<LPGAMEOBJECT> venus;
    vector<std::pair<Object, bool>> spawn;
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
    void Spawn(Object s);
    vector<std::pair<Object, bool>> getspawn() {
        return spawn;
    }
    void findgetposition(float& x, float& y, string name) {
        for (auto i : spawn) {
            if (i.first.name == name) {
                x = i.first.x;
                y = i.first.y;
                break;
            }
        }
    }
    vector<LPGAMEOBJECT> getobjects() {
        return objects;
    }
    void deleteenime(float cx, float cy,float vx);
    void AddObject(LPGAMEOBJECT obj, LPGAMEOBJECT referenceObj = nullptr);
    void Clear();
    void PurgeDeletedObjects();

    static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;
