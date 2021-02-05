#include <iostream>
#include <iomanip>
#include "parser.h"
#include "ppm.h"
#include "jpeg.h"
#include "matrixInverse.h"


int main(int argc, char* argv[])
{
    //
    // Demonstrate matrix inversion
    //
    double m[16] = {
        2, 0, 0, 0,
        0, 3, 0, 0,
        0, 0, 4, 0,
        0, 0, 0, 1
    };

    double inv[16];

    invert(m, inv);

    std::cout << "Original matrix:" << std::endl;
    for (int y = 0, i = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x, ++i)
        {
            std::cout << m[i] << "\t"; 
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Inverted matrix:" << std::endl;
    for (int y = 0, i = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x, ++i)
        {
            std::cout << std::setprecision(3) << inv[i] << "\t"; 
        }
        std::cout << std::endl;
    }

    return 0;
}
