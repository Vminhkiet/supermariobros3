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
enum VenusState {
    MOVING_UP,
    MOVING_DOWN,
    WAITING_AT_TOP,
    WAITING_AT_BOTTOM
};
class CVenus : public CGameObject {
protected:
    float yStart;  // V? trí ban ??u theo tr?c y
    bool isShooting;  // Tr?ng thái b?n
    DWORD stateTime; // Th?i gian b?t ??u b?n
    VenusState state;
    int huong = 0;
    bool tren = true;
    bool trai = true;
    int type;
public:
    CVenus(float x, float y,int type) : CGameObject(x, y) {
        yStart = y;
        this->type = type;
        isShooting = false;
        vy = VENUS_SPEED;
        state = MOVING_UP;
        vx = 0;
        SetType(OBJECT_TYPE_VENUS);
    }
    int IsBlocking()
    {
        return 0;
    }
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void Render();
    void GetBoundingBox(float& l, float& t, float& r, float& b);
    void CreateBullet();
    void OnCollisionWith(LPCOLLISIONEVENT e);
};

typedef CVenus* LPVENUS;
