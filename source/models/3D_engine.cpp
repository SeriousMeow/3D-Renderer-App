#include "3D_engine.hpp"

#include <renderer/transform.hpp>
#include <renderer/utils.hpp>

namespace app::models {

Engine::Engine()
    : on_scene_change_{[this](const Scene&) { Render(); }, [this](const Scene&) { Render(); },
                       [this](const Scene&) { Render(); }},
      rendered_image_{Image{renderer::Width{0}, renderer::Height{0}}} {
    CameraId camera_id = scene_.GetHandle().AccessData().PushCamera(renderer::Camera{});
    selected_camera_.GetHandle().AccessData() = camera_id;
    available_cameras_.GetHandle().AccessData().push_back(camera_id);
    scene_.Subscribe(&on_scene_change_);
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

void Engine::LoadObjectFromFile(const std::string& path) {
    try {
        renderer::Object new_object = renderer::utils::LoadObjFile(path);
        ObjectId object_id = scene_.GetHandle().AccessData().PushObject(
            new_object, renderer::transforms::kNoTransforms);
        available_objects_.GetHandle().AccessData().push_back(object_id);
        selected_object_.GetHandle().AccessData() = object_id;
    } catch (...) {
    }
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

void Engine::SetCameraPosition(const renderer::Vector& new_position) {
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

void Engine::Render() {
    Image image{renderer::Width{width_}, renderer::Height{height_}};
    image = renderer_.Render(scene_.AccessData(), selected_camera_.AccessData(), std::move(image));
    rendered_image_.GetHandle().AccessData() = std::move(image);
}

}  // namespace app::models
