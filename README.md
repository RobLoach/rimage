# Use [pntr](https://github.com/robloach/pntr) instead

# rimage

*rimage* provides basic image functions for loading and manipulating basic 2D bitmap data, forked from [raylib](https://github.com/raysan5/raylib)'s [textures](https://github.com/raysan5/raylib/blob/master/src/rtextures.c) module.

## Usage

``` c
#define SUPPORT_FILEFORMAT_PNG
#define RIMAGE_IMPLEMENTATION
#include "rimage.h"

int main() {
    Image image = LoadImage("cat.png");

    ImageDrawCircle(&image, 30, 10, 30, SKYBLUE);
    ImageDrawRectangle(&image, 100, 100, 100, 140, GREEN);
    ImageDrawLine(&image, 50, 50, 200, 80, ORANGE);
    ImageDrawRectangle(&image, 20, 150, 50, 80, RED);

    ExportImage(image, "out.png");

    UnloadImage(image);

    return 0;
}
```

## Why Fork?

It would be great to be able to use the Image API within raylib without requiring a hard fork. See the [discussion about it](https://github.com/raysan5/raylib/discussions/2865) to see how you could help out.

## License

rimage is licensed under an unmodified zlib/libpng license, which is an OSI-certified, BSD-like license that allows static linking with closed source software. Check [LICENSE](LICENSE) for further details.

raylib uses internally some libraries for window/graphics/inputs management and also to support different file formats loading, all those libraries are embedded with and are available in [src/external](https://github.com/raysan5/raylib/tree/master/src/external) directory. Check [raylib dependencies LICENSES](https://github.com/raysan5/raylib/wiki/raylib-dependencies) on raylib Wiki for details.
