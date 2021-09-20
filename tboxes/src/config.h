#ifndef TBOXES_SRC_CONFIG_H_
#define TBOXES_SRC_CONFIG_H_
#ifndef VERSION_NAME
#define VERSION_NAME "v0.0.0"
#endif
#include <iostream>

namespace config {
std::string get_version_name();
}
#endif  // TBOXES_SRC_CONFIG_H_
