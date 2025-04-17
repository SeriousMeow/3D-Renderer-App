#include <QApplication>

#include "app.hpp"
#include "except.hpp"

int main(int argc, char* argv[]) {
    QApplication qruntime(argc, argv);
    try {
        app::App app;
        return qruntime.exec();
    } catch (...) {
        return app::except::React();
    }
    return 0;
}
