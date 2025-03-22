/**
 * @file
 * @brief Ядро приложения
 */

#pragma once

#include "models/3D_engine.hpp"
#include "models/camera_monitor.hpp"
#include "models/object_monitor.hpp"

namespace app {
/**
 * @brief Взаимодействует с моделями приложения
 */
class AppKernel {
public:
    AppKernel();

protected:
    models::Engine engine_;
    models::CameraMonitor camera_monitor_;
    models::ObjectMonitor object_monitor_;
};

}  // namespace app
