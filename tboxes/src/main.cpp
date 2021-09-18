#include <iostream>
#include <vector>

#include "../libs/cxxopts/include/cxxopts.hpp"
#include "config.h"

int main(int argc, char** argv) {
  cxxopts::Options options("tboxes", config::get_version_name());

  options.add_options()("c,create-box", "Create toy box",
                        cxxopts::value<std::string>())(
      "l,list-boxes", "List boxes")("d,display-box", "Display box contents",
                                    cxxopts::value<std::string>())(
      "a,add-to-box", "Box to which to add figure",
      cxxopts::value<std::string>())(
      "t,triangle", "Add triangle with specified base and height",
      cxxopts::value<std::vector<int>>()->implicit_value("1,1"))("h,help",
                                                                 "Print usage");

  auto result = options.parse(argc, argv);

  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }
  if (result.count("list-boxes")) {
    std::cout << "Boxes:" << std::endl;
    return 0;
  }
  if (result.count("display-box")) {
    std::string box_name{result["display-box"].as<std::string>()};
    std::cout << "Displaying contents of box " << box_name << std::endl;
    return 0;
  }
  if (result.count("create-box")) {
    std::string bar;
    bar = result["create-box"].as<std::string>();
    std::cout << "name of box to create: " << bar << std::endl;
  }
  if (result.count("add-to-box")) {
    std::string target_box{result["add-to-box"].as<std::string>()};
    std::cout << "Adding figures to: " << target_box << std::endl;
    if (result.count("triangle")) {
      std::vector<int> triangle_measures{
          result["triangle"].as<std::vector<int>>()};
      std::cout << "Triangle base:" << triangle_measures.at(0) << std::endl;
      std::cout << "Triangle height:" << triangle_measures.at(1) << std::endl;
    }
    return 0;
  }
  return 0;
}
