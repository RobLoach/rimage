/**********************************************************************************************
*
*   rimage - Basic functions to load and manipulate images.
*
*   CONFIGURATION:
*
*   #define RIMAGE_IMPLEMENTATION
*       This should be defined in one of your .c files before including.
*
*   #define SUPPORT_FILEFORMAT_BMP
*   #define SUPPORT_FILEFORMAT_PNG
*   #define SUPPORT_FILEFORMAT_TGA
*   #define SUPPORT_FILEFORMAT_JPG
*   #define SUPPORT_FILEFORMAT_GIF
*   #define SUPPORT_FILEFORMAT_QOI
*   #define SUPPORT_FILEFORMAT_PSD
*   #define SUPPORT_FILEFORMAT_HDR
*   #define SUPPORT_FILEFORMAT_PIC
*   #define SUPPORT_FILEFORMAT_PNM
*   #define SUPPORT_FILEFORMAT_DDS
*   #define SUPPORT_FILEFORMAT_PKM
*   #define SUPPORT_FILEFORMAT_KTX
*   #define SUPPORT_FILEFORMAT_PVR
*   #define SUPPORT_FILEFORMAT_ASTC
*       Select desired fileformats to be supported for image data loading. Some of those formats are
*       supported by default, to remove support, just comment unrequired #define in this module
*
*   #define SUPPORT_IMAGE_EXPORT
*       Support image export in multiple file formats
*
*   #define SUPPORT_IMAGE_MANIPULATION
*       Support multiple image editing functions to scale, adjust colors, flip, draw on images, crop...
*       If not defined only three image editing functions supported: ImageFormat(), ImageAlphaMask(), ImageToPOT()
*
*   #define SUPPORT_IMAGE_GENERATION
*       Support procedural image generation functionality (gradient, spot, perlin-noise, cellular)
*
*   DEPENDENCIES:
*       stb_image        - Multiple image formats loading (JPEG, PNG, BMP, TGA, PSD, GIF, PIC)
*                          NOTE: stb_image has been slightly modified to support Android platform.
*       stb_image_resize - Multiple image resize algorithms
*
*
*   LICENSE: zlib/libpng
*
*   Copyright (c) 2013-2023 Ramon Santamaria (@raysan5)
*   Copyright (c) 2022-2023 Rob Loach (@RobLoach)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/


#ifndef RIMAGE_H_INCLUDED
#define RIMAGE_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

// NOTE: MSVC C++ compiler does not support compound literals (C99 feature)
// Plain structures in C++ (without constructors) can be initialized with { }
#if defined(__cplusplus)
    #define CLITERAL(type)      type
#else
    #define CLITERAL(type)      (type)
#endif

// Function specifiers in case library is build/used as a shared library (Windows)
// NOTE: Microsoft specifiers to tell compiler that symbols are imported/exported from a .dll
#if defined(_WIN32)
    #if defined(BUILD_LIBTYPE_SHARED)
        #if defined(__TINYC__)
            #define __declspec(x) __attribute__((x))
        #endif
        #define RLAPI __declspec(dllexport)     // We are building the library as a Win32 shared library (.dll)
    #elif defined(USE_LIBTYPE_SHARED)
        #define RLAPI __declspec(dllimport)     // We are using the library as a Win32 shared library (.dll)
    #endif
#endif

#ifndef RLAPI
    #define RLAPI       // Functions defined as 'extern' by default (implicit specifiers)
#endif

//----------------------------------------------------------------------------------
// Some basic Defines
//----------------------------------------------------------------------------------

// NOTE: MSVC C++ compiler does not support compound literals (C99 feature)
// Plain structures in C++ (without constructors) can be initialized with { }
#if defined(__cplusplus)
    #define CLITERAL(type)      type
#else
    #define CLITERAL(type)      (type)
#endif

// Some Basic Colors
// NOTE: Custom raylib color palette for amazing visuals on WHITE background
#define LIGHTGRAY  CLITERAL(Color){ 200, 200, 200, 255 }   // Light Gray
#define GRAY       CLITERAL(Color){ 130, 130, 130, 255 }   // Gray
#define DARKGRAY   CLITERAL(Color){ 80, 80, 80, 255 }      // Dark Gray
#define YELLOW     CLITERAL(Color){ 253, 249, 0, 255 }     // Yellow
#define GOLD       CLITERAL(Color){ 255, 203, 0, 255 }     // Gold
#define ORANGE     CLITERAL(Color){ 255, 161, 0, 255 }     // Orange
#define PINK       CLITERAL(Color){ 255, 109, 194, 255 }   // Pink
#define RED        CLITERAL(Color){ 230, 41, 55, 255 }     // Red
#define MAROON     CLITERAL(Color){ 190, 33, 55, 255 }     // Maroon
#define GREEN      CLITERAL(Color){ 0, 228, 48, 255 }      // Green
#define LIME       CLITERAL(Color){ 0, 158, 47, 255 }      // Lime
#define DARKGREEN  CLITERAL(Color){ 0, 117, 44, 255 }      // Dark Green
#define SKYBLUE    CLITERAL(Color){ 102, 191, 255, 255 }   // Sky Blue
#define BLUE       CLITERAL(Color){ 0, 121, 241, 255 }     // Blue
#define DARKBLUE   CLITERAL(Color){ 0, 82, 172, 255 }      // Dark Blue
#define PURPLE     CLITERAL(Color){ 200, 122, 255, 255 }   // Purple
#define VIOLET     CLITERAL(Color){ 135, 60, 190, 255 }    // Violet
#define DARKPURPLE CLITERAL(Color){ 112, 31, 126, 255 }    // Dark Purple
#define BEIGE      CLITERAL(Color){ 211, 176, 131, 255 }   // Beige
#define BROWN      CLITERAL(Color){ 127, 106, 79, 255 }    // Brown
#define DARKBROWN  CLITERAL(Color){ 76, 63, 47, 255 }      // Dark Brown

#define WHITE      CLITERAL(Color){ 255, 255, 255, 255 }   // White
#define BLACK      CLITERAL(Color){ 0, 0, 0, 255 }         // Black
#define BLANK      CLITERAL(Color){ 0, 0, 0, 0 }           // Blank (Transparent)
#define MAGENTA    CLITERAL(Color){ 255, 0, 255, 255 }     // Magenta
#define RAYWHITE   CLITERAL(Color){ 245, 245, 245, 255 }   // My own White (raylib logo)

//----------------------------------------------------------------------------------
// Structures Definition
//----------------------------------------------------------------------------------
// Boolean type
#if (defined(__STDC__) && __STDC_VERSION__ >= 199901L) || (defined(_MSC_VER) && _MSC_VER >= 1800)
    #include <stdbool.h>
#elif !defined(__cplusplus) && !defined(bool)
    typedef enum bool { false = 0, true = !false } bool;
    #define RL_BOOL_TYPE
#endif

// Vector2, 2 components
typedef struct Vector2 {
    float x;                // Vector x component
    float y;                // Vector y component
} Vector2;

// Vector3, 3 components
typedef struct Vector3 {
    float x;                // Vector x component
    float y;                // Vector y component
    float z;                // Vector z component
} Vector3;

// Vector4, 4 components
typedef struct Vector4 {
    float x;                // Vector x component
    float y;                // Vector y component
    float z;                // Vector z component
    float w;                // Vector w component
} Vector4;

// Color, 4 components, R8G8B8A8 (32bit)
typedef struct Color {
    unsigned char r;        // Color red value
    unsigned char g;        // Color green value
    unsigned char b;        // Color blue value
    unsigned char a;        // Color alpha value
} Color;

// Rectangle, 4 components
typedef struct Rectangle {
    float x;                // Rectangle top-left corner position x
    float y;                // Rectangle top-left corner position y
    float width;            // Rectangle width
    float height;           // Rectangle height
} Rectangle;

// Image, pixel data stored in CPU memory (RAM)
typedef struct Image {
    void *data;             // Image raw data
    int width;              // Image base width
    int height;             // Image base height
    int mipmaps;            // Mipmap levels, 1 by default
    int format;             // Data format (PixelFormat type)
} Image;

// GlyphInfo, font characters glyphs info
typedef struct GlyphInfo {
    int value;              // Character value (Unicode)
    int offsetX;            // Character offset X when drawing
    int offsetY;            // Character offset Y when drawing
    int advanceX;           // Character advance position X
    Image image;            // Character image data
} GlyphInfo;

// Font, font texture and GlyphInfo array data
typedef struct Font {
    int baseSize;           // Base size (default chars height)
    int glyphCount;         // Number of glyph characters
    int glyphPadding;       // Padding around the glyph characters
    //Texture2D texture;      // Texture atlas containing the glyphs
    Image texture;          // rimage uses Image instead of Texture2D
    Rectangle *recs;        // Rectangles in texture for the glyphs
    GlyphInfo *glyphs;      // Glyphs info data
} Font;

//----------------------------------------------------------------------------------
// Enumerators Definition
//----------------------------------------------------------------------------------

// Trace log level
// NOTE: Organized by priority level
typedef enum {
    LOG_ALL = 0,        // Display all logs
    LOG_TRACE,          // Trace logging, intended for internal use only
    LOG_DEBUG,          // Debug logging, used for internal debugging, it should be disabled on release builds
    LOG_INFO,           // Info logging, used for program execution info
    LOG_WARNING,        // Warning logging, used on recoverable failures
    LOG_ERROR,          // Error logging, used on unrecoverable failures
    LOG_FATAL,          // Fatal logging, used to abort program: exit(EXIT_FAILURE)
    LOG_NONE            // Disable logging
} TraceLogLevel;

// Pixel formats
// NOTE: Support depends on OpenGL version and platform
typedef enum {
    PIXELFORMAT_UNCOMPRESSED_GRAYSCALE = 1, // 8 bit per pixel (no alpha)
    PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA,    // 8*2 bpp (2 channels)
    PIXELFORMAT_UNCOMPRESSED_R5G6B5,        // 16 bpp
    PIXELFORMAT_UNCOMPRESSED_R8G8B8,        // 24 bpp
    PIXELFORMAT_UNCOMPRESSED_R5G5B5A1,      // 16 bpp (1 bit alpha)
    PIXELFORMAT_UNCOMPRESSED_R4G4B4A4,      // 16 bpp (4 bit alpha)
    PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,      // 32 bpp
    PIXELFORMAT_UNCOMPRESSED_R32,           // 32 bpp (1 channel - float)
    PIXELFORMAT_UNCOMPRESSED_R32G32B32,     // 32*3 bpp (3 channels - float)
    PIXELFORMAT_UNCOMPRESSED_R32G32B32A32,  // 32*4 bpp (4 channels - float)
    PIXELFORMAT_COMPRESSED_DXT1_RGB,        // 4 bpp (no alpha)
    PIXELFORMAT_COMPRESSED_DXT1_RGBA,       // 4 bpp (1 bit alpha)
    PIXELFORMAT_COMPRESSED_DXT3_RGBA,       // 8 bpp
    PIXELFORMAT_COMPRESSED_DXT5_RGBA,       // 8 bpp
    PIXELFORMAT_COMPRESSED_ETC1_RGB,        // 4 bpp
    PIXELFORMAT_COMPRESSED_ETC2_RGB,        // 4 bpp
    PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA,   // 8 bpp
    PIXELFORMAT_COMPRESSED_PVRT_RGB,        // 4 bpp
    PIXELFORMAT_COMPRESSED_PVRT_RGBA,       // 4 bpp
    PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA,   // 8 bpp
    PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA    // 2 bpp
} PixelFormat;

// Font type, defines generation method
typedef enum {
    FONT_DEFAULT = 0,               // Default font generation, anti-aliased
    FONT_BITMAP,                    // Bitmap font generation, no anti-aliasing
    FONT_SDF                        // SDF font generation, requires external shader
} FontType;

//------------------------------------------------------------------------------------
// Texture Loading and Drawing Functions (Module: textures)
//------------------------------------------------------------------------------------

// Image loading functions
// NOTE: This functions do not require GPU access
RLAPI Image LoadImage(const char *fileName);                                                             // Load image from file into CPU memory (RAM)
RLAPI Image LoadImageRaw(const char *fileName, int width, int height, int format, int headerSize);       // Load image from RAW file data
RLAPI Image LoadImageAnim(const char *fileName, int *frames);                                            // Load image sequence from file (frames appended to image.data)
RLAPI Image LoadImageFromMemory(const char *fileType, const unsigned char *fileData, int dataSize);      // Load image from memory buffer, fileType refers to extension: i.e. '.png'
//RLAPI Image LoadImageFromTexture(Texture2D texture);                                                     // Load image from GPU texture data
//RLAPI Image LoadImageFromScreen(void);                                                                   // Load image from screen buffer and (screenshot)
RLAPI void UnloadImage(Image image);                                                                     // Unload image from CPU memory (RAM)
RLAPI bool ExportImage(Image image, const char *fileName);                                               // Export image data to file, returns true on success
//RLAPI bool ExportImageAsCode(Image image, const char *fileName);                                         // Export image as code file defining an array of bytes, returns true on success

// Image generation functions
RLAPI Image GenImageColor(int width, int height, Color color);                                           // Generate image: plain color
RLAPI Image GenImageGradientV(int width, int height, Color top, Color bottom);                           // Generate image: vertical gradient
RLAPI Image GenImageGradientH(int width, int height, Color left, Color right);                           // Generate image: horizontal gradient
RLAPI Image GenImageGradientRadial(int width, int height, float density, Color inner, Color outer);      // Generate image: radial gradient
RLAPI Image GenImageChecked(int width, int height, int checksX, int checksY, Color col1, Color col2);    // Generate image: checked
RLAPI Image GenImageWhiteNoise(int width, int height, float factor);                                     // Generate image: white noise
RLAPI Image GenImagePerlinNoise(int width, int height, int offsetX, int offsetY, float scale);           // Generate image: perlin noise
RLAPI Image GenImageCellular(int width, int height, int tileSize);                                       // Generate image: cellular algorithm, bigger tileSize means bigger cells
RLAPI Image GenImageText(int width, int height, const char *text);                                       // Generate image: grayscale image from text data

// Image manipulation functions
RLAPI Image ImageCopy(Image image);                                                                      // Create an image duplicate (useful for transformations)
RLAPI Image ImageFromImage(Image image, Rectangle rec);                                                  // Create an image from another image piece
RLAPI Image ImageText(const char *text, int fontSize, Color color);                                      // Create an image from text (default font)
RLAPI Image ImageTextEx(Font font, const char *text, float fontSize, float spacing, Color tint);         // Create an image from text (custom sprite font)
RLAPI void ImageFormat(Image *image, int newFormat);                                                     // Convert image data to desired format
RLAPI void ImageToPOT(Image *image, Color fill);                                                         // Convert image to POT (power-of-two)
RLAPI void ImageCrop(Image *image, Rectangle crop);                                                      // Crop an image to a defined rectangle
RLAPI void ImageAlphaCrop(Image *image, float threshold);                                                // Crop image depending on alpha value
RLAPI void ImageAlphaClear(Image *image, Color color, float threshold);                                  // Clear alpha channel to desired color
RLAPI void ImageAlphaMask(Image *image, Image alphaMask);                                                // Apply alpha mask to image
RLAPI void ImageAlphaPremultiply(Image *image);                                                          // Premultiply alpha channel
RLAPI void ImageBlurGaussian(Image *image, int blurSize);                                                // Apply Gaussian blur using a box blur approximation
RLAPI void ImageResize(Image *image, int newWidth, int newHeight);                                       // Resize image (Bicubic scaling algorithm)
RLAPI void ImageResizeNN(Image *image, int newWidth,int newHeight);                                      // Resize image (Nearest-Neighbor scaling algorithm)
RLAPI void ImageResizeCanvas(Image *image, int newWidth, int newHeight, int offsetX, int offsetY, Color fill);  // Resize canvas and fill with color
RLAPI void ImageMipmaps(Image *image);                                                                   // Compute all mipmap levels for a provided image
RLAPI void ImageDither(Image *image, int rBpp, int gBpp, int bBpp, int aBpp);                            // Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
RLAPI void ImageFlipVertical(Image *image);                                                              // Flip image vertically
RLAPI void ImageFlipHorizontal(Image *image);                                                            // Flip image horizontally
RLAPI void ImageRotateCW(Image *image);                                                                  // Rotate image clockwise 90deg
RLAPI void ImageRotateCCW(Image *image);                                                                 // Rotate image counter-clockwise 90deg
RLAPI void ImageColorTint(Image *image, Color color);                                                    // Modify image color: tint
RLAPI void ImageColorInvert(Image *image);                                                               // Modify image color: invert
RLAPI void ImageColorGrayscale(Image *image);                                                            // Modify image color: grayscale
RLAPI void ImageColorContrast(Image *image, float contrast);                                             // Modify image color: contrast (-100 to 100)
RLAPI void ImageColorBrightness(Image *image, int brightness);                                           // Modify image color: brightness (-255 to 255)
RLAPI void ImageColorReplace(Image *image, Color color, Color replace);                                  // Modify image color: replace color
RLAPI Color *LoadImageColors(Image image);                                                               // Load color data from image as a Color array (RGBA - 32bit)
RLAPI Color *LoadImagePalette(Image image, int maxPaletteSize, int *colorCount);                         // Load colors palette from image as a Color array (RGBA - 32bit)
RLAPI void UnloadImageColors(Color *colors);                                                             // Unload color data loaded with LoadImageColors()
RLAPI void UnloadImagePalette(Color *colors);                                                            // Unload colors palette loaded with LoadImagePalette()
RLAPI Rectangle GetImageAlphaBorder(Image image, float threshold);                                       // Get image alpha border rectangle
RLAPI Color GetImageColor(Image image, int x, int y);                                                    // Get image pixel color at (x, y) position

// Image drawing functions
// NOTE: Image software-rendering functions (CPU)
RLAPI void ImageClearBackground(Image *dst, Color color);                                                // Clear image background with given color
RLAPI void ImageDrawPixel(Image *dst, int posX, int posY, Color color);                                  // Draw pixel within an image
RLAPI void ImageDrawPixelV(Image *dst, Vector2 position, Color color);                                   // Draw pixel within an image (Vector version)
RLAPI void ImageDrawLine(Image *dst, int startPosX, int startPosY, int endPosX, int endPosY, Color color); // Draw line within an image
RLAPI void ImageDrawLineV(Image *dst, Vector2 start, Vector2 end, Color color);                          // Draw line within an image (Vector version)
RLAPI void ImageDrawCircle(Image *dst, int centerX, int centerY, int radius, Color color);               // Draw a filled circle within an image
RLAPI void ImageDrawCircleV(Image *dst, Vector2 center, int radius, Color color);                        // Draw a filled circle within an image (Vector version)
RLAPI void ImageDrawCircleLines(Image *dst, int centerX, int centerY, int radius, Color color);          // Draw circle outline within an image
RLAPI void ImageDrawCircleLinesV(Image *dst, Vector2 center, int radius, Color color);                   // Draw circle outline within an image (Vector version)
RLAPI void ImageDrawRectangle(Image *dst, int posX, int posY, int width, int height, Color color);       // Draw rectangle within an image
RLAPI void ImageDrawRectangleV(Image *dst, Vector2 position, Vector2 size, Color color);                 // Draw rectangle within an image (Vector version)
RLAPI void ImageDrawRectangleRec(Image *dst, Rectangle rec, Color color);                                // Draw rectangle within an image
RLAPI void ImageDrawRectangleLines(Image *dst, Rectangle rec, int thick, Color color);                   // Draw rectangle lines within an image
RLAPI void ImageDraw(Image *dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint);             // Draw a source image within a destination image (tint applied to source)
RLAPI void ImageDrawText(Image *dst, Font font, const char *text, int posX, int posY, int fontSize, Color color);   // Draw text (using default font) within an image (destination)
RLAPI void ImageDrawTextEx(Image *dst, Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); // Draw text (custom sprite font) within an image (destination)

/*
// Texture loading functions
// NOTE: These functions require GPU access
RLAPI Texture2D LoadTexture(const char *fileName);                                                       // Load texture from file into GPU memory (VRAM)
RLAPI Texture2D LoadTextureFromImage(Image image);                                                       // Load texture from image data
RLAPI TextureCubemap LoadTextureCubemap(Image image, int layout);                                        // Load cubemap from image, multiple image cubemap layouts supported
RLAPI RenderTexture2D LoadRenderTexture(int width, int height);                                          // Load texture for rendering (framebuffer)
RLAPI void UnloadTexture(Texture2D texture);                                                             // Unload texture from GPU memory (VRAM)
RLAPI void UnloadRenderTexture(RenderTexture2D target);                                                  // Unload render texture from GPU memory (VRAM)
RLAPI void UpdateTexture(Texture2D texture, const void *pixels);                                         // Update GPU texture with new data
RLAPI void UpdateTextureRec(Texture2D texture, Rectangle rec, const void *pixels);                       // Update GPU texture rectangle with new data

// Texture configuration functions
RLAPI void GenTextureMipmaps(Texture2D *texture);                                                        // Generate GPU mipmaps for a texture
RLAPI void SetTextureFilter(Texture2D texture, int filter);                                              // Set texture scaling filter mode
RLAPI void SetTextureWrap(Texture2D texture, int wrap);                                                  // Set texture wrapping mode

// Texture drawing functions
RLAPI void DrawTexture(Texture2D texture, int posX, int posY, Color tint);                               // Draw a Texture2D
RLAPI void DrawTextureV(Texture2D texture, Vector2 position, Color tint);                                // Draw a Texture2D with position defined as Vector2
RLAPI void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);  // Draw a Texture2D with extended parameters
RLAPI void DrawTextureRec(Texture2D texture, Rectangle source, Vector2 position, Color tint);            // Draw a part of a texture defined by a rectangle
RLAPI void DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint); // Draw a part of a texture defined by a rectangle with 'pro' parameters
RLAPI void DrawTextureNPatch(Texture2D texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint); // Draws a texture (or part of it) that stretches or shrinks nicely
*/

// Color/pixel related functions
RLAPI Color Fade(Color color, float alpha);                                 // Get color with alpha applied, alpha goes from 0.0f to 1.0f
RLAPI int ColorToInt(Color color);                                          // Get hexadecimal value for a Color
RLAPI Vector4 ColorNormalize(Color color);                                  // Get Color normalized as float [0..1]
RLAPI Color ColorFromNormalized(Vector4 normalized);                        // Get Color from normalized values [0..1]
RLAPI Vector3 ColorToHSV(Color color);                                      // Get HSV values for a Color, hue [0..360], saturation/value [0..1]
RLAPI Color ColorFromHSV(float hue, float saturation, float value);         // Get a Color from HSV values, hue [0..360], saturation/value [0..1]
RLAPI Color ColorTint(Color color, Color tint);                             // Get color multiplied with another color
RLAPI Color ColorBrightness(Color color, float factor);                     // Get color with brightness correction, brightness factor goes from -1.0f to 1.0f
RLAPI Color ColorContrast(Color color, float contrast);                     // Get color with contrast correction, contrast values between -1.0f and 1.0f
RLAPI Color ColorAlpha(Color color, float alpha);                           // Get color with alpha applied, alpha goes from 0.0f to 1.0f
RLAPI Color ColorAlphaBlend(Color dst, Color src, Color tint);              // Get src alpha-blended into dst color with tint
RLAPI Color GetColor(unsigned int hexValue);                                // Get Color structure from hexadecimal value
RLAPI Color GetPixelColor(void *srcPtr, int format);                        // Get Color from a source pixel pointer of certain format
RLAPI void SetPixelColor(void *dstPtr, Color color, int format);            // Set color formatted into destination pixel pointer
RLAPI int GetPixelDataSize(int width, int height, int format);              // Get pixel data size in bytes for certain format

//------------------------------------------------------------------------------------
// Font Loading and Text Drawing Functions (Module: text)
//------------------------------------------------------------------------------------

// Font loading/unloading functions
RLAPI Font GetFontDefault(void);                                                            // Get the default Font
RLAPI Font LoadFont(const char *fileName);                                                  // Load font from file into GPU memory (VRAM)
RLAPI Font LoadFontEx(const char *fileName, int fontSize, int *fontChars, int glyphCount);  // Load font from file with extended parameters, use NULL for fontChars and 0 for glyphCount to load the default character set
RLAPI Font LoadFontFromImage(Image image, Color key, int firstChar);                        // Load font from Image (XNA style)
RLAPI Font LoadFontFromMemory(const char *fileType, const unsigned char *fileData, int dataSize, int fontSize, int *fontChars, int glyphCount); // Load font from memory buffer, fileType refers to extension: i.e. '.ttf'
RLAPI GlyphInfo *LoadFontData(const unsigned char *fileData, int dataSize, int fontSize, int *fontChars, int glyphCount, int type); // Load font data for further use
RLAPI Image GenImageFontAtlas(const GlyphInfo *chars, Rectangle **recs, int glyphCount, int fontSize, int padding, int packMethod); // Generate image font atlas using chars info
RLAPI void UnloadFontData(GlyphInfo *chars, int glyphCount);                                // Unload font chars info data (RAM)
RLAPI void UnloadFont(Font font);                                                           // Unload font from GPU memory (VRAM)
//RLAPI bool ExportFontAsCode(Font font, const char *fileName);                               // Export font as code file, returns true on success

/*
// Text drawing functions
RLAPI void DrawFPS(int posX, int posY);                                                     // Draw current FPS
RLAPI void DrawText(const char *text, int posX, int posY, int fontSize, Color color);       // Draw text (using default font)
RLAPI void DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); // Draw text using font and additional parameters
RLAPI void DrawTextPro(Font font, const char *text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint); // Draw text using Font and pro parameters (rotation)
RLAPI void DrawTextCodepoint(Font font, int codepoint, Vector2 position, float fontSize, Color tint); // Draw one character (codepoint)
RLAPI void DrawTextCodepoints(Font font, const int *codepoints, int count, Vector2 position, float fontSize, float spacing, Color tint); // Draw multiple character (codepoint)
*/

// Text font info functions
//RLAPI int MeasureText(const char *text, int fontSize);                                      // Measure string width for default font
RLAPI Vector2 MeasureTextEx(Font font, const char *text, float fontSize, float spacing);    // Measure string size for Font
RLAPI int GetGlyphIndex(Font font, int codepoint);                                          // Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found
RLAPI GlyphInfo GetGlyphInfo(Font font, int codepoint);                                     // Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found
RLAPI Rectangle GetGlyphAtlasRec(Font font, int codepoint);                                 // Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found

// Text codepoints management functions (unicode characters)
RLAPI char *LoadUTF8(const int *codepoints, int length);                // Load UTF-8 text encoded from codepoints array
RLAPI void UnloadUTF8(char *text);                                      // Unload UTF-8 text encoded from codepoints array
RLAPI int *LoadCodepoints(const char *text, int *count);                // Load all codepoints from a UTF-8 text string, codepoints count returned by parameter
RLAPI void UnloadCodepoints(int *codepoints);                           // Unload codepoints data from memory
RLAPI int GetCodepointCount(const char *text);                          // Get total number of codepoints in a UTF-8 encoded string
RLAPI int GetCodepoint(const char *text, int *codepointSize);           // Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
RLAPI int GetCodepointNext(const char *text, int *codepointSize);       // Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
RLAPI int GetCodepointPrevious(const char *text, int *codepointSize);   // Get previous codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
RLAPI const char *CodepointToUTF8(int codepoint, int *utf8Size);        // Encode one codepoint into UTF-8 byte array (array length returned as parameter)

// Text strings management functions (no UTF-8 strings, only byte chars)
// NOTE: Some strings allocate memory internally for returned strings, just be careful!
RLAPI int TextCopy(char *dst, const char *src);                                             // Copy one string to another, returns bytes copied
RLAPI bool TextIsEqual(const char *text1, const char *text2);                               // Check if two text string are equal
RLAPI unsigned int TextLength(const char *text);                                            // Get text length, checks for '\0' ending
RLAPI const char *TextFormat(const char *text, ...);                                        // Text formatting with variables (sprintf() style)
RLAPI const char *TextSubtext(const char *text, int position, int length);                  // Get a piece of a text string
RLAPI char *TextReplace(char *text, const char *replace, const char *by);                   // Replace text string (WARNING: memory must be freed!)
RLAPI char *TextInsert(const char *text, const char *insert, int position);                 // Insert text in a position (WARNING: memory must be freed!)
RLAPI const char *TextJoin(const char **textList, int count, const char *delimiter);        // Join text strings with delimiter
RLAPI const char **TextSplit(const char *text, char delimiter, int *count);                 // Split text into multiple strings
RLAPI void TextAppend(char *text, const char *append, int *position);                       // Append text at specific position and move cursor!
RLAPI int TextFindIndex(const char *text, const char *find);                                // Find first text occurrence within a string
RLAPI const char *TextToUpper(const char *text);                      // Get upper case version of provided string
RLAPI const char *TextToLower(const char *text);                      // Get lower case version of provided string
RLAPI const char *TextToPascal(const char *text);                     // Get Pascal case notation version of provided string
RLAPI int TextToInteger(const char *text);                            // Get integer value from text (negative values not supported)

#ifdef __cplusplus
}
#endif

#endif  // RIMAGE_H_INCLUDED

#ifdef RIMAGE_IMPLEMENTATION
#ifndef RIMAGE_IMPLEMENTATION_ONCE
#define RIMAGE_IMPLEMENTATION_ONCE

#define SUPPORT_MODULE_RTEXTURES
#define SUPPORT_MODULE_RTEXT
#define SUPPORT_IMAGE_MANIPULATION
//#define SUPPORT_IMAGE_GENERATION
#define SUPPORT_IMAGE_EXPORT

#ifdef __cplusplus
extern "C" {
#endif

#define STBI_NO_LINEAR

#ifndef TRACELOG
#include <stdio.h>
#define TRACELOG(level, ...) printf(__VA_ARGS__)
#endif

#if defined(SUPPORT_TRACELOG_DEBUG)
#define TRACELOGD(...) TRACELOG(LOG_DEBUG, __VA_ARGS__)
#else
#define TRACELOGD(...) (void)0
#endif

#ifndef RIMAGE_MALLOC
#include <stdlib.h>
#define RIMAGE_MALLOC(sz) malloc(sz)
#endif
#ifndef RL_MALLOC
#define RL_MALLOC(sz) RIMAGE_MALLOC(sz)
#endif

#ifndef RIMAGE_FREE
#include <stdlib.h>
#define RIMAGE_FREE(ptr) free(ptr)
#endif
#ifndef RL_FREE
#define RL_FREE(ptr) RIMAGE_FREE(ptr)
#endif

#ifndef RIMAGE_CALLOC
#include <stdlib.h>
#define RIMAGE_CALLOC(n,sz) calloc(n,sz)
#endif
#ifndef RL_CALLOC
#define RL_CALLOC(n,sz) RIMAGE_CALLOC(n,sz)
#endif

#ifndef RIMAGE_REALLOC
#include <stdlib.h>
#define RIMAGE_REALLOC(ptr,sz) realloc(ptr,sz)
#endif
#ifndef RL_REALLOC
#define RL_REALLOC(ptr,sz) RIMAGE_REALLOC(ptr,sz)
#endif

#ifndef RIMAGE_STRLEN
#include <string.h>
#define RIMAGE_STRLEN strlen
#endif

#ifndef RIMAGE_STRCPY
#include <string.h>
#define RIMAGE_STRCPY strcpy
#endif

#ifndef RIMAGE_STRCMP
#include <string.h>
#define RIMAGE_STRCMP strcmp
#endif

#ifndef RIMAGE_SPRINTF
#include <stdio.h>
#define RIMAGE_SPRINTF sprintf
#endif

#ifndef RIMAGE_MEMCPY
#include <string.h>
#define RIMAGE_MEMCPY(dest, src, n) memcpy(dest, src, n)
#endif

// Text
//#define SUPPORT_DEFAULT_FONT 1
//#define SUPPORT_FILEFORMAT_FNT      1
#define SUPPORT_FILEFORMAT_TTF      1
#define SUPPORT_TEXT_MANIPULATION   1
#ifndef MAX_TEXT_BUFFER_LENGTH
#define MAX_TEXT_BUFFER_LENGTH      1024
#endif
#ifndef MAX_TEXTSPLIT_COUNT
#define MAX_TEXTSPLIT_COUNT          128
#endif

#ifndef RIMAGE_GETFILEEXTENSION
#define RIMAGE_GETFILEEXTENSION rimage_getfileextension
// Get pointer to extension for a filename string (includes the dot: .png)
const char *rimage_getfileextension(const char *fileName)
{
    const char *dot = strrchr(fileName, '.');

    if (!dot || dot == fileName) return NULL;

    return dot;
}
#endif

// Check file extension
// NOTE: Extensions checking is not case-sensitive
bool IsFileExtension(const char *fileName, const char *ext)
{
    #define MAX_FILE_EXTENSION_SIZE  16

    bool result = false;
    const char *fileExt = RIMAGE_GETFILEEXTENSION(fileName);

    if (fileExt != NULL)
    {
#if defined(SUPPORT_MODULE_RTEXT) && defined(SUPPORT_TEXT_MANIPULATION)
        int extCount = 0;
        const char **checkExts = TextSplit(ext, ';', &extCount);  // WARNING: Module required: rtext

        char fileExtLower[MAX_FILE_EXTENSION_SIZE + 1] = { 0 };
        strncpy(fileExtLower, TextToLower(fileExt),MAX_FILE_EXTENSION_SIZE);  // WARNING: Module required: rtext

        for (int i = 0; i < extCount; i++)
        {
            if (RIMAGE_STRCMP(fileExtLower, TextToLower(checkExts[i])) == 0)
            {
                result = true;
                break;
            }
        }
#else
        if (RIMAGE_STRCMP(fileExt, ext) == 0) result = true;
#endif
    }

    return result;
}

#ifndef RIMAGE_LOADFILEDATA
#define SUPPORT_STANDARD_FILEIO
#define RIMAGE_LOADFILEDATA rimage_loadfiledata
unsigned char *rimage_loadfiledata(const char *fileName, unsigned int *bytesRead)
{
    unsigned char *data = NULL;
    *bytesRead = 0;

    if (fileName != NULL)
    {
#if defined(SUPPORT_STANDARD_FILEIO)
        FILE *file = fopen(fileName, "rb");

        if (file != NULL)
        {
            // WARNING: On binary streams SEEK_END could not be found,
            // using fseek() and ftell() could not work in some (rare) cases
            fseek(file, 0, SEEK_END);
            int size = ftell(file);
            fseek(file, 0, SEEK_SET);

            if (size > 0)
            {
                data = (unsigned char *)RL_MALLOC(size*sizeof(unsigned char));

                // NOTE: fread() returns number of read elements instead of bytes, so we read [1 byte, size elements]
                unsigned int count = (unsigned int)fread(data, sizeof(unsigned char), size, file);
                *bytesRead = count;

                if (count != size) TRACELOG(LOG_WARNING, "FILEIO: [%s] File partially loaded", fileName);
                else TRACELOG(LOG_INFO, "FILEIO: [%s] File loaded successfully", fileName);
            }
            else TRACELOG(LOG_WARNING, "FILEIO: [%s] Failed to read file", fileName);

            fclose(file);
        }
        else TRACELOG(LOG_WARNING, "FILEIO: [%s] Failed to open file", fileName);
#else
    TRACELOG(LOG_WARNING, "FILEIO: Standard file io not supported, use custom file callback");
#endif
    }
    else TRACELOG(LOG_WARNING, "FILEIO: File name provided is not valid");

    return data;
}
#endif

#ifndef RIMAGE_SAVEFILEDATA
#define RIMAGE_SAVEFILEDATA rimage_savefiledata
// Save data to file from buffer
bool rimage_savefiledata(const char *fileName, void *data, unsigned int bytesToWrite)
{
    bool success = false;

    if (fileName != NULL)
    {
        /*
        if (saveFileData)
        {
            return saveFileData(fileName, data, bytesToWrite);
        }*/
#if defined(SUPPORT_STANDARD_FILEIO)
        FILE *file = fopen(fileName, "wb");

        if (file != NULL)
        {
            unsigned int count = (unsigned int)fwrite(data, sizeof(unsigned char), bytesToWrite, file);

            if (count == 0) TRACELOG(LOG_WARNING, "FILEIO: [%s] Failed to write file", fileName);
            else if (count != bytesToWrite) TRACELOG(LOG_WARNING, "FILEIO: [%s] File partially written", fileName);
            else TRACELOG(LOG_INFO, "FILEIO: [%s] File saved successfully", fileName);

            int result = fclose(file);
            if (result == 0) success = true;
        }
        else TRACELOG(LOG_WARNING, "FILEIO: [%s] Failed to open file", fileName);
#else
    TRACELOG(LOG_WARNING, "FILEIO: Standard file io not supported, use custom file callback");
#endif
    }
    else TRACELOG(LOG_WARNING, "FILEIO: File name provided is not valid");

    return success;
}
#endif

// Include the modified raylib code.
#include "src/rtextures.c"
#include "src/rtext.c"

#ifdef __cplusplus
}
#endif

#endif  // RIMAGE_IMPLEMENTATION_ONCE
#endif  // RIMAGE_IMPLEMENTATION
