#include "widget.h"
#include "formtext.h"
#include "form.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // Widget w;
    //w.show();
    //FormText f;
    Form f;
    f.show();
    return a.exec();
}
