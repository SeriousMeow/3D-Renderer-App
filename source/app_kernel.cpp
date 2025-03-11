#include "app_kernel.hpp"

namespace app {

AppKernel::AppKernel() {
    engine_.SubscribeSelectedCamera(camera_monitor_.GetCameraPort());
    engine_.SubscribeScene(camera_monitor_.GetScenePort());
}

}  // namespace app
