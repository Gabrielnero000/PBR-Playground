#include "primitive.h"

Primitive::Primitive(MaterialUniquePtr material) : material_{std::move(material)} {}
Primitive::~Primitive() {}