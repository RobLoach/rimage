#define SUPPORT_FILEFORMAT_PNG
#define RIMAGE_IMPLEMENTATION
#include "rimage.h"

#include <stdio.h>

int main() {
    // Load
    Image image = LoadImage("resources/carlsagan.png");

    // Draw
    ImageDrawCircle(&image, 20, 20, 10, RED);
    ImageDrawLine(&image, 200, 10, 80, 300, BLUE);
    ImageDrawRectangle(&image, 10, 150, 50, 40, GREEN);

    // Font
    Font font = LoadFont("resources/font.ttf");

    // ImageDrawTextEx
    Vector2 position = {10, 40};
    ImageDrawTextEx(&image, font, "Hello World!", position, 40.0f, 0.0f, PURPLE);

    // Export
    ExportImage(image, "out.png");

    // Unload
    UnloadImage(image);
    UnloadFont(font);

    return 0;
}
