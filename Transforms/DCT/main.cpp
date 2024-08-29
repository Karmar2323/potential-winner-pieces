#include <iostream>
#include <cmath>
#include <iomanip>

/* Discrete cosine transform of an 8 bit 8x8 subimage.
  Written to C++ from JPEG codec example 
  (Wikipedia <https://en.wikipedia.org/wiki/JPEG>).
  The console app prints the hard-coded subimage array 
  taken from the wikipedia article (29.8.2024). It then prints 
  the shifted-value array, performs DCT on this and 
  prints the result.
*/

int main(){
    const int BLOCKSIZE{8};
    const int MIDPOINT{128};
    float inv_sqrt2 {1 / sqrtf(2)};
    const float PI {3.14159};
    const int CWIDTH{8};

    int subimage [][BLOCKSIZE] {
        {52,55,61,66,70,61,64,73},
        {63,59,55,90,109,85,69,72},
        {62,59,68,113,144,104,66,73},
        {63,58,71,122,154,106,70,69},
        {67,61,68,104,126,88,68,70},
        {79,65,60,70,77,68,58,75},
        {85,71,64,59,55,61,65,83},
        {87,79,69,68,65,76,78,94}
    };

    int temp_image [BLOCKSIZE][BLOCKSIZE];
    float dct_matrix [BLOCKSIZE][BLOCKSIZE];
    /* https://en.wikipedia.org/wiki/JPEG
     Discrete cosine transform
     1. shift from positive range to zero-centered: for 8-bit image subract 128.
     2. compute 2-D DCT
      G_uv = 1/4 * alpha(u)alpha(v) 
        *sum(x_0->7){ sum(y_0->7)[ g_xy * cos([(2x + 1)u*pi]/16)]) *cos([(2y + 1)v*pi]/16)]) ] }
      where G_uv = DCT coefficient at coordinates (u,v),
      u = horizontal spatial frequency for integers 0 <= u < 8
      v = vertical spatial frequency for integers 0 <= v < 8
      alpha(u) = 1/sqrt(2), if u = 0,
                1, otherwise
                is normalizing scale factor to make transformation orthonormal
      g_xy = pixel value at (x,y) coordinates
     */

    // print original subimage
    std::cout << "The subimage with value range [0, 255]: " << std::endl;
    for (size_t i {}; i < BLOCKSIZE; i++) {
        for (size_t j {}; j < BLOCKSIZE; j++) {
            std::cout << std::setw(CWIDTH*0.5) << subimage[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // 1. shifting
    std::cout << "Subimage shifted to range [-128, 127]: " << std::endl;
    for (size_t i {}; i < BLOCKSIZE; i++) {
        for (size_t j {}; j < BLOCKSIZE; j++) {
            temp_image[i][j] = subimage[i][j] - MIDPOINT;
            // print the result
            std::cout << std::setw(CWIDTH*0.5) << temp_image[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // 2. DCT
    std::cout << "DCT coefficients: " << std::endl;
    // u: horizontal coordinate for result
    for (size_t u {}; u < BLOCKSIZE; u++) {
        // v: vertical coordinate for result
        for (size_t v {}; v < BLOCKSIZE; v++) {
            // alpha: normalizing factor for u,v
            float alphau {u == 0 ? inv_sqrt2 : 1};
            float alphav {v == 0 ? inv_sqrt2 : 1};            

            float sumxy{0};
            for (size_t x{}; x < BLOCKSIZE; x++) {
                // the sum over vertical coordinates
                float sumy{0};
                for (size_t y{}; y < BLOCKSIZE; y++) {
                    // 1st cosine depending on horizontal coordinates x and u
                    float cosu = cosf(((2*x + 1)*u*PI) / 16);
                    // 2nd cosine
                    float cosv = cosf(((2*y + 1)*v*PI) / 16);
                    // inner sum over y
                    sumy += temp_image[x][y] * cosu * cosv;
                }
                //outer sum
                sumxy += sumy;
            }
            // final DCT coefficient
            dct_matrix[u][v] = 0.25 * alphau * alphav * sumxy;
            // print it
            std::cout << std::setw(CWIDTH) << std::showpoint << std::fixed
                << std::setprecision(2) << dct_matrix[u][v];
        }
        std::cout << std::endl;

    }
    return 0;
}
