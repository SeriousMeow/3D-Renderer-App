#include "app.hpp"

namespace app {

App::App() : AppKernel{}, AppGUI{&engine_} {
    engine_.SubscribeImage(view_.GetImagePort());
    engine_.SubscribeSelectedCamera(camera_monitor_.GetCameraPort());
    engine_.SubscribeScene(camera_monitor_.GetScenePort());
    camera_monitor_.SubscribeCameraPosition(camera_info_.GetCameraPositionPort());
    camera_monitor_.SubscribeCameraAngles(camera_info_.GetCameraAnglesPort());
}

}  // namespace app
