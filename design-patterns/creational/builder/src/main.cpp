#include <iostream>
#include <ostream>
#include <string>
#include <vector>

class CodeBuilder {
 private:
  std::string class_name;
  struct Field {
    std::string name;
    std::string type;
  };
  std::vector<Field> fields;

 public:
  CodeBuilder(const std::string& class_name) : class_name{class_name} {}

  CodeBuilder& add_field(const std::string& name, const std::string& type) {
    fields.push_back({name, type});
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const CodeBuilder& obj) {
    os << "class " << obj.class_name << "\n"
       << "{\n";
    for (const auto& field : obj.fields) {
      os << "  " << field.type << " " << field.name << ";\n";
    }
    os << "}\n";
    return os;
  }
};

int main() {
  std::cout << "Hello" << std::endl;
  const auto student = CodeBuilder{"Student"}
                           .add_field("age", "int")
                           .add_field("name", "std::string");
  std::cout << student << std::endl;
  return 0;
}
