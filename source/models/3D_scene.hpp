/**
 * @file
 * @brief Работа с 3D сценой
 */

#pragma once

#include <renderer/scene.hpp>

#include "../utils/ports.hpp"

namespace app {
namespace models {
/**
 * @brief 3D сцена
 */
class Scene {
public:
    /**
     * @brief Подписываение порта сцены
     *
     * Подписывает переданный порт на ищменения сцены
     *
     * @param[in] port Порт для подписания
     */
    void SubscribeScenePort(ports::PortIn<renderer::Scene>* port);

private:
    ports::PortOut<renderer::Scene> scene_;
};

}  // namespace models
}  // namespace app
