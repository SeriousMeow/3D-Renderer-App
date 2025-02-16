/**
 * @file
 * @brief Ядро приложения
 */

#pragma once

#include "models/3D_scene.hpp"

namespace app {
/**
 * @brief Взаимодействует с моделями приложения
 */
class AppKernel {
public:
    AppKernel();

protected:
    app::models::Scene scene_;
};

}  // namespace app
