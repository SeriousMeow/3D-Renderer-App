#include "camera_monitor.hpp"

namespace app::models {

CameraMonitor::CameraMonitor()
    : scene_{[this](const Scene& scene) { UpdateData(scene); },

             [this](const Scene& scene) { UpdateData(scene); },

             [this](const Scene& scene) { UpdateData(scene); }},
      selected_camera_{[this](CameraId camera_id) { camera_id_ = camera_id; },
                       [this](CameraId camera_id) { camera_id_ = camera_id; },
                       [this](CameraId camera_id) { camera_id_ = camera_id; }

      } {
}

void CameraMonitor::SubscribeCameraPosition(ports::PortIn<renderer::Point>* port) {
    camera_position_.Subscribe(port);
}

void CameraMonitor::SubscribeCameraAngles(ports::PortIn<CameraAngles>* port) {
    camera_angles_.Subscribe(port);
}

ports::PortIn<CameraMonitor::Scene>* CameraMonitor::GetScenePort() {
    return &scene_;
}

ports::PortIn<CameraMonitor::CameraId>* CameraMonitor::GetCameraPort() {
    return &selected_camera_;
}

void CameraMonitor::UpdateData(const Scene& scene) {
    if (not selected_camera_.IsSubscribed()) {  // не подключена камера - работы нет
        return;
    }
    {
        assert((scene.HasCamera(camera_id_)) and
               "CameraMonitor: передаваемая камера должна находиться в сцене");
    }
    const renderer::Camera& camera = scene.AccessCamera(camera_id_);
    camera_position_.GetHandle().AccessData() = camera.GetPosition();
    auto angles_handle = camera_angles_.GetHandle();
    angles_handle.AccessData().yaw = camera.GetYaw();
    angles_handle.AccessData().pitch = camera.GetPitch();
}

}  // namespace app::models
