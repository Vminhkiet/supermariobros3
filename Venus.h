#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"

#define VENUS_WIDTH 16
#define VENUS_HEIGHT 24
#define VENUS_SPEED -0.05f
#define VENUS_BULLET_SPEED 0.2f

#define ID_ANI_VENUS 20001
#define ID_ANI_VENUS_BULLET 20002

class CVenus : public CGameObject {
protected:
    float yStart;  // V? trí ban ??u theo tr?c y
    bool isShooting;  // Tr?ng thái b?n
    DWORD shootTime;  // Th?i gian b?t ??u b?n
    int huong = 0;
    bool len = true;
    bool xuong = false;
    bool tren = true;
    bool trai = true;
    bool dung = false;
public:
    CVenus(float x, float y) : CGameObject(x, y) {
        yStart = y;
        isShooting = false;
        vy = VENUS_SPEED;
        vx = 0;
        SetType(OBJECT_TYPE_VENUS);
    }

    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void Render();
    void GetBoundingBox(float& l, float& t, float& r, float& b);
    void CreateBullet();
};

typedef CVenus* LPVENUS;
