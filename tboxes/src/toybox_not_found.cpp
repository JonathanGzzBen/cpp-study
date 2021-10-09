#include "src/toybox_not_found.h"

const char* ToyBoxNotFound::what() const noexcept { return message.c_str(); }
