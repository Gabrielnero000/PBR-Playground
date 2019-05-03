#include "primitive.h"

Primitive::Primitive(Material::MaterialPtr material, const std::string &id) : material_{std::move(material)}, id_{id} {}
Primitive::~Primitive() {}