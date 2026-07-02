#include <QApplication>
#include <QQuickStyle>
#include "AppBootstrap.h"

int main(int argc, char *argv[]) {
    QQuickStyle::setStyle("Basic");
    QApplication app(argc, argv);
    AppBootstrap bootstrap;
    bootstrap.bootstrap();
    return app.exec();
}
