#include "output.h"

Output::Output(const glm::vec2 resolution) : resolution_{resolution}
{
    // Buffer needs to be alocated and initialized as 0
    buffer_.resize(resolution_.x, std::vector<glm::vec3>(resolution_.y));
    for (int j = resolution_.y - 1; j >= 0; j--)
        for (int i = 0; i < resolution_.x; i++)
            buffer_[i][j] = glm::vec3{0.0f, 0.0f, 0.0f};
}

Output::~Output() {}

void Output::save(const std::string filename)
{
    // PPM's pattern
    std::ofstream image;
    image.open(filename + ".ppm");
    image << "P3\n"
          << resolution_.x << " "
          << resolution_.y << "\n255\n";
    for (int j = resolution_.y - 1; j >= 0; j--)
        for (int i = 0; i < resolution_.x; i++)
        {
            buffer_[i][j][0] = powf(buffer_[i][j][0], 1.0f / 2.2f);
            buffer_[i][j][1] = powf(buffer_[i][j][1], 1.0f / 2.2f);
            buffer_[i][j][2] = powf(buffer_[i][j][2], 1.0f / 2.2f);

            if (buffer_[i][j][0] < 0.0f)
                buffer_[i][j][0] = 0.0f;
            if (buffer_[i][j][0] > 1.0f)
                buffer_[i][j][0] = 1.0f;

            if (buffer_[i][j][1] < 0.0f)
                buffer_[i][j][1] = 0.0f;
            if (buffer_[i][j][1] > 1.0f)
                buffer_[i][j][1] = 1.0f;

            if (buffer_[i][j][2] < 0.0f)
                buffer_[i][j][2] = 0.0f;
            if (buffer_[i][j][2] > 1.0f)
                buffer_[i][j][2] = 1.0f;

            // Bring colors from [0, 1] to [0, 255]
            // Watch out for rounding errors
            image << int(buffer_[i][j][0] * 255.99f) << " "
                  << int(buffer_[i][j][1] * 255.99f) << " "
                  << int(buffer_[i][j][2] * 255.99f) << "\n";
        }

    image.close();
}