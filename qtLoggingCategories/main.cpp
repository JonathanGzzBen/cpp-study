#include <QCoreApplication>
#include <QDebug>
#include <QLoggingCategory>

void test(QLoggingCategory &lcat) {
  qDebug(lcat) << "Debug";
  qInfo(lcat) << "Info";
  qWarning(lcat) << "Warning";
  qCritical(lcat) << "Critical";
}

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  QLoggingCategory myCategory("myCategory");
  myCategory.setEnabled(QtDebugMsg, false);
  test(myCategory);

  return a.exec();
}
