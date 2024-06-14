#include "IntroScreen.h"
#include "PlayScene.h"
#include "Grass.h"
#include "Utils.h"
#include "TileMap.h"
CScene1* CScene1::__instance = NULL;
void CScene1::Loadfile() {
    LoadResource("textures\\world-1-1-map.json");
}

void CScene1::Update(DWORD dt)
{
	
	
	vector<CGameObject*> coObjects;

	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->IsDeleted() == false)
			coObjects.push_back(objects[i]);
	}
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
			tileMap->Draw({ 0,0 });
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->IsDeleted() == false)
			objects[i]->Render();
	}
}
CScene1* CScene1::GetInstance()
{
	if (__instance == NULL) __instance = new CScene1();
	return __instance;
}

void CScene1::Setitem(vector<LPGAMEOBJECT>& objects, LPGAMEOBJECT& player) {
	mariored = new CMario(10, 150, 0);
	mariored->SetLevel(MARIO_LEVEL_SMALL);

	player = mariored;

	for (auto i : this->objects) {
		objects.push_back(i);
	}
}
void CScene1::LoadResource(string s) {
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
		if (layer["name"] == "Grass") {
			for (auto& object : layer["objects"]) {
				Grass* grass = new Grass(float(object["x"]), float(object["y"]));
				objects.push_back(grass);
			}
		}

	}


}
