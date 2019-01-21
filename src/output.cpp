#include "output.h"

Output::Output(const glm::vec2 resolution) : resolution_{resolution}
{
    // Buffer needs to be alocated
    buffer_.resize(resolution_.x, std::vector<glm::vec3>(resolution_.y));
}

Output::~Output() {}

void Output::save()
{
    // PPM's pattern
    std::ofstream image;
    image.open("output.ppm");
    image << "P3\n"
          << resolution_.x << " "
          << resolution_.y << "\n255\n";
    for (int j = resolution_.y - 1; j >= 0; j--)
        for (int i = 0; i < resolution_.x; i++)
            // Bring colors from [0, 1] to [0, 255]
            // Watch out for rounding errors
            image << int(buffer_[i][j][0] * 255.99f) << " "
                  << int(buffer_[i][j][1] * 255.99f) << " "
                  << int(buffer_[i][j][2] * 255.99f) << "\n";
    image.close();
}