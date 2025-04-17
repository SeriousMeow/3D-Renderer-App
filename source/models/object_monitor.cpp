#include "object_monitor.hpp"

namespace app::models {

ObjectMonitor::ObjectMonitor()
    : scene_{[this](const Scene&) { UpdateData(); }},
      selected_object_{[this](ObjectId) { UpdateData(); }} {
}

void ObjectMonitor::SubscribeObjectPosition(ports::PortIn<renderer::Point>* port) {
    object_position_.Subscribe(port);
}

void ObjectMonitor::SubscribeObjectAngles(ports::PortIn<ObjectAngles>* port) {
    object_angles_.Subscribe(port);
}

void ObjectMonitor::SubscribeObjectScale(ports::PortIn<float>* port) {
    object_scale_.Subscribe(port);
}

ports::PortIn<ObjectMonitor::Scene>* ObjectMonitor::GetScenePort() {
    return &scene_;
}

ports::PortIn<ObjectMonitor::ObjectId>* ObjectMonitor::GetObjectPort() {
    return &selected_object_;
}

void ObjectMonitor::UpdateData() {
    if (not scene_.IsSubscribed()) {  // нет сцены - работы нет
        return;
    }
    if (not selected_object_.IsSubscribed()) {  // не подключен объект - работы нет
        return;
    }
    if (not scene_.GetData().HasObject(
            selected_object_.GetData())) {  // нет объекта - нечего менять
        return;
    }
    const renderer::SceneObject& object = scene_.GetData().AccessObject(selected_object_.GetData());

    object_position_.GetHandle().AccessData() = object.AccessPosition();

    auto angles_handle = object_angles_.GetHandle();
    angles_handle.AccessData().x_angle = object.AccessXAngle();
    angles_handle.AccessData().y_angle = object.AccessYAngle();
    angles_handle.AccessData().z_angle = object.AccessZAngle();

    object_scale_.GetHandle().AccessData() = object.AccessScale();
}

}  // namespace app::models
