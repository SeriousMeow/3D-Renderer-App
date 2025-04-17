#include "main_window.hpp"

#include "ui_main_window.h"

namespace app::gui {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);
    show();
}

Ui::MainWindow* MainWindow::AccessUi() {
    return ui_.get();
}

}  // namespace app::gui
