#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Brick.h"
#include "Die.h"
#include "Sprites.h"
#include "Portal.h"
#include "Finish.h"
#include "Swap.h"
#include "Coin.h"
#include "Platform.h"
#include "Curtain.h"
#include "Nen.h"
#include "Ground.h"
#include "QuestionBlock.h"
#include "TopGround.h"
#include "Venus.h"
#include "Koopa.h"
#include "Para.h"
#include "Goomba.h"
#include "Grass.h"
#include "Duoi.h"
#include "Intro.h"
#include "ParaKoopa.h"
#include "IntroScreen.h"
#include "SampleKeyEventHandler.h"


using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	
	player = NULL;
	key_handler = new CSampleKeyHandler(this);

}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	if (id != 1)
	{
		vector<string> tokens = split(line);
		CGameObject* obj;

		// skip invalid lines - an object set must have at least id, x, y
		if (tokens.size() < 2) return;

		int object_type = atoi(tokens[0].c_str());
		
		if (object_type == LOAD_RESOURCE)
		{
			LoadResource("textures\\world-1-1-map.json");
			return;
		}
		else if (object_type == -2) {
			CScene1::GetInstance()->LoadResource("textures\\introworldmap.json");
			return;
		}
		float x = (float)atof(tokens[1].c_str());
		float y = (float)atof(tokens[2].c_str());
	
			switch (object_type)
			{
			case OBJECT_TYPE_MARIO:
				if (player != NULL)
				{
					DebugOut(L"[ERROR] MARIO object was created before!\n");
					return;
				}
				obj = new CMario(x, y);
				player = (CMario*)obj;
				if (id == 3) {
					dynamic_cast<CMario*>(player)->setid(1016);
					dynamic_cast<CMario*>(player)->setay();
				}
				DebugOut(L"[INFO] Player object has been created!\n");
				return;
				break;
			case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x, y); break;
			case OBJECT_TYPE_BRICK: obj = new CBrick(x, y); break;
			case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;
			case OBJECT_TYPE_MAN: obj = new CCurtain(x, y); break;
			case OBJECT_TYPE_NEN: {

				obj = new CNEN(x, y); break;
			}
			case OBJECT_TYPE_MARIOGREEN: {

				obj = new CMario(x, y, 0, true);

				player = (CMario*)obj;
			}
			case OBJECT_TYPE_PLATFORM:
			{

				float cell_width = (float)atof(tokens[3].c_str());
				float cell_height = (float)atof(tokens[4].c_str());
				int length = atoi(tokens[5].c_str());
				int sprite_begin = atoi(tokens[6].c_str());
				int sprite_middle = atoi(tokens[7].c_str());
				int sprite_end = atoi(tokens[8].c_str());

				obj = new CPlatform(
					x, y,
					cell_width, cell_height, length,
					sprite_begin, sprite_middle, sprite_end
				);

				break;
			}

			case OBJECT_TYPE_PORTAL:
			{
				float r = (float)atof(tokens[3].c_str());
				float b = (float)atof(tokens[4].c_str());
				int scene_id = atoi(tokens[5].c_str());
				obj = new CPortal(x, y, r, b, scene_id);
			}

			break;


			default:
				DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
				return;
			}

			// General object setup
			obj->SetPosition(x, y);

			
			objects.push_back(obj);
	}
}
void CPlayScene::Spawn(Object s){
	float x = s.x;
	float y = s.y;
	string enemy = s.name;
	if (enemy == "Venus") {
		CVenus* gameObj = new CVenus(
			x ,
			y ,
			1
		);
		venus.push_back(gameObj);
	}
	else if (enemy == "Venus1") {
		CVenus* gameObj = new CVenus(
			x,
			y,
			3
		);
		venus.push_back(gameObj);
	}
	else if (enemy == "Venus3") {
		CVenus* gameObj = new CVenus(
			x,
			y,
			2
		);
		venus.push_back(gameObj);
	}
	else {
		if (s.name == "Troopa") {
			CKOOPA* koopa = new CKOOPA(
				x ,
				y 
			);
			// Thêm portal vào danh sách đối tượng của Scene
			objects.push_back(koopa);
			// Thêm portal vào Grid
			//grid->InsertObject(ground);
		}
		else if (s.name == "Paratroopa") {
			CParaKoopa* koopa = new CParaKoopa(
				x,
				y
			);
			// Thêm portal vào danh sách đối tượng của Scene
			objects.push_back(koopa);
			// Thêm portal vào Grid
			//grid->InsertObject(ground);
		}
		else if (s.name == "Troopa1") {
			CKOOPA* koopa = new CKOOPA(
				x,
				y,
				true
			);
			// Thêm portal vào danh sách đối tượng của Scene
			objects.push_back(koopa);
			// Thêm portal vào Grid
			//grid->InsertObject(ground);
		}
		else if (s.name == "Gooba") {
			CGoomba* goopa = new CGoomba(
				x ,
				y
			);
			// Thêm portal vào danh sách đối tượng của Scene
			objects.push_back(goopa);
			// Thêm portal vào Grid
			//grid->InsertObject(ground);
		}
		else if (s.name == "Para") {
			CPARA* koopa = new CPARA(
				x ,
				y 
			);
			// Thêm portal vào danh sách đối tượng của Scene
			objects.push_back(koopa);
			// Thêm portal vào Grid
			//grid->InsertObject(ground);
		}
	}
}
void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();
	
	if (id == 1)
	{
		Intro::GetInstance()->Setitem(objects, player);
	}
	else if (id == 3) {	
		CScene1::GetInstance()->Setitem(objects, player);
	}
	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	
	if (id == 1) {
		Intro::GetInstance()->Update(dt);
		CGame::GetInstance()->SetCamPos(0, 0 /*cy*/);
	}
	else if (id == 3) {
		CScene1::GetInstance()->Update(dt);
		CGame::GetInstance()->SetCamPos(0,0 /*cy*/);
	}
	else{
		//grid->Update(dt);
		float x, y;
		CGame::GetInstance()->GetCamPos(x, y);
		for (auto& i : spawn) {
			if (i.first.x >= x && i.first.x <= x + SCREEN_WIDTH && i.first.y >= y && i.first.y <= y + SCREEN_HEIGHT && !i.second) {
				i.second = true;
				Spawn(i.first);
			}
		}
		
		vector<LPGAMEOBJECT> coObjects;
		coObjects.push_back(player);
		
		for (size_t i = 0; i < objects.size(); i++)
		{
			coObjects.push_back(objects[i]);

		}
		for (auto& obj : venus)
		{
			coObjects.push_back(obj);
		}
		if (this->getpause()) {
			player->Update(dt, &coObjects);
			return;
		}
		if (player != NULL) {
			player->Update(dt, &coObjects);
		}
       
	

		// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
		if (player == NULL) return;

		// Update camera to follow mario
		float cx, cy;
		player->GetPosition(cx, cy);
		CMario* mario = dynamic_cast<CMario*>(player);
		CGame* game = CGame::GetInstance();
		cx -= game->GetBackBufferWidth() / 2;
		cy -= game->GetBackBufferHeight() / 2;
		
		if (cx < 0) cx = 0;
		
		if (cx > 2503) cx = 2503;
		if (cy > 155) {
			cy = 240;
		}
		else if (mario->gettele() && cy < 150 && cy > 0) {
			cy = 0;
		}
		else if (!mario->checkfly() && cy > -100 && !mario->gettele()) {
			cy = 0;
		}
		else if (mario->checkfly() && cy > 0 && !mario->gettele()) {
			cy = 0;
		}
		float vx, vy;
		mario->GetSpeed(vx, vy);
		deleteenime(cx, cy,vx);
		for (auto& obj : venus)
		{
			obj->Update(dt, &coObjects);
		}

		for (size_t i = 0; i < objects.size(); i++)
		{
			objects[i]->Update(dt, &coObjects);

		}
		CGame::GetInstance()->SetCamPos((int)cx, (int)cy);
		tileMap->Update(dt, &objects);

	}
	    

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	if (id == 1) {
		Intro::GetInstance()->Render();
	}
	else if (id == 3) {
		CScene1::GetInstance()->Render();
	}
	else {
		float x, y;
		CGame::GetInstance()->GetCamPos(x, y);
		tileMap->Draw({ 0,0 }, 255, true);
		bool tele = dynamic_cast<CMario*>(player)->gettele();
		if (tele)
			player->Render();
		for (auto i : venus) {
			i->Render();
		}
		if (tileMap && tileMap->getload()) {
			tileMap->Draw({ 0, 0 });
		}
		
		for (int i = 0; i < objects.size(); i++) {
			objects[i]->Render();
		}
		if (!tele)
			player->Render();
	}
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	for (auto it = venus.begin(); it != venus.end(); it++)
	{
		delete (*it);
	}
	
	spawn.clear();
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}
void CPlayScene::LoadResource(string s) {
	LPGAME game = CGame::GetInstance();
	if (id != 3) {
		D3DXCOLOR blueColor = D3DXCOLOR(0.53f, 0.81f, 0.92f, 1.0f);

		CGame::GetInstance()->SetBackgroundColor(blueColor);
	}
	else {
		
	}


	// Khởi tạo TileMap và Grid
	tileMap = new CTileMap();
	//grid = new CGrid(40, 30, 16, 16);

	// Load dữ liệu từ tệp JSON
	tileMap->LoadFromFile(ToLPCWSTR(s));
	
	// Lặp qua các layer trong tệp JSON để tìm các đối tượng
	ifstream file(s);
	json j = json::parse(file);
	for (auto& layer : j["layers"]) {
		if (layer["name"] == "Ground") {
			for (auto& object : layer["objects"]) {
				// Tạo đối tượng portal từ dữ liệu trong tệp JSON

				 CGround* ground = new CGround(
					float(object["x"])-2,
					float(object["y"])-228,
					 object["width"]-8,
					 object["height"]
				);
				// Thêm portal vào danh sách đối tượng của Scene
				objects.push_back(ground);
				// Thêm portal vào Grid
				//grid->InsertObject(ground);
			}
		}
		else if (layer["name"] == "Die") {
			for (auto& object : layer["objects"]) {
				// Tạo đối tượng portal từ dữ liệu trong tệp JSON

				CDie* ground = new CDie(
					float(object["x"]) - 2,
					float(object["y"]) - 228,
					object["width"] ,
					object["height"]
				);
				// Thêm portal vào danh sách đối tượng của Scene
				objects.push_back(ground);
				// Thêm portal vào Grid
				//grid->InsertObject(ground);
			}
		}
		else if (layer["name"] == "Finish") {
			for (auto& object : layer["objects"]) {
				// Tạo đối tượng portal từ dữ liệu trong tệp JSON
				Finish* ground = new Finish(
					float(object["x"]) - 7,
					float(object["y"]) - 226);
				// Thêm portal vào danh sách đối tượng của Scene
				objects.push_back(ground);
				// Thêm portal vào Grid
				//grid->InsertObject(ground);
			}
		}
		else if (layer["name"] == "TopGround") {
			for (auto& object : layer["objects"]) {
				// Tạo đối tượng portal từ dữ liệu trong tệp JSON

				CTop* ground = new CTop(
					float(object["x"]) - 2,
					float(object["y"]) - 228,
					object["width"]-8,
					object["height"]-15
				);
				// Thêm portal vào danh sách đối tượng của Scene
				objects.push_back(ground);
				// Thêm portal vào Grid
				//grid->InsertObject(ground);
			}
		}
		else if (layer["name"] == "Brick") {
			for (auto& object : layer["objects"]) {
				CBrick* brick = new CBrick(
					float(object["x"]) - 2,
					float(object["y"]) - 228
				);
				objects.push_back(brick);
			}
		}
		else if (layer["name"] == "Questionblock") {
			for (auto& object : layer["objects"]) {
				CQuestionblock* obj;
				if (object["name"] == "Coin") {
					obj = new CQuestionblock(
						float(object["x"]) - 8,
						float(object["y"]) - 228,
						1
					);
					objects.push_back(obj);
				}
				else if (object["name"] == "Nam") {
					obj = new CQuestionblock(
						float(object["x"]) - 8,
						float(object["y"]) - 228,
						2
					);
					objects.push_back(obj);
				}
				else if (object["name"] == "Leaf") {
					obj = new CQuestionblock(
						float(object["x"]) - 8,
						float(object["y"]) - 228,
						3
					);
					objects.push_back(obj);
				}
				else if (object["name"] == "NN") {
					obj = new CQuestionblock(
						float(object["x"]) - 8,
						float(object["y"]) - 228
					);
					objects.push_back(obj);
				}
				else if (object["name"] == "NN1") {
					obj = new CQuestionblock(
						float(object["x"]) - 2,
						float(object["y"]) - 228,
						0,
						true
					);
					objects.push_back(obj);
				}
				else if (object["name"] == "P") {
					obj = new CQuestionblock(
						float(object["x"]) - 2,
						float(object["y"]) - 228,
						4,
						true
					);
					objects.push_back(obj);
				}
				
			}
		}
		else if (layer["name"] == "Venus") {
			for (auto& object : layer["objects"]) {
				Object s;
				s.x = float(object["x"]) - 8;
				s.y = float(object["y"]) - 220;
				s.name = object["name"];
				spawn.push_back({ s,false });
				
			}
		}
		else if (layer["name"] == "Grass") {
			for (auto& object : layer["objects"]) {
				Grass* grass = new Grass(float(object["x"]), float(object["y"]));
				objects.push_back(grass);
			}
		}
		else if (layer["name"] == "Coin") {
			for (auto& object : layer["objects"]) {
				CCoin* grass = new CCoin(float(object["x"]) - 8, float(object["y"]) - 220);
				objects.push_back(grass);
			}
		}
		else if (layer["name"] == "Label") {
			for (auto& object : layer["objects"]) {
				if (object["name"] == "Swap1") {
					Swap* s=new Swap(float(object["x"]) - 8, float(object["y"]) - 228,true, object["width"]-2,object["height"] ,object["name"],true);
					objects.push_back(s);
				}
				else if (object["name"] == "Swap2") {
					Swap* s = new Swap(float(object["x"]) - 8, float(object["y"]) - 228, true, object["width"]-2, object["height"] , object["name"],false);
					objects.push_back(s);
				}
				else {
					Object s;
					s.x = float(object["x"]) - 8;
					s.y = float(object["y"]) - 220;
					s.name = object["name"];
					spawn.push_back({ s,false });
				}
			}
		}
		else if (layer["name"] == "Enime") {
			for (auto& object : layer["objects"]) {

				if (object["name"] == "Troopa") {

					Object s;
					s.x = float(object["x"]) - 8;
					s.y = float(object["y"]) - 250;
					s.name = object["name"];
					spawn.push_back({ s,false });

				}
				else if (object["name"] == "Troopa1") {

					Object s;
					s.x = float(object["x"]) - 8;
					s.y = float(object["y"]) - 250;
					s.name = object["name"];
					spawn.push_back({ s,false });

				}
				else if (object["name"] == "Paratroopa") {

					Object s;
					s.x = float(object["x"]) - 8;
					s.y = float(object["y"]) - 250;
					s.name = object["name"];
					spawn.push_back({ s,false });

				}
				else if (object["name"] == "Gooba") {
					Object s;
					s.x = float(object["x"]) - 8;
					s.y = float(object["y"]) - 250;
					s.name = "Gooba";
					spawn.push_back({ s,false });
				}
				else if (object["name"] == "Para") {
					Object s;
					s.x = float(object["x"]) - 8;
					s.y = float(object["y"]) - 250;
					s.name = "Para";
					spawn.push_back({ s,false });
				}
			}
		}
		
	}
	

}
void CPlayScene::AddObject(LPGAMEOBJECT obj, LPGAMEOBJECT referenceObj){
	if (referenceObj == nullptr) {
		objects.push_back(obj);
	}
	else {
		auto it = std::find(objects.begin(), objects.end(), referenceObj);
		if (it != objects.end()) {
			objects.insert(it, obj);  // Thêm obj trước referenceObj
		}
		else {
			objects.push_back(obj);
		}
	}
}

void CPlayScene::deleteenime(float cx,float cy,float vx) {
	for (auto& i : venus) {
		if (dynamic_cast<CVenus*>(i)) {

		}
	}
	for(auto& i:objects){
		float mx, my;
		/*
		if (dynamic_cast<CBrick*>(i)) {
			if (mx >= cx - SCREEN_WIDTH && mx <= cx + SCREEN_WIDTH && my >= cy && my <= cy + SCREEN_HEIGHT) {

			}
		}
		else if (dynamic_cast<CGoomba*>(i)) {
			if (mx >= cx - SCREEN_WIDTH && mx <= cx + SCREEN_WIDTH && my >= cy && my <= cy + SCREEN_HEIGHT) {

			}
		}
		else if (dynamic_cast<CPARA*>(i)) {

		}
		else*/ if (dynamic_cast<CKOOPA*>(i)) {
			CKOOPA* h = dynamic_cast<CKOOPA*>(i);
			if (h->Getstate() != 0)
				return;
			if (!h->getdie())
				continue;
			h->getstart(mx, my);
			if (vx > 0) {
				if (mx <= cx + SCREEN_WIDTH+10 && mx >= cx + SCREEN_WIDTH  && my >= cy && my <= cy + SCREEN_HEIGHT) {
					dynamic_cast<CKOOPA*>(i)->SetState(0);
					dynamic_cast<CKOOPA*>(i)->setres(true);
				}
			}
			else if (vx < 0) {
				if (mx >= cx + 30 && mx <= cx + 40 && my >= cy && my <= cy + SCREEN_HEIGHT) {
					dynamic_cast<CKOOPA*>(i)->SetState(0);
					dynamic_cast<CKOOPA*>(i)->setres(true);
				}
			}
		}
		else if (dynamic_cast<CParaKoopa*>(i)) {
			CParaKoopa* h = dynamic_cast<CParaKoopa*>(i);
			
			if (!h->getdie())
				continue;
			h->getstart(mx, my);
			if (vx > 0) {
				if (mx <= cx + SCREEN_WIDTH-50 && mx >= cx + SCREEN_WIDTH - 60 && my >= cy && my <= cy + SCREEN_HEIGHT) {
					dynamic_cast<CParaKoopa*>(i)->setcanh(true);
					dynamic_cast<CParaKoopa*>(i)->SetState(0);
					dynamic_cast<CParaKoopa*>(i)->setres(true);
				}
			}
			else if (vx < 0) {
				if (mx >= cx + 30 && mx <= cx + 40 && my >= cy && my <= cy + SCREEN_HEIGHT) {
					dynamic_cast<CParaKoopa*>(i)->setcanh(true);
					dynamic_cast<CParaKoopa*>(i)->SetState(0);
					dynamic_cast<CParaKoopa*>(i)->setres(true);
				}
			}
		}
		
		
	}
}