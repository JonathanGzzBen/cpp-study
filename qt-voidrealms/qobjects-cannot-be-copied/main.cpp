#include "cat.h"
#include <QCoreApplication>

void test(Cat *cat) { qInfo() << cat; }

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);

  Cat kitty;
  kitty.setObjectName("kitty");
  Cat death;
  death.setObjectName("The grim reaper");
  test(&kitty);
  test(&death);

  return a.exec();
}
