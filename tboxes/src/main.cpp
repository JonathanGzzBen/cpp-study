#include <iostream>
#include <vector>

#include "src/config.h"
#include "src/toybox.h"

std::vector<ToyBox*> toyboxes;
void print_menu();

int main(int argc, char** argv) {
  char input{'\0'};
  do {
    print_menu();
    std::cout << "Selection: ";
    std::cin >> input;
    switch (input) {
      case 'c':
      case 'C': {
        std::cout << "Enter box name: ";
        std::string box_name;
        std::cin >> box_name;
        ToyBox* new_box = new ToyBox{box_name};
        std::cout << "Created ToyBox " << new_box->get_name() << std::endl;
        toyboxes.push_back(new_box);
        break;
      }
      case 'l':
      case 'L': {
        std::cout << "Boxes:" << std::endl;
        break;
      }
      case 'd':
      case 'D': {
        std::cout << "Which box do you want to display?: ";
        std::string box_name;
        std::cin >> box_name;
        std::cout << "Displaying contents of box " << box_name << std::endl;
      }
      case 't':
      case 'T': {
        std::cout << "Enter measures of new triangle" << std::endl;
        std::cout << "Triangle base: ";
        int triangle_base{0};
        std::cin >> triangle_base;
        std::cout << "Triangle height: ";
        int triangle_height{0};
        std::cin >> triangle_height;
        auto* triangle = new Triangle{triangle_base, triangle_height};
        std::cout << *triangle << std::endl;
      }
    }
    std::cout << std::endl << std::endl;
  } while (input != 'q' && input != 'Q');

  for (const auto& box : toyboxes) {
    delete box;
  }
  return 0;
}

void print_menu() {
  std::cout << "tboxes " << config::get_version_name() << std::endl;
  std::cout << "c  - Create ToyBox" << std::endl;
  std::cout << "l  - List ToyBoxes" << std::endl;
  std::cout << "d  - Display ToyBox contents" << std::endl;
  std::cout << "at - Add Triangle to ToyBox" << std::endl;
  std::cout << "q  - Quit" << std::endl << std::endl;
}
