#include "Venus.h"
#include "Bullet.h"
#include "Ground.h"
#include "PlayScene.h"
void CVenus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
    CGameObject::Update(dt, coObjects);
    DWORD now = GetTickCount64();

    switch (state) {
        case MOVING_UP: {
            y += vy * dt;
            if (y + 58 < yStart) {  // Lên tới đỉnh

                state = WAITING_AT_TOP;
                stateTime = now;
                vy = 0;
            }
            break;
        }
        case WAITING_AT_TOP: {
            float kx, ky;
            CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
            currentScene->GetPlayer()->GetPosition(kx, ky);
            if (now - stateTime >= 2000 ) { 
                // Đợi 2 giây tại đỉnh
                if( abs(kx - x) < 100 && type != 3)
                    CreateBullet();
                state = MOVING_DOWN;
                vy = -VENUS_SPEED;
                stateTime = now;  // Cập nhật thời gian bắt đầu di chuyển xuống
            }
            break;
        }
        case MOVING_DOWN: {
            y += vy * dt;
            if (y > yStart) {  // Xuống tới đáy
                y = yStart;
                state = WAITING_AT_BOTTOM;
                stateTime = now;
                vy = 0;
            }
            break;
        }
        case WAITING_AT_BOTTOM: {
            if (now - stateTime >= 2000) {  // Đợi 2 giây tại đáy
                state = MOVING_UP;
                vy = VENUS_SPEED;
                stateTime = now;  // Cập nhật thời gian bắt đầu di chuyển lên
            }
            break;
        }
    }
}

void CVenus::Render() {
    CAnimations* animations = CAnimations::GetInstance();
    float x, y;
    CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
    currentScene->GetPlayer()->GetPosition(x, y);
    if (type == 3) {
        animations->Get(11113)->Render(this->x, this->y);
        return;
    }
    if (x < this->x) {
        trai = true;
    }
    else {
        trai = false;
    }
    if (y < this->y) {
        tren = true;
    }
    else {
        tren = false;
    }
    if (trai) {
        if (tren) {
            if (state==MOVING_UP || state==MOVING_DOWN)
                if(type == 1)
                     animations->Get(11101)->Render(this->x, this->y);
                else
                    animations->Get(11109)->Render(this->x, this->y);
            else 
                if (type == 1)
                    animations->Get(11105)->Render(this->x, this->y);
                else
                    animations->Get(11114)->Render(this->x, this->y);
        }
        else {
            if (state == MOVING_UP || state == MOVING_DOWN)
                if (type == 1)
                    animations->Get(11103)->Render(this->x, this->y);
                else
                    animations->Get(11111)->Render(this->x, this->y);
            else
                if (type == 1)
                    animations->Get(11107)->Render(this->x, this->y);
                else
                    animations->Get(11116)->Render(this->x, this->y);
        }
    }
    else {
        if (tren) {
            if (state == MOVING_UP || state == MOVING_DOWN)
                if (type == 1)
                    animations->Get(11102)->Render(this->x, this->y);
                else
                    animations->Get(11110)->Render(this->x, this->y);
            else
                if (type == 1)
                    animations->Get(11106)->Render(this->x, this->y);
                else
                    animations->Get(11115)->Render(this->x, this->y);
        }
        else {
            if (state == MOVING_UP || state == MOVING_DOWN)
                if (type == 1)
                    animations->Get(11104)->Render(this->x, this->y);
                else
                    animations->Get(11112)->Render(this->x, this->y);
            else
                if (type == 1)
                    animations->Get(11108)->Render(this->x, this->y);
                else
                    animations->Get(11117)->Render(this->x, this->y);
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
void CVenus::OnCollisionWith(LPCOLLISIONEVENT e) {
    if (dynamic_cast<CGround*>(e->obj))
        return;
}