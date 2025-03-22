#include "camera_monitor.hpp"

namespace app::models {

CameraMonitor::CameraMonitor()
    : scene_{[this](const Scene&) { UpdateData(); }, [this](const Scene&) { UpdateData(); },
             [this](const Scene& scene) { UpdateData(); }},
      selected_camera_{[this](CameraId) { UpdateData(); }, [this](CameraId) { UpdateData(); },
                       [this](CameraId) { UpdateData(); }} {
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

void CameraMonitor::UpdateData() {
    if (not scene_.IsSubscribed()) {  // нет сцены - нет работы
        return;
    }
    if (not selected_camera_.IsSubscribed()) {  // не подключена камера - работы нет
        return;
    }
    {
        assert((scene_.GetData().HasCamera(selected_camera_.GetData())) and
               "CameraMonitor: передаваемая камера должна находиться в сцене");
    }
    const renderer::Camera& camera = scene_.GetData().AccessCamera(selected_camera_.GetData());
    camera_position_.GetHandle().AccessData() = camera.GetPosition();

    auto angles_handle = camera_angles_.GetHandle();
    angles_handle.AccessData().yaw = camera.GetYaw();
    angles_handle.AccessData().pitch = camera.GetPitch();
}

}  // namespace app::models
