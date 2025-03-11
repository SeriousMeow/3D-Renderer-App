/**
 * @file
 * @brief Интерфейс приложения
 */

#pragma once

#include "controllers/engine_controller.hpp"
#include "interface/camera_info.hpp"
#include "interface/main_window.hpp"
#include "interface/view.hpp"

namespace app {
/**
 * @brief Взаимодействует с интерфейсом приложения
 */
class AppGUI {
public:
    /**
     * @brief Инициализирует интерфейс приложения
     *
     * @param[in] engine Движок
     */
    AppGUI(models::Engine* engine);

protected:
    gui::MainWindow main_window_;
    gui::View view_;
    gui::CameraInfo camera_info_;
    controllers::EngineController engine_controller_;
};

}  // namespace app
