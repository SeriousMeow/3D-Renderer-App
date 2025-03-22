/**
 * @file
 * @brief Обновление информации об объкте
 */

#pragma once

#include <QDoubleSpinBox>
#include <renderer/types.hpp>

#include "../models/object_monitor.hpp"
#include "../utils/ports.hpp"

namespace app::gui {

/**
 * @brief Обновляет информацию об объекте в интерфейсе
 */
class ObjectInfo {
public:
    using ObjectAngles = models::ObjectMonitor::ObjectAngles;

    /**
     * @brief Создание ObjectInfo
     *
     * @param[in] x Поле ввода x
     * @param[in] y Поле ввода y
     * @param[in] z Поле ввода z
     * @param[in] x_angle Поле ввода угла x
     * @param[in] y_angle Поле ввода угла y
     * @param[in] z_angle Поле ввода угла z
     * @param[in] scale Поле ввода масштаба
     */
    ObjectInfo(QDoubleSpinBox* x, QDoubleSpinBox* y, QDoubleSpinBox* z, QDoubleSpinBox* x_angle,
               QDoubleSpinBox* y_angle, QDoubleSpinBox* z_angle, QDoubleSpinBox* scale);

    /**
     * @brief Получение указателя на порт позиции объекта
     *
     * Возвращает указатель на входной порт для позиции объекта
     *
     * @return Указатель на порт позиции
     */
    ports::PortIn<renderer::Point>* GetObjectPositionPort();

    /**
     * @brief Получение указателя на порт углов объекта
     *
     * Возвращает указатель на входной порт для углов объекта
     *
     * @return Указатель на порт углов
     */
    ports::PortIn<ObjectAngles>* GetObjectAnglesPort();

    /**
     * @brief Получение указателя на порт масштаба
     *
     * Возвращает указатель на входной порт для масштаба объекта
     *
     * @return Указатель на порт масштаба
     */
    ports::PortIn<float>* GetObjectScalePort();

private:
    /**
     * Обновляет позицию в интерфейсе
     */
    void UpdatePosition(const renderer::Point& position);

    /**
     * Обновляет углы в интерфейсе
     */
    void UpdateAngles(const ObjectAngles& angles);

    /**
     * Обновляет масштаб в интерфейсе
     */
    void UpdateScale(const float scale);

    ports::PortIn<renderer::Point> object_position_;  // позиция объекта
    ports::PortIn<ObjectAngles> object_angles_;       // углы объекта
    ports::PortIn<float> object_scale_;               // масштаб объекта

    QDoubleSpinBox* x_field_;
    QDoubleSpinBox* y_field_;
    QDoubleSpinBox* z_field_;

    QDoubleSpinBox* x_angle_field_;
    QDoubleSpinBox* y_angle_field_;
    QDoubleSpinBox* z_angle_field_;

    QDoubleSpinBox* scale_field_;
};

}  // namespace app::gui
