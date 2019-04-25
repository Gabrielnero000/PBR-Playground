#include "primitive.h"

Primitive::Primitive() {}
Primitive::Primitive(Material *material) : material_{material} {}
Primitive::~Primitive() {}