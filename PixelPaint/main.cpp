#include <raylib.h>
#include <iostream>
#include <vector>
#define MAX_INPUT_CHARS     7

using namespace std;

class App
{
public:
    struct ColorPallete{
        int x;
        int y;
        Color color;
    };

    int cellSize;
    int mapWidth;
    int mapHeight;
    int borderSize;
    int startX;
    int startY;
    Color cellColors[71][53]; // 2D array to store the color of each cell
    Color selectedColor; // Color selected by the user

    int palleteX;
    int palleteY;
    int palleteWidth;
    int palleteHeight;
    int palleteBorder;
    vector<Color> colorPallete;
    vector<ColorPallete> palleteLoc;

    App()
    {
        ColorPallete cP;
        //Cells
        cellSize = 10;
        mapWidth = 71;
        mapHeight = 53;
        borderSize = 1;
        startX = 20;
        startY = 200;

        //PALLETE
        palleteX = 50;
        palleteY = 50;
        palleteWidth = 100;
        palleteHeight = 50;
        palleteBorder = 10;
        colorPallete = {WHITE,RED,BLUE,ORANGE,YELLOW,GREEN,GRAY,BLACK,BROWN,
        PURPLE,PINK,LIGHTGRAY,DARKBLUE,DARKBROWN,DARKGRAY,DARKGREEN,DARKPURPLE,BEIGE,LIME,SKYBLUE,MAROON};

        selectedColor = WHITE; // Default selected color

        // Initialize all cell colors to WHITE
        for (int x = 0; x < mapWidth; x++)
        {
            for (int y = 0; y < mapHeight; y++)
            {
                cellColors[x][y] = WHITE;
            }
        }
    }



    void Draw()
    {
        // Draw cells
        for (int x = 0; x < mapWidth; x++)
        {
            for (int y = 0; y < mapHeight; y++)
            {
                DrawRectangle(x * cellSize + startX, y * cellSize + startY, cellSize - borderSize, cellSize - borderSize, cellColors[x][y]);
            }
        }
        palleteX = 20;
        palleteY = 50;

        DrawText("Pixel Art",GetScreenWidth()/2 - 100,10,40,WHITE);

        // Draw Pallete
        for(int x = 0; x < colorPallete.size(); x++){
            if(palleteX >= GetScreenWidth() - palleteWidth) 
            {
                palleteY += 50;
                palleteX = 20;
            }
            DrawRectangle(palleteX - 2 , palleteY - 2, palleteWidth - palleteBorder + 4, palleteHeight - palleteBorder + 4,WHITE);
            DrawRectangle(palleteX , palleteY, palleteWidth - palleteBorder, palleteHeight - palleteBorder, colorPallete[x]);
            ColorPallete cp = {palleteX,palleteY,colorPallete[x]};
            palleteLoc.push_back(cp);
            palleteX += 100;
        }
        
    }

    void Update()
    {

        int mouseX = GetMouseX();
        int mouseY = GetMouseY();

        // Update selected color based on mouse input
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {

            for(auto cp : palleteLoc){
                if(mouseX == cp.x && mouseY == cp.y)
                {
                    selectedColor = cp.color;
                } 
            }
            for(int i = 0; i < palleteLoc.size();i++)
            {
                if(mouseX >= palleteLoc[i].x && mouseX < palleteLoc[i].x + palleteWidth - palleteBorder && mouseY >= palleteLoc[i].y && mouseY < palleteLoc[i].y + palleteHeight - palleteBorder)
                {
                    selectedColor = palleteLoc[i].color;
                } 
            }

            int cellX = (mouseX - startX) / cellSize;
            int cellY = (mouseY - startY) / cellSize;

            // Check if mouse click is within the map bounds
            if (cellX >= 0 && cellX < mapWidth && cellY >= 0 && cellY < mapHeight)
            {
                cellColors[cellX][cellY] = selectedColor; // Change color of the clicked cell
            }
        }
    }
};

int main()
{
    InitWindow(750, 750, "Draw 2D");
    SetTargetFPS(60);

    App app;

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        app.Update(); // Update selected color and cell colors based on mouse input
        app.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
