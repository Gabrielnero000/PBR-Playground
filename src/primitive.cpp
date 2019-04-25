#include "primitive.h"

Primitive::Primitive() {}
Primitive::Primitive(Material* material) : material_{std::move(material)} {}
Primitive::~Primitive() {}