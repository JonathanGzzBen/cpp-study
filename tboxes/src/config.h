#ifndef _CONFIG_H_
#define _CONFIG_H_
#ifndef VERSION_NAME
#define VERSION_NAME "v0.0.0"
#endif
#include <iostream>

namespace config {
    std::string get_version_name();
}
#endif
