#include "camera_info.hpp"

#include <QSignalBlocker>

namespace app::gui {

CameraInfo::CameraInfo(QDoubleSpinBox* x, QDoubleSpinBox* y, QDoubleSpinBox* z, QDoubleSpinBox* yaw,
                       QDoubleSpinBox* pitch)
    : camera_position_{[this](const renderer::Point& position) { UpdatePosition(position); },
                       [this](const renderer::Point& position) { UpdatePosition(position); },
                       [this](const renderer::Point& position) { UpdatePosition(position); }},
      camera_angles_{[this](const CameraAngles& angles) { UpdateAngles(angles); },
                     [this](const CameraAngles& angles) { UpdateAngles(angles); },
                     [this](const CameraAngles& angles) { UpdateAngles(angles); }

      },
      x_field_{x},
      y_field_{y},
      z_field_{z},
      yaw_field_{yaw},
      pitch_field_{pitch} {
    {
        assert(x and "CameraInfo: x не должен быть nullptr");
        assert(y and "CameraInfo: y не должен быть nullptr");
        assert(z and "CameraInfo: z не должен быть nullptr");
        assert(yaw and "CameraInfo: yaw не должен быть nullptr");
        assert(pitch and "CameraInfo: pitch не должен быть nullptr");
    }
}

ports::PortIn<renderer::Point>* CameraInfo::GetCameraPositionPort() {
    return &camera_position_;
}

ports::PortIn<CameraInfo::CameraAngles>* CameraInfo::GetCameraAnglesPort() {
    return &camera_angles_;
}

void CameraInfo::UpdatePosition(const renderer::Point& position) {
    {
        assert(x_field_ and "CameraInfo::UpdatePosition: x_field_ не должен быть nullptr");
        assert(y_field_ and "CameraInfo::UpdatePosition: y_field_ не должен быть nullptr");
        assert(z_field_ and "CameraInfo::UpdatePosition: z_field_ не должен быть nullptr");
    }
    QSignalBlocker lock_x{x_field_};
    QSignalBlocker lock_y{y_field_};
    QSignalBlocker lock_z{z_field_};
    x_field_->setValue(position.x);
    y_field_->setValue(position.y);
    z_field_->setValue(position.z);
}

void CameraInfo::UpdateAngles(const CameraAngles& angles) {
    {
        assert(yaw_field_ and "CameraInfo::UpdateAngles: yaw_field_ не должен быть nullptr");
        assert(pitch_field_ and "CameraInfo::UpdateAngles: pitch_field_ не должен быть nullptr");
    }
    QSignalBlocker lock_yaw{yaw_field_};
    QSignalBlocker lock_pitch{pitch_field_};
    yaw_field_->setValue(angles.yaw);
    pitch_field_->setValue(angles.pitch);
}

}  // namespace app::gui
