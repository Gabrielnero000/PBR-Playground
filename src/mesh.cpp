#include "mesh.h"

Mesh::Mesh(const std::string filename)
{

    std::vector<glm::vec3> vertex_temp;
    std::string line;
    std::ifstream mesh;
    mesh.open(filename);

    int index[3];

    if (mesh.is_open())
    {
        while (getline(mesh, line))
        {
            switch (line[0])
            {
            case 'v':
                for (size_t i = 0, j = 0; i < line.size(); i++)
                {
                    if (line[i] == ' ')
                    {
                        index[j] = i;
                        j++;
                    }
                }

                vertex_temp.push_back(glm::vec3{
                    std::stof(line.substr(index[0] + 1, index[1] - index[0])),
                    std::stof(line.substr(index[1] + 1, index[2] - index[1])),
                    std::stof(line.substr(index[2] + 1, (line.size() - 1) - index[2]))});

                break;

            case 'f':

                for (size_t i = 0, j = 0; i < line.size(); i++)
                {
                    if (line[i] == ' ')
                    {
                        index[j] = i;
                        j++;
                    }
                }

                triangles_.push_back(new Triangle{
                    vertex_temp[std::stoi(line.substr(index[0] + 1, index[1] - index[0])) - 1],
                    vertex_temp[std::stoi(line.substr(index[1] + 1, index[2] - index[1])) - 1],
                    vertex_temp[std::stoi(line.substr(index[2] + 1, (line.size() - 1) - index[2])) - 1]});

                /*std::cout << std::stod(line.substr(index[0] + 1, index[1] - index[0]))
                          << ", " << std::stod(line.substr(index[1] + 1, index[2] - index[1]))
                          << ", " << std::stof(line.substr(index[2] + 1, (line.size() - 1) - index[2])) << std::endl;*/

                break;

            default:
                break;
            }
        }
    }
}

Mesh::~Mesh()
{
}

bool Mesh::intersect(const Ray &ray,
                     float t_min,
                     float t_max,
                     Record &record) const
{
    bool intersect = false;

    //std::cout << "v1: " << triangles_[0]->v1_[0] << ", " << triangles_[0]->v1_[1] << ", " << triangles_[0]->v1_[2] << std::endl;
    //std::cout << "v2: " << triangles_[0]->v2_[0] << ", " << triangles_[0]->v2_[1] << ", " << triangles_[0]->v2_[2] << std::endl;
    //std::cout << "v3: " << triangles_[0]->v3_[0] << ", " << triangles_[0]->v3_[1] << ", " << triangles_[0]->v3_[2] << std::endl;

    for (size_t i = 0; i < triangles_.size(); i++)
    {
        if (triangles_[i]->intersect(ray, t_min, t_max, record))
            intersect = true;
    }

    return intersect;
}