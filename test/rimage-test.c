#define SUPPORT_FILEFORMAT_JPG
#define RIMAGE_IMPLEMENTATION
#include "rimage.h"

#include <assert.h>

int main() {
    Image image = LoadImage("resources/carlsagan.jpg");

    ImageResizeNN(&image, 500, 600);

    assert(image.width == 500);

    return 0;
}
