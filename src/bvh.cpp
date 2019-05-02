#include "bvh.h"

BVH::BVH(std::vector<Primitive::PrimitivePtr> &primitives) : Accelerator::Accelerator(primitives)
{
    for (std::size_t i = 0; i < primitives_.size(); i++)
        primitive_indexes_.push_back(i);
}

BVH::~BVH() {}

void BVH::build()
{
    int axis = 0;
    bool ordered = false;
    AABB box, box_left, box_right;

    while (!ordered)
    {
        ordered = true;
        for (std::size_t i = 0; i < primitives_.size() - 1; i++)
        {
            primitives_[primitive_indexes_[i]]->boundingBox(box_left);
            primitives_[primitive_indexes_[i + 1]]->boundingBox(box_right);

            if (box_left.centroid_[axis] > box_right.centroid_[axis])
            {
                int aux = primitive_indexes_[i];
                primitive_indexes_[i] = primitive_indexes_[i + 1];
                primitive_indexes_[i + 1] = aux;
                ordered = false;
            }
        }
    }

    root_ = buildRecursive(primitive_indexes_);
}

BVH::BVHNode *BVH::buildRecursive(const std::vector<int> primitive_indexes)
{
    BVHNode *node;
    AABB box, box_left, box_right;

    if (primitive_indexes.size() < 2) // Only one primitive
    {
        primitives_[primitive_indexes[0]]->boundingBox(box);
        node = new BVHNode(primitive_indexes, box);
        node->left_ = nullptr;
        node->right_ = nullptr;

        return node;
    }

    primitives_[primitive_indexes[0]]->boundingBox(box_left);
    primitives_[primitive_indexes[primitive_indexes.size() - 1]]->boundingBox(box_right);
    box = AABB::surroundingBox(box_left, box_right);

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
    float t_temp = t_max;
    return traceRecursive(ray, t_min, &t_temp, record, root_);
}

bool BVH::traceRecursive(const Ray &ray,
                         float t_min,
                         float *t_max,
                         Record &record,
                         BVHNode *node) const
{
    bool intersected = false;
    float *closest_so_far = t_max;
    if (node != nullptr && node->box_.intersect(ray, t_min, *t_max))
    {
        Record tmp_record;

        if (node->left_ == nullptr && node->right_ == nullptr) // Is a leaf
        {
            for (std::size_t i = 0; i < node->primitive_indexes_.size(); i++)
            {
                if (primitives_[node->primitive_indexes_[i]]->intersect(ray, t_min, *t_max, tmp_record))
                {
                    intersected = true;                          // has intersection
                    record = tmp_record;                         // update intersection's record
                    *closest_so_far = tmp_record.t_;             // update t_max
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