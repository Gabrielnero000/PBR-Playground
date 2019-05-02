#include "primitive.h"

Primitive::Primitive(Material::MaterialPtr material) : material_{std::move(material)} {}
Primitive::~Primitive() {}