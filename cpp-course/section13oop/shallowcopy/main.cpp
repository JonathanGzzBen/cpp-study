#include <iostream>
using std::string;

class Item {
 private:
  string name;

 public:
  Item(string name = "Default");
  string get_name();
  bool set_name(string name);
};

Item::Item(string name) : name{name} {}

string Item::get_name() { return this->name; }

bool Item::set_name(string name) {
    this->name = name;
    return true;
}

class Person {
 private:
  string name;
  int age;
  Item *favorite_item;

 public:
  // Shallow copy
  Person(const Person &person);
  Person(string name = "Default", int age = 1, Item *item = new Item());
  string get_name() const;
  int get_age() const;
  string set_name(string name);
  bool set_age(int age);
  Item *get_favorite_item() const;
  bool set_favorite_item(Item *item);
};

Person::Person(string name, int age, Item *item)
    : name{name}, age{age}, favorite_item{item} {}

// Shallow Copy
Person::Person(const Person &person)
    : name{person.name}, age{person.age}, favorite_item(person.favorite_item) {
  std::cout << "Copy constructor of " << person.name << std::endl;
}

string Person::get_name() const { return this->name; }

Item *Person::get_favorite_item() const { return this->favorite_item; }

bool Person::set_favorite_item(Item *item) {
  this->favorite_item = item;
  return true;
}

void print_greeting(Person p) {
  std::cout << "Hey, my name is " << p.get_name() << " and my favorite item is "
            << p.get_favorite_item()->get_name() << std::endl;
}

int main() {
  Person person;
  Item *xbox_controller = new Item("Xbox Controller");
  person.set_favorite_item(xbox_controller);
  print_greeting(person);

  Person person_shallow_copy{person};
  person.get_favorite_item()->set_name("Playstation controller");
  print_greeting(person_shallow_copy);
  print_greeting(person);
}
