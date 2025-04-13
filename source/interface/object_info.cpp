#include "object_info.hpp"

#include <QSignalBlocker>

namespace app::gui {

ObjectInfo::ObjectInfo(QDoubleSpinBox* x, QDoubleSpinBox* y, QDoubleSpinBox* z,
                       QDoubleSpinBox* x_angle, QDoubleSpinBox* y_angle, QDoubleSpinBox* z_angle,
                       QDoubleSpinBox* scale)
    : object_position_{[this](const renderer::Point& position) { UpdatePosition(position); },
                       [this](const renderer::Point& position) { UpdatePosition(position); },
                       [this](const renderer::Point& position) { UpdatePosition(position); }},
      object_angles_{[this](const ObjectAngles& angles) { UpdateAngles(angles); },
                     [this](const ObjectAngles& angles) { UpdateAngles(angles); },
                     [this](const ObjectAngles& angles) { UpdateAngles(angles); }},
      object_scale_{[this](float scale) { UpdateScale(scale); },
                    [this](float scale) { UpdateScale(scale); },
                    [this](float scale) { UpdateScale(scale); }},
      x_field_{x},
      y_field_{y},
      z_field_{z},
      x_angle_field_{x_angle},
      y_angle_field_{y_angle},
      z_angle_field_{z_angle},
      scale_field_{scale} {
    {
        assert(x and "ObjectInfo: x не должен быть nullptr");
        assert(y and "ObjectInfo: y не должен быть nullptr");
        assert(z and "ObjectInfo: z не должен быть nullptr");

        assert(x_angle and "ObjectInfo: x_angle не должен быть nullptr");
        assert(y_angle and "ObjectInfo: y_angle не должен быть nullptr");
        assert(z_angle and "ObjectInfo: z_angle не должен быть nullptr");

        assert(scale and "ObjectInfo: scale не должен быть nullptr");
    }
}

ports::PortIn<renderer::Point>* ObjectInfo::GetObjectPositionPort() {
    return &object_position_;
}

ports::PortIn<ObjectInfo::ObjectAngles>* ObjectInfo::GetObjectAnglesPort() {
    return &object_angles_;
}

ports::PortIn<float>* ObjectInfo::GetObjectScalePort() {
    return &object_scale_;
}

void ObjectInfo::UpdatePosition(const renderer::Point& position) {
    {
        assert(x_field_ and "ObjectInfo::UpdatePosition: x_field_ не должен быть nullptr");
        assert(y_field_ and "ObjectInfo::UpdatePosition: y_field_ не должен быть nullptr");
        assert(z_field_ and "ObjectInfo::UpdatePosition: z_field_ не должен быть nullptr");
    }
    QSignalBlocker lock_x{x_field_};
    QSignalBlocker lock_y{y_field_};
    QSignalBlocker lock_z{z_field_};
    x_field_->setValue(position.x);
    y_field_->setValue(position.y);
    z_field_->setValue(position.z);
}

void ObjectInfo::UpdateAngles(const ObjectAngles& angles) {
    {
        assert(x_angle_field_ and
               "ObjectInfo::UpdateAngles: x_angle_field_ не должен быть nullptr");
        assert(y_angle_field_ and
               "ObjectInfo::UpdateAngles: y_angle_field_ не должен быть nullptr");
        assert(z_angle_field_ and
               "ObjectInfo::UpdateAngles: z_angle_field_ не должен быть nullptr");
    }
    QSignalBlocker lock_x{x_angle_field_};
    QSignalBlocker lock_y{y_angle_field_};
    QSignalBlocker lock_z{z_angle_field_};
    x_angle_field_->setValue(angles.x_angle);
    y_angle_field_->setValue(angles.y_angle);
    z_angle_field_->setValue(angles.z_angle);
}

void ObjectInfo::UpdateScale(const float scale) {
    {
        assert(scale_field_ and "ObjectInfo::UpdateScale: scale_field_ не должен быть nullptr ");
    }
    QSignalBlocker lock_scale{scale_field_};
    scale_field_->setValue(scale);
}

}  // namespace app::gui
