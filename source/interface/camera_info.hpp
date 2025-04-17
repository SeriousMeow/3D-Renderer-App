/**
 * @file
 * @brief Обновление информации о камере
 */

#pragma once

#include <QDoubleSpinBox>
#include <renderer/types.hpp>

#include "../models/camera_monitor.hpp"
#include "../utils/ports.hpp"

namespace app::gui {

/**
 * @brief Обновляет информацию о координатах камеры в интерфейсе
 */
class CameraInfo {
public:
    using CameraAngles = models::CameraMonitor::CameraAngles;

    /**
     * @brief Создание CameraInfo
     *
     * @param[in] x Поле ввода x
     * @param[in] y Поле ввода y
     * @param[in] z Поле ввода z
     * @param[in] yaw Поле ввода yaw
     * @param[in] pitch Поле ввода pitch
     */
    CameraInfo(QDoubleSpinBox* x, QDoubleSpinBox* y, QDoubleSpinBox* z, QDoubleSpinBox* yaw,
               QDoubleSpinBox* pitch);

    /**
     * @brief Получение указателя на порт позиции камеры
     *
     * Возвращает указатель на входной порт для позиции камеры
     *
     * @return Указатель на порт позиции
     */
    ports::PortIn<renderer::Point>* GetCameraPositionPort();

    /**
     * @brief Получение указателя на порт углов камеры
     *
     * Возвращает указатель на входной порт для углов камеры
     *
     * @return Указатель на порт углов
     */
    ports::PortIn<CameraAngles>* GetCameraAnglesPort();

private:
    /**
     * Обновляет позицию в интерфейсе
     */
    void UpdatePosition(const renderer::Point& position);

    /**
     * Обновляет углы в интерфейсе
     */
    void UpdateAngles(const CameraAngles& angles);

    ports::PortIn<renderer::Point> camera_position_;  // позиция камеры
    ports::PortIn<CameraAngles> camera_angles_;       // углы взгляда камеры

    QDoubleSpinBox* x_field_;
    QDoubleSpinBox* y_field_;
    QDoubleSpinBox* z_field_;
    QDoubleSpinBox* yaw_field_;
    QDoubleSpinBox* pitch_field_;
};

}  // namespace app::gui
