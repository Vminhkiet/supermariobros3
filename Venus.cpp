#include "Venus.h"
#include "Bullet.h"
#include "PlayScene.h"
void CVenus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
    CGameObject::Update(dt, coObjects);

    if (!isShooting && GetTickCount64() - shootTime > 2000 ) {  // Cứ mỗi 2 giây lại bắn một lần
        isShooting = true;
        shootTime = GetTickCount64();
        CreateBullet();
        isShooting = false;
        dung = false;
        xuong = true;
        len = false;
    }

    // Di chuyển lên xuống theo trục y
    if(!dung)
      y += vy * dt;
    else {
        len = false;
        xuong = false;
    }
    if (y < yStart - 32 || y > yStart) {
        dung = true;
        
        vy = -vy;
    }
}

void CVenus::Render() {
    CAnimations* animations = CAnimations::GetInstance();
    float x, y;
    CGame::GetInstance()->GetCamPos(x, y);
    if (x < this->x) {
        trai = true;
    }
    else {
        trai = false;
    }
    if (y < this->y) {
        tren = false;
    }
    else {
        tren = true;
    }
    if (trai) {
        if (tren) {
            if (len || xuong)
                animations->Get(11101)->Render(this->x, this->y);
            else 
                animations->Get(11105)->Render(this->x, this->y);
        }
        else {
            if (len || xuong)
                animations->Get(11103)->Render(this->x, this->y);
            else
                animations->Get(11107)->Render(this->x, this->y);
        }
    }
    else {
        if (tren) {
            if (len || xuong)
                animations->Get(11102)->Render(this->x, this->y);
            else
                animations->Get(11106)->Render(this->x, this->y);
        }
        else {
            if (len || xuong)
                animations->Get(11104)->Render(this->x, this->y);
            else
                animations->Get(11108)->Render(this->x, this->y);
        }
    }
}
void CVenus::CreateBullet() {
    float bx, by;
    bx = x;
    by = y;
    if (tren) {
        if (trai)
            huong = 1;
        else
            huong = 3;
    }
    else {
        if (trai)
            huong = 2;
        else
            huong = 4;
    }
    LPGAMEOBJECT c = new CBullet(bx, by, huong);
    CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
    currentScene->AddObject(c);
}
void CVenus::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

        left = x - 15 / 2;
        top = y - 20 / 2;
        right = left + 15;
        bottom = top + 20;
}