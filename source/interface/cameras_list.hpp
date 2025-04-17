/**
 * @file
 * @brief Обновление списка камер
 */
#pragma once

#include <QListWidget>

#include "../models/3D_engine.hpp"
#include "../utils/ports.hpp"

namespace app::gui {

/**
 * @brief Обновляет список камер в интерфейсе
 */
class CamerasList {
public:
    using CameraId = models::Engine::CameraId;

    /**
     * @brief Создание CamerasList
     *
     * @param[in] cameras_list Список с объектами
     */
    CamerasList(QListWidget* cameras_list);

    /**
     * @brief Получение указателя на порт списка камер
     *
     * Возвращает указатель на входной порт для подключения списка камер
     *
     * @return Указатель на порт списка камер
     */
    ports::PortIn<std::vector<CameraId>>* GetCamerasListPort();

    /**
     * @brief Получение указателя на порт камеры
     *
     * Возвращает указатель на входной порт для подключения камеры
     *
     * @return Указатель на порт камеры
     */
    ports::PortIn<CameraId>* GetCameraPort();

private:
    /**
     * Обновляет список камер в интерфейсе
     */
    void UpdateCamerasList(const std::vector<CameraId>& new_cameras_list);

    /**
     * Обновляет выбранную камеру в списке
     */
    void UpdateSelectedCamera(const CameraId new_camera_id);

    QListWidget* cameras_list_field_;
    ports::PortIn<std::vector<CameraId>> cameras_list_;
    ports::PortIn<CameraId> selected_camera_;
};

}  // namespace app::gui
