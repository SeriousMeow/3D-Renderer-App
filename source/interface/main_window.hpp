/**
 * @file
 * @brief Главное окно приложения
 */

#pragma once

#include <QMainWindow>
#include <QScopedPointer>

#include "ui_main_window.h"

namespace Ui {  // NOLINT
class MainWindow;
}

namespace app {

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

    QLabel* RenderRegion() const;

private:
    QScopedPointer<Ui::MainWindow> ui_;
};

}  // namespace app
