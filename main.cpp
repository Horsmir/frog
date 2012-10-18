#include <QtGui/QApplication>
#include "frog.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    frog foo;
    foo.show();
    return app.exec();
}
