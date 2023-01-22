#define SUPPORT_FILEFORMAT_PNG
#define RIMAGE_IMPLEMENTATION
#include "rimage.h"

#include <assert.h>

#include <stdio.h>

int main() {
    // LoadImage
    Image image = LoadImage("resources/carlsagan.png");
    assert(image.width == 256);
    assert(image.height == 221);

    // ImageResizeNN
    {
        ImageResizeNN(&image, 500, 600);
        assert(image.width == 500);
        assert(image.height == 600);
    }

    // Font
    {
        Font font = LoadFont("resources/font.ttf");
        Vector2 position = {10, 10};
        ImageDrawTextEx(&image, font, "Hello World", position, 10.0f, 0.0f, RED);
        UnloadFont(font);
    }

    // Unload
    UnloadImage(image);

    return 0;
}
