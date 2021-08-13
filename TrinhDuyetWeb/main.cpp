#include <QApplication>
#include "TrinhDuyet.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    TrinhDuyet trinhDuyet;
    trinhDuyet.show();

    return app.exec();
}
