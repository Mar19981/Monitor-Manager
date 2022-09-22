#include "monitormanager.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MonitorManager w;
    try {
        w.show();
    }
    catch (std::exception& e) {
        w.hide();

    }
    return a.exec();
}
