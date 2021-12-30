#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include <iostream>
#include <string>

void do_cpp() {
  std::string name;
  std::cout << "Please enter your name: ";
  std::getline(std::cin, name);
  std::cout << "Hello, " << name << std::endl;
}

void do_qt() {
  QTextStream qin(stdin);
  QTextStream qout(stdout);

  qout << "Please enter your name: ";
  qout.flush();
  auto name{qin.readLine()};
  qout << "Hello, " << name << "\n";
  qout.flush();
}

void do_mixed() {
  QTextStream qin(stdin);
  QTextStream qout(stdout);
  qInfo() << "Please enter your name: ";
  auto name{qin.readLine()};
  qInfo() << "Hello, " << name;
}

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  //  do_cpp();
  //  do_qt();
  do_mixed();

  return a.exec();
}
