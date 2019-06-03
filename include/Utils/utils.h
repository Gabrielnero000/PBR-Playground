#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <fstream>
#include <vector>
#include "vec.h"
#include "OBJ_Loader.h"
#include "stb_image.h"
#include "Primitives/triangle.h"

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

void read(const std::string &filename, std::vector<Primitive::PrimitivePtr> &triangles, Material *material)
{
    objl::Loader loader;
    bool loadout = loader.LoadFile(filename);

    if (loadout)
    {
        for (int i = 0; i < loader.LoadedMeshes.size(); i++)
        {
            objl::Mesh curMesh = loader.LoadedMeshes[i];
            for (int j = 0; j < curMesh.Vertices.size(); j += 3)
            {
                Vec3f v_1(curMesh.Vertices[j].Position.X,
                          curMesh.Vertices[j].Position.Y,
                          curMesh.Vertices[j].Position.Z);

                Vec3f v_2(curMesh.Vertices[j + 1].Position.X,
                          curMesh.Vertices[j + 1].Position.Y,
                          curMesh.Vertices[j + 1].Position.Z);

                Vec3f v_3(curMesh.Vertices[j + 2].Position.X,
                          curMesh.Vertices[j + 2].Position.Y,
                          curMesh.Vertices[j + 2].Position.Z);

                Vec3f n_1(curMesh.Vertices[j].Normal.X,
                          curMesh.Vertices[j].Normal.Y,
                          curMesh.Vertices[j].Normal.Z);

                Vec3f n_2(curMesh.Vertices[j + 1].Normal.X,
                          curMesh.Vertices[j + 1].Normal.Y,
                          curMesh.Vertices[j + 1].Normal.Z);

                Vec3f n_3(curMesh.Vertices[j + 2].Normal.X,
                          curMesh.Vertices[j + 2].Normal.Y,
                          curMesh.Vertices[j + 2].Normal.Z);

                float tx_1 = curMesh.Vertices[j].TextureCoordinate.X;
                float ty_1 = curMesh.Vertices[j].TextureCoordinate.Y;

                float tx_2 = curMesh.Vertices[j + 1].TextureCoordinate.X;
                float ty_2 = curMesh.Vertices[j + 1].TextureCoordinate.Y;

                float tx_3 = curMesh.Vertices[j + 2].TextureCoordinate.X;
                float ty_3 = curMesh.Vertices[j + 2].TextureCoordinate.Y;

                triangles.push_back(Primitive::PrimitivePtr(new Triangle(
                    Material::MaterialPtr(material->duplicate()),
                    "mesh_triangle",
                    v_1, v_2, v_3,
                    n_1, n_2, n_3,
                    tx_1, ty_1,
                    tx_2, ty_2,
                    tx_3, ty_3,
                    true)));
            }
        }
    }
}