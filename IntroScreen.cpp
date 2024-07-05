#include "IntroScreen.h"
#include "PlayScene.h"
#include "Grass.h"
#include "Ground.h"
#include "NODE.h"
#include "Utils.h"
#include "TileMap.h"
#include "ItemEn.h"
CScene1* CScene1::__instance = NULL;
void CScene1::Loadfile() {
    LoadResource("textures\\introworldmap.json");
}

void CScene1::Update(DWORD dt)
{
	
	
	vector<CGameObject*> coObjects;

	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->IsDeleted() == false)
			coObjects.push_back(objects[i]);
	}
	mariored->Update(dt, &coObjects);
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->IsDeleted() == false)
			objects[i]->Update(dt, &coObjects);
	}
	tileMap->Update(dt, &objects);
}
void CScene1::Render() {
	if (tileMap)
		if (tileMap->getload())
			tileMap->Draw({ 25,228 },255,true);
	
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->IsDeleted() == false)
			objects[i]->Render();
	}
	mariored->Render();
}
CScene1* CScene1::GetInstance()
{
	if (__instance == NULL) __instance = new CScene1();
	return __instance;
}

void CScene1::Setitem(vector<LPGAMEOBJECT>& objects, LPGAMEOBJECT& player) {
	Loadfile();

	mariored = (CMario*)player;

	for (auto i : this->objects) {
		objects.push_back(i);
	}
}
void CScene1::LoadResource(string s) {
	D3DXCOLOR blackColor = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	CGame::GetInstance()->SetBackgroundColor(blackColor);
	LPGAME game = CGame::GetInstance();
	// Khởi tạo TileMap và Grid
	tileMap = new CTileMap();
	//grid = new CGrid(40, 30, 16, 16);

	// Load dữ liệu từ tệp JSON
	tileMap->LoadFromFile(ToLPCWSTR(s));

	// Lặp qua các layer trong tệp JSON để tìm các đối tượng
	ifstream file(s);
	json j = json::parse(file);
	for (auto& layer : j["layers"]) {
		if (layer["name"] == "grass") {
			for (auto& object : layer["objects"]) {
				Grass* grass = new Grass(float(object["x"]) + 19 , float(object["y"]));
				objects.push_back(grass);
			}
		}
		else if (layer["name"] == "Ground") {
			for (auto& object : layer["objects"]) {
				// Tạo đối tượng portal từ dữ liệu trong tệp JSON

				CGround* ground = new CGround(
					float(object["x"]) + 19,
					float(object["y"]) + 1,
					object["width"],
					object["height"]
				);
				// Thêm portal vào danh sách đối tượng của Scene
				objects.push_back(ground);
				// Thêm portal vào Grid
				//grid->InsertObject(ground);
			}
		}
		else if (layer["name"] == "NODE") {
			for (auto& object : layer["objects"]) {
				NODE* grass = new NODE(float(object["x"]) + 19, float(object["y"]),object["name"]);
				objects.push_back(grass);
			}
		}
		else if (layer["name"] == "Item") {
			for (auto& object : layer["objects"]) {
				ItemEn* grass = new ItemEn(float(object["x"]) + 19, float(object["y"]));
				objects.push_back(grass);
			}
		}
	}


}
