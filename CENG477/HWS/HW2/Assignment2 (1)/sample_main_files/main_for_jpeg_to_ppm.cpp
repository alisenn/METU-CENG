#include <iostream>
#include <iomanip>
#include "parser.h"
#include "ppm.h"
#include "jpeg.h"
#include "matrixInverse.h"


/*
 * argv[1]: Input JPEG file name
 * argv[2]: Output PPM file name
 */
int main(int argc, char* argv[])
{
    // Read JPEG file
    int w, h;
    read_jpeg_header(argv[1], w, h);

    unsigned char* jpegImage = new unsigned char [w * h * 3];
    read_jpeg(argv[1], jpegImage, w, h);

    // Now save as PPM
    write_ppm(argv[2], jpegImage, w, h);

    return 0;
}
