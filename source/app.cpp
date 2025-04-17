#include "app.hpp"

namespace app {

App::App() : AppKernel{}, AppGUI{&engine_} {
    engine_.SubscribeImage(image_region_.GetImagePort());
    engine_.SubscribeSelectedCamera(camera_monitor_.GetCameraPort());
    engine_.SubscribeScene(camera_monitor_.GetScenePort());

    camera_monitor_.SubscribeCameraPosition(camera_info_.GetCameraPositionPort());
    camera_monitor_.SubscribeCameraAngles(camera_info_.GetCameraAnglesPort());

    object_monitor_.SubscribeObjectPosition(object_info_.GetObjectPositionPort());
    object_monitor_.SubscribeObjectAngles(object_info_.GetObjectAnglesPort());
    object_monitor_.SubscribeObjectScale(object_info_.GetObjectScalePort());

    engine_.SubscribeAvailableObjects(objects_list_.GetObjectsListPort());
    engine_.SubscribeSelectedObject(objects_list_.GetObjectPort());

    engine_.SubscribeAvailableCameras(cameras_list_.GetCamerasListPort());
    engine_.SubscribeSelectedCamera(cameras_list_.GetCameraPort());
}

}  // namespace app
