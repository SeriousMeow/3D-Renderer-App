#include "3D_engine.hpp"

#include <renderer/utils.hpp>

namespace app::models {

Engine::Engine()
    : on_scene_change_{[this](const Scene&) { Render(); }},
      rendered_image_{Image{renderer::Width{0}, renderer::Height{0}}} {
    SpawnCamera();
    scene_.Subscribe(&on_scene_change_);
    {
        // пока нет управления освещением, оно задается статически
        auto handle = scene_.GetHandle();
        handle.AccessData().PushLight(
            renderer::DirectionalLight{.strength = 0.2, .direction = {-1, 0, 0}});
        handle.AccessData().PushLight(renderer::AmbientLight{.strength = 0.5});
        handle.AccessData().PushLight(renderer::PointLight{.strength = 10, .position = {0, 0, 3}});
    }
}

void Engine::SubscribeSelectedCamera(ports::PortIn<CameraId>* port) {
    selected_camera_.Subscribe(port);
}

void Engine::SubscribeAvailableCameras(ports::PortIn<std::vector<CameraId>>* port) {
    available_cameras_.Subscribe(port);
}

void Engine::SubscribeSelectedObject(ports::PortIn<ObjectId>* port) {
    selected_object_.Subscribe(port);
}

void Engine::SubscribeAvailableObjects(ports::PortIn<std::vector<ObjectId>>* port) {
    available_objects_.Subscribe(port);
}

void Engine::SubscribeImage(ports::PortIn<Image>* port) {
    rendered_image_.Subscribe(port);
}

void Engine::SubscribeScene(ports::PortIn<Scene>* port) {
    scene_.Subscribe(port);
}

void Engine::Resize(const Width width, const Height height) {
    width_ = width;
    height_ = height;
    scene_.Notify();  // подробнее в todo в private секции 3D_engine.hpp
}

void Engine::SpawnCamera() {
    CameraId new_camera;
    auto handle = scene_.GetHandle();
    new_camera =
        handle.AccessData().PushCamera(renderer::Camera{renderer::Point{0, 0, 0}, 0, 0, 90, 0.1});
    available_cameras_.GetHandle().AccessData().push_back(new_camera);
    selected_camera_.GetHandle().AccessData() = new_camera;
}

void Engine::LoadObjectFromFile(const std::string& path) {
    renderer::Object new_object = renderer::utils::LoadFile(path);
    if (new_object.Begin() == new_object.End()) {  // пустой объект
        return;
    }
    ObjectId object_id = scene_.GetHandle().AccessData().PushObject(new_object);
    available_objects_.GetHandle().AccessData().push_back(object_id);
    selected_object_.GetHandle().AccessData() = object_id;
}

void Engine::SwitchCamera(const CameraId new_camera_id) {
    {
        assert((scene_.AccessData().HasCamera(new_camera_id)) and
               "SwitchCamera: новая камера должна быть в сцене");
    }
    selected_camera_.GetHandle().AccessData() = new_camera_id;
    scene_.Notify();  // подробнее в todo в private секции 3D_engine.hpp
}

void Engine::SwitchObject(const ObjectId new_object_id) {
    {
        assert((scene_.AccessData().HasObject(new_object_id)) and
               "SwitchObject: новая камера должна быть в сцене");
    }
    selected_object_.GetHandle().AccessData() = new_object_id;
    scene_.Notify();  // подробнее в todo в private секции 3D_engine.hpp
}

void Engine::SetCameraPosition(const renderer::Point& new_position) {
    auto handle = scene_.GetHandle();
    renderer::Camera& camera = handle.AccessData().AccessCamera(selected_camera_.AccessData());
    camera.SetPosition(new_position);
}

void Engine::SetCameraAngles(const float new_yaw, const float new_pitch) {
    auto handle = scene_.GetHandle();
    renderer::Camera& camera = handle.AccessData().AccessCamera(selected_camera_.AccessData());
    camera.SetYaw(new_yaw);
    camera.SetPitch(new_pitch);
}

void Engine::MoveCamera(const float forward_distance, const float right_distance,
                        const float up_distance) {
    auto handle = scene_.GetHandle();
    renderer::Camera& camera = handle.AccessData().AccessCamera(selected_camera_.AccessData());
    camera.MoveForward(forward_distance);
    camera.MoveRight(right_distance);
    camera.MoveWorldUp(up_distance);
}

void Engine::RotateCamera(const float yaw_offset, const float pitch_offset) {
    auto handle = scene_.GetHandle();
    renderer::Camera& camera = handle.AccessData().AccessCamera(selected_camera_.AccessData());
    camera.AddYaw(yaw_offset);
    camera.AddPitch(pitch_offset);
}

void Engine::SetObjectPosition(const renderer::Point& new_position) {
    if (not scene_.AccessData().HasObject(selected_object_.AccessData())) {  // нет объекта
        return;
    }
    auto handle = scene_.GetHandle();
    renderer::SceneObject& object = handle.AccessData().AccessObject(selected_object_.AccessData());
    object.AccessPosition() = new_position;
}

void Engine::SetObjectAngles(const float new_x_angle, const float new_y_angle,
                             const float new_z_angle) {
    if (not scene_.AccessData().HasObject(selected_object_.AccessData())) {  // нет объекта
        return;
    }
    auto handle = scene_.GetHandle();
    renderer::SceneObject& object = handle.AccessData().AccessObject(selected_object_.AccessData());
    object.AccessXAngle() = new_x_angle;
    object.AccessYAngle() = new_y_angle;
    object.AccessZAngle() = new_z_angle;
}

void Engine::SetObjectScale(const float new_scale) {
    if (not scene_.AccessData().HasObject(selected_object_.AccessData())) {  // нет объекта
        return;
    }
    auto handle = scene_.GetHandle();
    renderer::SceneObject& object = handle.AccessData().AccessObject(selected_object_.AccessData());
    object.AccessScale() = new_scale;
}

void Engine::Render() {
    Image image{renderer::Width{width_}, renderer::Height{height_}};
    image = renderer_.Render(scene_.AccessData(), selected_camera_.AccessData(), std::move(image),
                             renderer::Renderer::DRAW_FACETS | renderer::Renderer::ENABLE_LIGHT);
    rendered_image_.GetHandle().AccessData() = std::move(image);
}

}  // namespace app::models
