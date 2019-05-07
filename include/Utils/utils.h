#include <iostream>
#include <fstream>
#include <vector>
#include "vec.h"
#include "OBJ_Loader.h"

void saveToFile(const std::string &filename, std::vector<std::vector<Vec3f>> &buffer)
{
    // PPM's pattern
    std::ofstream image;
    image.open(filename + ".ppm");
    image << "P3\n"
          << buffer.size() << " "
          << buffer[0].size() << "\n255\n";
    for (int j = buffer[0].size() - 1; j >= 0; j--)
    {
        for (int i = 0; i < buffer.size(); i++)
        {

            if (buffer[i][j][0] < 0.0f)
                buffer[i][j][0] = 0.0f;
            if (buffer[i][j][0] > 1.0f)
                buffer[i][j][0] = 1.0f;

            if (buffer[i][j][1] < 0.0f)
                buffer[i][j][1] = 0.0f;
            if (buffer[i][j][1] > 1.0f)
                buffer[i][j][1] = 1.0f;

            if (buffer[i][j][2] < 0.0f)
                buffer[i][j][2] = 0.0f;
            if (buffer[i][j][2] > 1.0f)
                buffer[i][j][2] = 1.0f;

            // buffer[i][j][0] = powf(buffer[i][j][0], 1.0f / 2.2f);
            // buffer[i][j][1] = powf(buffer[i][j][1], 1.0f / 2.2f);
            // buffer[i][j][2] = powf(buffer[i][j][2], 1.0f / 2.2f);

            // Bring colors from [0, 1] to [0, 255]
            // Watch out for rounding errors
            image << int(buffer[i][j][0] * 255.99f) << " "
                  << int(buffer[i][j][1] * 255.99f) << " "
                  << int(buffer[i][j][2] * 255.99f) << "\n";
        }
    }

    image.close();
}