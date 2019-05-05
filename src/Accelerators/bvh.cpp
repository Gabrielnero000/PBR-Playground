#include "Accelerators/bvh.h"

BVH::BVH(std::vector<Primitive::PrimitivePtr> &primitives) : Accelerator::Accelerator(primitives)
{
    for (std::size_t i = 0; i < primitives_.size(); i++)
        primitive_indexes_.push_back(i);
}

BVH::~BVH() {}

void BVH::build()
{
    root_ = buildRecursive(primitive_indexes_);
}

BVH::BVHNode *BVH::buildRecursive(std::vector<int> primitive_indexes)
{
    // for (std::size_t i = 0; i < primitive_indexes.size(); i++)
    //     std::cout << primitives_[primitive_indexes[i]]->id_ << ", ";

    //std::cout << primitive_indexes.size() << std::endl;

    BVHNode *node;
    int axis = 0;
    bool ordered = false;
    AABB box, box_left, box_right;

    if (primitive_indexes.size() < 2) // Only one primitive
    {
        primitives_[primitive_indexes[0]]->boundingBox(box);
        node = new BVHNode(primitive_indexes, box);
        node->left_ = nullptr;
        node->right_ = nullptr;

        return node;
    }

    ordered = false;
    while (!ordered)
    {
        ordered = true;
        for (std::size_t i = 0; i < primitive_indexes.size() - 1; i++)
        {
            primitives_[primitive_indexes[i]]->boundingBox(box_left);
            primitives_[primitive_indexes[i + 1]]->boundingBox(box_right);

            if (box_left.min_[axis] > box_right.min_[axis])
            {
                int aux = primitive_indexes[i];
                primitive_indexes[i] = primitive_indexes[i + 1];
                primitive_indexes[i + 1] = aux;
                ordered = false;
            }
        }
    }

    primitives_[primitive_indexes[0]]->boundingBox(box);

    for (std::size_t i = 1; i < primitive_indexes.size(); i++)
    {
        primitives_[primitive_indexes[i]]->boundingBox(box_right);
        box = AABB::surroundingBox(box, box_right);
    }

    // std::cout << box.min_[0] << ", " << box.min_[1] << ", " << box.min_[2] << std::endl;
    // std::cout << box.max_[0] << ", " << box.max_[1] << ", " << box.max_[2] << "\n"
    //           << std::endl;

    const int half = primitive_indexes.size() / 2;

    const std::vector<int> left_split = std::vector<int>(primitive_indexes.begin(), primitive_indexes.begin() + half);
    const std::vector<int> right_split = std::vector<int>(primitive_indexes.begin() + half, primitive_indexes.end());

    node = new BVHNode(primitive_indexes, box);
    node->left_ = buildRecursive(left_split);
    node->right_ = buildRecursive(right_split);

    return node;
}

bool BVH::trace(const Ray &ray,
                float t_min,
                float t_max,
                Record &record) const
{
    return traceRecursive(ray, t_min, t_max, record, root_);
}

bool BVH::traceRecursive(const Ray &ray,
                         float t_min,
                         float &t_max,
                         Record &record,
                         BVHNode *node) const
{
    bool intersected = false;
    if (node != nullptr && node->box_.intersect(ray, t_min, t_max))
    {
        Record tmp_record;

        if (node->left_ == nullptr && node->right_ == nullptr) // Is a leaf
        {
            for (std::size_t i = 0; i < node->primitive_indexes_.size(); i++)
            {
                if (primitives_[node->primitive_indexes_[i]]->intersect(ray, t_min, t_max, tmp_record))
                {
                    intersected = true;                          // has intersection
                    record = tmp_record;                         // update intersection's record
                    t_max = tmp_record.t_;                       // update t_max
                    record.index_ = node->primitive_indexes_[i]; // the primitive index
                }
            }
        }
        else
        {
            if (traceRecursive(ray, t_min, t_max, record, node->left_))
                intersected = true;
            if (traceRecursive(ray, t_min, t_max, record, node->right_))
                intersected = true;
        }
    }

    return intersected;
}

BVH::BVHNode::BVHNode(const std::vector<int> primitive_indexes, const AABB box) : primitive_indexes_{primitive_indexes},
                                                                                  box_{box} {}

BVH::BVHNode::~BVHNode() {}