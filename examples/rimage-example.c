#define SUPPORT_FILEFORMAT_PNG
#define RIMAGE_IMPLEMENTATION
#include "rimage.h"

int main() {
    // Load
    Image image = LoadImage("resources/carlsagan.png");

    // Draw
    ImageDrawCircle(&image, 20, 20, 10, RED);
    ImageDrawLine(&image, 200, 10, 80, 300, BLUE);
    ImageDrawRectangle(&image, 10, 150, 50, 40, GREEN);

    // Export
    ExportImage(image, "out.png");

    // Unload
    UnloadImage(image);

    return 0;
}
