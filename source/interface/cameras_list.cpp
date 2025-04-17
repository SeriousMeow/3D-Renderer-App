#include "cameras_list.hpp"

#include <QSignalBlocker>

namespace app::gui {

CamerasList::CamerasList(QListWidget* cameras_list)
    : cameras_list_field_{cameras_list},
      cameras_list_{[this](const std::vector<CameraId>& list) { UpdateCamerasList(list); }},
      selected_camera_{
          [this](const CameraId new_camera_id) { UpdateSelectedCamera(new_camera_id); }} {
    {
        assert(cameras_list and "CamerasList: cameras_list не должен быть nullptr");
    }
}

ports::PortIn<std::vector<CamerasList::CameraId>>* CamerasList::GetCamerasListPort() {
    return &cameras_list_;
}

ports::PortIn<CamerasList::CameraId>* CamerasList::GetCameraPort() {
    return &selected_camera_;
}

void CamerasList::UpdateCamerasList(const std::vector<CameraId>& new_cameras_list) {
    {
        assert(cameras_list_field_ and
               "CamerasListList::UpdateCamerasList: cameras_list_field_ не должен быть nullptr");
    }
    QSignalBlocker lock(cameras_list_field_);
    cameras_list_field_->clear();
    for (ssize_t row = 0; row < new_cameras_list.size(); ++row) {
        cameras_list_field_->insertItem(row, QString::number(new_cameras_list[row]));
    }
    if (selected_camera_
            .IsSubscribed()) {  // после перезаписи элементов выставить старый выбранный объект
        UpdateSelectedCamera(selected_camera_.GetData());
    }
}

void CamerasList::UpdateSelectedCamera(const CameraId new_camera_id) {
    {
        assert(cameras_list_field_ and
               "CamerasList::UpdateSelectedCamera: cameras_list_field_ не должен быть nullptr");
    }
    QSignalBlocker lock(cameras_list_field_);
    int selected_row = -1;
    for (int row = 0; row < cameras_list_field_->count(); ++row) {
        if (cameras_list_field_->item(row)->text() == QString::number(new_camera_id)) {
            selected_row = row;
            break;
        }
    }
    if (selected_row !=
        -1) {  // выбранного объекта нет в списке - нет объектов/нет выбранного объекта
        cameras_list_field_->setCurrentRow(selected_row);
    }
}

}  // namespace app::gui
