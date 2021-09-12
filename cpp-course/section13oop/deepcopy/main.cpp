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
  // Deep copy
  Person(const Person &person);
  Person(Person &&person);
  Person(string name = "Default", int age = 1, Item *item = new Item());
  Person(string name, int age, Item item);
  ~Person();
  string get_name() const;
  int get_age() const;
  string set_name(string name);
  bool set_age(int age);
  Item *get_favorite_item() const;
  bool set_favorite_item(Item *item);
};

// Deep Copy
Person::Person(const Person &person)
    : Person{person.name, person.age, *person.favorite_item} {
  std::cout << "Copy constructor of " << person.name << std::endl;
}

Person::Person(Person &&person)
    : Person{person.name, person.age, *person.favorite_item} {
  person.name = "";
  person.age = 0;
  person.favorite_item = nullptr;
  std::cout << "Move constructor of " << person.name << std::endl;
}

Person::Person(string name, int age, Item *item)
    : name{name}, age{age}, favorite_item{item} {}

Person::Person(string name, int age, Item item)
    : name{name}, age{age}, favorite_item{new Item{item}} {}

Person::~Person() {
  std::cout << "Released memory of " << favorite_item->get_name() << std::endl;
  delete favorite_item;
}

string Person::get_name() const { return this->name; }

Item *Person::get_favorite_item() const { return this->favorite_item; }

bool Person::set_favorite_item(Item *item) {
  this->favorite_item = item;
  return true;
}

void print_greeting(const Person &p) {
  std::cout << "Hey, my name is " << p.get_name() << " and my favorite item is "
            << p.get_favorite_item()->get_name() << std::endl;
}

Person get_student() { return Person{"Student"}; }

int main() {
  Person person;
  Item *xbox_controller = new Item("Xbox Controller");
  person.set_favorite_item(xbox_controller);
  print_greeting(person);

  Person person_deep_copy{person};
  person.get_favorite_item()->set_name("Playstation controller");
  print_greeting(person_deep_copy);
  print_greeting(person);

  Person another_person{"Eduardo Lim", 19, new Item("Black Desert")};
  print_greeting(another_person);
  print_greeting(std::move(get_student()));
  print_greeting(Person{"Yulion", 19});
}
