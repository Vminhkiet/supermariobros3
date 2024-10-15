#include <vector>
#include <set>
#include "GameObject.h"
#include "Game.h"

class CGrid
{
private:
    std::vector<std::vector<std::set<LPGAMEOBJECT>>> cells; // M?ng 2 chi?u ch?a các set ??i t??ng game
    int columnCount; // S? l??ng c?t c?a l??i
    int rowCount; // S? l??ng hàng c?a l??i
    float cellWidth; // Chi?u r?ng m?i ô l??i
    float cellHeight; // Chi?u cao m?i ô l??i
    std::set<LPGAMEOBJECT> moveObjects; // Các ??i t??ng ??ng

public:
    CGrid(int columnCount, int rowCount, float cellWidth, float cellHeight);
    ~CGrid();

    void InsertObject(LPGAMEOBJECT object);
    void GetObjectsInViewport(std::vector<LPGAMEOBJECT>& objects);
    void Update(DWORD dt);
};
typedef CGrid* LPGRID;