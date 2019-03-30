#include "mesh.h"

Mesh::Mesh(MaterialUniquePtr material,
           const std::string filename) : Primitive::Primitive(std::move(material))
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
            {
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
            }
            break;

            case 'f':
            {
                for (size_t i = 0, j = 0; i < line.size(); i++)
                {
                    if (line[i] == ' ')
                    {
                        index[j] = i;
                        j++;
                    }
                }

                glm::vec3 v_1 = vertex_temp[std::stoi(line.substr(index[0] + 1, index[1] - index[0])) - 1];
                glm::vec3 v_2 = vertex_temp[std::stoi(line.substr(index[1] + 1, index[2] - index[1])) - 1];
                glm::vec3 v_3 = vertex_temp[std::stoi(line.substr(index[2] + 1, (line.size() - 1) - index[2])) - 1];

                triangles_.push_back(TriangleUniquePtr(new Triangle{NULL, v_1, v_2, v_3}));
            }
            break;

            default:
                break;
            }
        }
    }
}

Mesh::~Mesh() {}

bool Mesh::intersect(const Ray &ray,
                     float t_min,
                     float t_max,
                     Record &record) const
{
    bool intersect = false;
    Record tmp_record;
    float closest_so_far = t_max;

    for (size_t i = 0; i < triangles_.size(); i++)
    {
        if (triangles_[i]->intersect(ray, t_min, closest_so_far, tmp_record))
        {
            record = tmp_record;
            closest_so_far = tmp_record.t_;
            record.index_ = i;
            intersect = true;
        }
    }

    return intersect;
}