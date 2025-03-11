/**
 * @file
 * @brief Наблюдение за текущей
 */

#pragma once

#include <renderer/scene.hpp>

#include "../utils/ports.hpp"

namespace app::models {

/**
 * @brief Наблюдает за текущей камерой и выдает необходимую информацию
 *
 * Подключается к изменениям сцены и выбранной камеры. При изменении сцены собирает информацию о
 * новом положении камеры и углах, описывающих направление взгляда, после чего выдает их на свои
 * выходные порты. Требуется, чтобы выбранная камера находилась в сцене
 */
class CameraMonitor {
    /**
     * @brief Тип сцены
     */
    using Scene = renderer::Scene;

    /**
     * @brief Тип ID камеры
     */
    using CameraId = renderer::Scene::CameraId;

public:
    /**
     * @brief Возвращаемые углы камеры
     */
    struct CameraAngles {
        float yaw;
        float pitch;
    };

    /**
     * @brief Создание CameraMonitor
     */
    CameraMonitor();

    /**
     * @brief Подписка на изменение позиции камеры
     *
     * Подписывает переданный порт на изменение позиции текущей выбранной камеры. Если объект не
     * подписан на сцену и камеру, то значение произвольное
     *
     * @param[in] port Порт для подписания
     */
    void SubscribeCameraPosition(ports::PortIn<renderer::Point>* port);

    /**
     * @brief Подписка на изменение углов камеры
     *
     * Подписывает переданный порт на изменение углов текущей выбранной камеры. Если объект не
     * подписан на сцену и камеру, то значение произвольное
     *
     * @param[in] port Порт для подписания
     */
    void SubscribeCameraAngles(ports::PortIn<CameraAngles>* port);

    /**
     * @brief Получение указателя на порт сцены
     *
     * Возвращает указатель на входной порт для подключения сцены
     *
     * @return Указатель на порт сцены
     */
    ports::PortIn<Scene>* GetScenePort();

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
     * @brief Обновление значений в портах
     *
     * Обновляет значения в выходных портах
     */
    void UpdateData(const Scene& scene);

    ports::PortIn<Scene> scene_;               // информация изменения сцены
    ports::PortIn<CameraId> selected_camera_;  // информация смены камеры

    CameraId camera_id_;

    ports::PortOut<renderer::Point> camera_position_;  // позиция камеры
    ports::PortOut<CameraAngles> camera_angles_;       // углы камеры
};

}  // namespace app::models
