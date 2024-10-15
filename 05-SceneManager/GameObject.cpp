#include <d3dx9.h>
#include <algorithm>


#include "debug.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "AssetIDs.h"
#include "Sprites.h"

CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = 1;	
	state = -1;
	isDeleted = false;
	type = 0;
}

void CGameObject::RenderBoundingBox()
{
	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy; 
    CGame::GetInstance()->GetCamPos(cx, cy);

	if(this->GetType()== OBJECT_TYPE_GROUND)
	   CGame::GetInstance()->Draw(x+(int)(r-l)/2 - cx, y + (int)(b-t)/2 - cy, bbox, &rect, BBOX_ALPHA);
	else
		CGame::GetInstance()->Draw(x  - cx, y - cy, bbox, &rect, BBOX_ALPHA);
}

CGameObject::~CGameObject()
{

}