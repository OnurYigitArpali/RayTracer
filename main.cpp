
#include "parser.h"
#include "integrator.h"
#include "timer.h"

#include <iostream>
#include <iomanip>

int main(int argc, char *argv[])
{
    fst::Timer timer;
    fst::Timer total_timer;

    total_timer.start();
    timer.start();
    parser::Scene scene;
    scene.loadFromXml(argv[1]);
    std::cout << std::fixed << std::showpoint << std::setprecision(5);
    std::cout << "loadFromXml    : " << timer.getTime() << " seconds" << std::endl;

    timer.start();
    fst::Integrator integrator(scene);
    std::cout << "loadFromParser : " << timer.getTime() << " seconds" << std::endl;

    timer.start();
    integrator.integrate();
    std::cout << "Traversal      : " << timer.getTime() << " seconds" << std::endl;
    std::cout << std::endl << "Total          : " << total_timer.getTime() << " seconds" << std::endl;

    return 0;
}

/*
#include <iostream>
#include <iomanip>
#include "parser.h"
#include "ppm.h"
#include "jpeg.h"
#include "matrixInverse.h"
#include "parser.h"
#include "integrator.h"
#include "timer.h"

typedef unsigned char RGB[3];

/*
 * argv[1]: Output JPEG file name
 * argv[2]: Output PPM file name
 */
/*
int main(int argc, char* argv[])
{
    // The code below creates a test pattern and writes
    // it to a PPM file to demonstrate the usage of the
    // ppm_write function.

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

    // Read it back to a different array
    int w, h;
    read_jpeg_header(argv[1], w, h);

    unsigned char* jpegImage = new unsigned char [w * h * 3];
    read_jpeg(argv[1], jpegImage, w, h);

    // Now save as PPM
    write_ppm(argv[2], jpegImage, w, h);

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
}
*/