/**
 * @file
 * @brief Класс приложения
 */

#pragma once

#include "app_gui.hpp"
#include "app_kernel.hpp"

/**
 * @brief Функциональность приложения
 */
namespace app {
/**
 * @brief Центральный класс приложения
 */
class App : AppKernel, AppGUI {
public:
    App();

private:
};

}  // namespace app
