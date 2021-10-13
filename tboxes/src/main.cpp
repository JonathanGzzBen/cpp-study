#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

#include "src/config.h"
#include "src/invalid_measures_exception.h"
#include "src/square.h"
#include "src/toybox.h"
#include "src/toybox_not_found.h"
#include "src/triangle.h"

void print_menu();
void add_box(std::vector<ToyBox*>* const toyboxes);
void list_toyboxes(const std::vector<ToyBox*>& toyboxes);
void display_toybox(const std::vector<ToyBox*>& toyboxes);
void add_figure(std::vector<ToyBox*>* const toyboxes);
void add_triangle(std::vector<ToyBox*>* const toyboxes);
void add_square(std::vector<ToyBox*>* const toyboxes);
std::unique_ptr<Triangle> read_triangle();
std::unique_ptr<Square> read_square();
ToyBox* find_box(const std::string box_name,
                 const std::vector<ToyBox*>& toyboxes);

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
      case 'f':
      case 'F': {
        add_figure(&toyboxes);
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
  std::cout << "f - Add new Figure to ToyBox" << std::endl;
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
      std::vector<Triangle*> triangles{};
      std::vector<Square*> squares{};
      for (const auto& figure : toybox->get_figures()) {
        auto triangle{dynamic_cast<Triangle*>(figure.get())};
        if (triangle != nullptr) {
          triangles.push_back(triangle);
        }
        auto square{dynamic_cast<Square*>(figure.get())};
        if (square != nullptr) {
          squares.push_back(square);
        }
      }
      std::cout << "Triangles:" << std::endl;
      for (const auto& triangle : triangles) {
        std::cout << std::setw(20) << *triangle << std::endl;
      }
      std::cout << "Squares:" << std::endl;
      for (const auto& square : squares) {
        std::cout << std::setw(20) << *square << std::endl;
      }
      std::cout << std::endl;
      return;
    }
  }
  std::cout << "No box with that name found." << std::endl;
}

void add_figure(std::vector<ToyBox*>* const toyboxes) {
  std::cout << "Which figure do you wish to add? " << config::get_version_name()
            << std::endl;
  std::cout << "t  - Triangle" << std::endl;
  std::cout << "s  - Square" << std::endl;
  std::cout << "q  - Cancel" << std::endl << std::endl;

  std::cout << "Selection: ";
  char selection{'\0'};
  std::cin >> selection;
  switch (selection) {
    case 't':
    case 'T': {
      add_triangle(toyboxes);
      break;
    }
    case 's':
    case 'S': {
      add_square(toyboxes);
      break;
    }
  }
}

void add_triangle(std::vector<ToyBox*>* const toyboxes) {
  try {
    std::cout << "Enter measures of new triangle:" << std::endl;
    auto triangle{read_triangle()};
    std::cout << "Target box: ";
    std::string target_box;
    std::cin >> target_box;
    auto box{find_box(target_box, *toyboxes)};
    box->get_figures().push_back(std::move(triangle));
  } catch (InvalidMeasuresException& ex) {
    std::cout << ex.what() << std::endl;
  } catch (ToyBoxNotFound& ex) {
    std::cout << ex.what() << std::endl;
  }
}

void add_square(std::vector<ToyBox*>* const toyboxes) {
  std::cout << "Enter measures of new square:" << std::endl;
  try {
    auto square{read_square()};
    std::cout << "Target box: ";
    std::string target_box;
    std::cin >> target_box;
    auto box = find_box(target_box, *toyboxes);
    box->get_figures().push_back(std::move(square));
  } catch (InvalidMeasuresException& ex) {
    std::cout << ex.what() << std::endl;
  } catch (ToyBoxNotFound& ex) {
    std::cout << ex.what() << std::endl;
  }
}

std::unique_ptr<Triangle> read_triangle() {
  std::cout << "Triangle base: ";
  int triangle_base{0};
  std::cin >> triangle_base;
  std::cout << "Triangle height: ";
  int triangle_height{0};
  std::cin >> triangle_height;
  if (triangle_base <= 0) {
    throw InvalidMeasuresException{"Base of triangle must be positive"};
  } else if (triangle_height <= 0) {
    throw InvalidMeasuresException{"Height of triangle must be positive"};
  }
  auto triangle = std::make_unique<Triangle>(triangle_base, triangle_height);
  return triangle;
}

std::unique_ptr<Square> read_square() {
  std::cout << "Square side length: ";
  int square_side{0};
  std::cin >> square_side;
  if (square_side <= 0) {
    throw InvalidMeasuresException{"Sides of square must be positive values"};
  }
  auto square = std::make_unique<Square>(square_side);
  return square;
}

ToyBox* find_box(const std::string box_name,
                 const std::vector<ToyBox*>& toyboxes) {
  for (const auto& box : toyboxes) {
    if (box->get_name() == box_name) {
      return box;
    }
  }
  throw ToyBoxNotFound{box_name};
}
