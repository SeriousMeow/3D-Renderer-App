#include "main_window.hpp"

#include "ui_main_window.h"

namespace app {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);
}

QLabel* MainWindow::RenderRegion() const {
    return ui_->RenderRegion;
}

}  // namespace app
