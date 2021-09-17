#include <iostream>
#include <ostream>

#include "../libs/cxxopts/include/cxxopts.hpp"
#include "config.h"

int main(int argc, char** argv) {
  cxxopts::Options options("tboxes", config::get_version_name());

  options.add_options()("c,create-box", "Create toy box", cxxopts::value<std::string>())(
      "d,debug", "Enable debugging",
      cxxopts::value<bool>()->default_value("false"))(
      "f,foo", "Param foo", cxxopts::value<int>()->default_value("10"))(
      "h,help", "Print usage");

  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }
  bool debug = result["debug"].as<bool>();
  if (debug) {
    std::cout << "running in debug" << std::endl;
  }
  std::string bar;
  if (result.count("bar")) {
    bar = result["bar"].as<std::string>();
    std::cout << "bar: " << bar << std::endl;
  }
  int foo = result["foo"].as<int>();
  if (foo > 0) {
    for (int i{0}; i < foo; i++) {
      std::cout << i << std::endl;
    }
  }

  return 0;
}
