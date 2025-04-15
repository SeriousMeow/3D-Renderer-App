/**
 * @file
 * @brief Интерфейс приложения
 */

#pragma once

#include "controllers/engine_controller.hpp"
#include "interface/camera_info.hpp"
#include "interface/cameras_list.hpp"
#include "interface/image_region.hpp"
#include "interface/main_window.hpp"
#include "interface/object_info.hpp"
#include "interface/objects_list.hpp"

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
    gui::ImageRegion image_region_;
    gui::CameraInfo camera_info_;
    gui::ObjectInfo object_info_;
    gui::ObjectsList objects_list_;
    gui::CamerasList cameras_list_;
    controllers::EngineController engine_controller_;
};

}  // namespace app
