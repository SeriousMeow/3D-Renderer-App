#include <QApplication>

#include "app.hpp"
#include "except.hpp"

int main(int argc, char* argv[]) {
    try {
        QApplication app(argc, argv);
        app::App renderer_app;
        return app.exec();
    } catch (...) {
        return app::except::React();
    }
    return 0;
}
