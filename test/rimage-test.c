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

    // Unload
    UnloadImage(image);

    return 0;
}
