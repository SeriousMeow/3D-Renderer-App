/**
 * @file
 * @brief Интерфейс приложения
 */

#pragma once

#include "interface/main_window.hpp"
#include "interface/view.hpp"

namespace app {
/**
 * @brief Взаимодействует с интерфейсом приложения
 */
class AppGUI {
public:
    AppGUI();

protected:
    MainWindow main_window_;
    View view_;
};

}  // namespace app
