#include <raylib.h>
#include <iostream>

using namespace std;



int main()
{
    InitWindow(750, 750, "Test");
    SetTargetFPS(60);
    while(WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();


    }
    CloseWindow();
    return 0;
} 