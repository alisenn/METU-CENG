#include <iostream>
#include <iomanip>
#include "parser.h"
#include "ppm.h"
#include "jpeg.h"
#include "matrixInverse.h"

typedef unsigned char RGB[3];

/*
 * argv[1]: Output JPEG file name
 */
int main(int argc, char* argv[])
{
    // The code below creates a test pattern and writes
    // it to a JPEG file.

    const RGB BAR_COLOR[8] =
    {
        { 255, 255, 255 },  // 100% White
        { 255, 255,   0 },  // Yellow
        {   0, 255, 255 },  // Cyan
        {   0, 255,   0 },  // Green
        { 255,   0, 255 },  // Magenta
        { 255,   0,   0 },  // Red
        {   0,   0, 255 },  // Blue
        {   0,   0,   0 },  // Black
    };

    int width = 640, height = 480;
    int columnWidth = width / 8;

    unsigned char* image = new unsigned char [width * height * 3];

    int i = 0;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int colIdx = x / columnWidth;
            image[i++] = BAR_COLOR[colIdx][0];
            image[i++] = BAR_COLOR[colIdx][1];
            image[i++] = BAR_COLOR[colIdx][2];
        }
    }

    // Save this image as JPEG
    write_jpeg(argv[1], image, width, height);

    return 0;
}
