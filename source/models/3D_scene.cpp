#include "3D_scene.hpp"

namespace app::models {

void Scene::SubscribeScenePort(ports::PortIn<renderer::Scene>* port) {
    {
        assert(port and "SubscribeView: port не может быть nullptr");
    }
    scene_.Subscribe(port);
}

}  // namespace app::models
