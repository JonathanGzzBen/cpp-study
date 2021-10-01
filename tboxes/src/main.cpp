#include <iostream>
#include <memory>
#include <vector>

#include "src/config.h"
#include "src/toybox.h"

void print_menu();
void add_box(std::vector<ToyBox*>* const toyboxes);
void list_toyboxes(const std::vector<ToyBox*>& toyboxes);
void display_toybox(const std::vector<ToyBox*>& toyboxes);
void add_triangle(std::vector<ToyBox*>* const toyboxes);

int main(int argc, char** argv) {
  std::vector<ToyBox*> toyboxes;
  char input{'\0'};
  do {
    print_menu();
    std::cout << "Selection: ";
    std::cin >> input;
    std::cout << std::endl;
    switch (input) {
      case 'c':
      case 'C': {
        add_box(&toyboxes);
        break;
      }
      case 'l':
      case 'L': {
        list_toyboxes(toyboxes);
        break;
      }
      case 'd':
      case 'D': {
        display_toybox(toyboxes);
        break;
      }
      case 't':
      case 'T': {
        add_triangle(&toyboxes);
        break;
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

void add_box(std::vector<ToyBox*>* const toyboxes) {
  std::cout << "Enter box name: ";
  std::string box_name;
  std::cin >> box_name;
  ToyBox* new_box = new ToyBox{box_name};
  std::cout << "Created ToyBox " << new_box->get_name() << std::endl;
  toyboxes->push_back(new_box);
}

void list_toyboxes(const std::vector<ToyBox*>& toyboxes) {
  std::cout << "Boxes:" << std::endl;
  for (const auto& toybox : toyboxes) {
    std::cout << toybox->get_name() << std::endl;
  }
}

void display_toybox(const std::vector<ToyBox*>& toyboxes) {
  std::cout << "Which box do you want to display?: ";
  std::string box_name;
  std::cin >> box_name;
  for (const auto& toybox : toyboxes) {
    if (toybox->get_name() == box_name) {
      std::cout << "Triangles:" << std::endl;
      for (const auto& triangle : toybox->get_triangles()) {
        std::cout << *triangle << std::endl;
      }
      std::cout << std::endl;
    }
  }
}

void add_triangle(std::vector<ToyBox*>* const toyboxes) {
  std::cout << "Enter measures of new triangle" << std::endl;
  std::cout << "Triangle base: ";
  int triangle_base{0};
  std::cin >> triangle_base;
  std::cout << "Triangle height: ";
  int triangle_height{0};
  std::cin >> triangle_height;
  auto triangle = std::make_unique<Triangle>(triangle_base, triangle_height);

  std::cout << "Target box: ";
  std::string target_box;
  std::cin >> target_box;
  for (const auto& box : *toyboxes) {
    if (box->get_name() == target_box) {
      box->get_triangles().push_back(std::move(triangle));
      return;
    }
  }
}
