
#include "Grid.h"

CGrid::CGrid(int columnCount, int rowCount, float cellWidth, float cellHeight)
{
    this->columnCount = columnCount;
    this->rowCount = rowCount;
    this->cellWidth = cellWidth;
    this->cellHeight = cellHeight;

    cells.resize(rowCount);
    for (int i = 0; i < rowCount; ++i)
    {
        cells[i].resize(columnCount);
    }
}

CGrid::~CGrid()
{
    // Hủy các đối tượng trong grid nếu cần thiết
}

void CGrid::InsertObject(LPGAMEOBJECT object)
{
    float oleft, otop, oright , obotton;
    object->GetBoundingBox(oleft, otop, oright , obotton);

    int startCol = static_cast<int>(oleft / cellWidth);
    int endCol = static_cast<int>(oright / cellWidth);
    int startRow = static_cast<int>(otop / cellHeight);
    int endRow = static_cast<int>(obotton / cellHeight);

    for (int row = startRow; row <= endRow; ++row)
    {
        for (int col = startCol; col <= endCol; ++col)
        {
            if (col >= 0 && col < columnCount && row >= 0 && row < rowCount)
            {
                cells[row][col].insert(object);
            }
        }
    }
}

void CGrid::GetObjectsInViewport(std::vector<LPGAMEOBJECT>& objects)
{
    float camX, camY;
    CGame::GetInstance()->GetCamPos(camX, camY);
    int screenWidth = SCREEN_WIDTH;
    int screenHeight = SCREEN_HEIGHT;

    float left = camX;
    float top = camY;
    float right = camX + screenWidth;
    float bottom = camY + screenHeight;

    int startCol = static_cast<int>(left / cellWidth);
    int endCol = static_cast<int>(right / cellWidth);
    int startRow = static_cast<int>(top / cellHeight);
    int endRow = static_cast<int>(bottom / cellHeight);

    std::set<LPGAMEOBJECT> uniqueObjects;

    for (int row = startRow; row <= endRow; ++row)
    {
        for (int col = startCol; col <= endCol; ++col)
        {
            if (col >= 0 && col < columnCount && row >= 0 && row < rowCount)
            {
                for (LPGAMEOBJECT object : cells[row][col])
                {
                    uniqueObjects.insert(object);
                }
            }
        }
    }

    for (auto iter : uniqueObjects)
    {
        objects.push_back(iter);
    }

    for (auto iter : moveObjects)
    {
        objects.push_back(iter);
    }
}

void CGrid::Update(DWORD dt)
{
    // Chỉ cập nhật các đối tượng động
    for (auto iter : moveObjects)
    {
        iter->Update(dt);
    }
}