/**
 * @file
 * @brief Наблюдение за текущим объектом
 */

#pragma once

#include <renderer/scene.hpp>

#include "../utils/ports.hpp"

namespace app::models {

/**
 * @brief Наблюдает за текущим объектом и выдает необходимую информацию
 *
 * Подключается к изменениям сцены и выбранного объекта. При изменении сцены собирает информацию о
 * новом положении объекта, углах поворота и масштабе, после чего выдает их на свои
 * выходные порты. Если объекта нет в сцене, то значение произвольное
 */
class ObjectMonitor {
    /**
     * @brief Тип сцены
     */
    using Scene = renderer::Scene;

    /**
     * @brief Тип ID объекта
     */
    using ObjectId = renderer::Scene::ObjectId;

public:
    /**
     * @brief Возвращаемые углы объекта
     */
    struct ObjectAngles {
        float x_angle;
        float y_angle;
        float z_angle;
    };
    /**
     * @brief Создание ObjectMonitor
     */
    ObjectMonitor();

    /**
     * @brief Подписка на изменение позиции объекта
     *
     * Подписывает переданный порт на изменение позиции текущего выбранного объетка. Если монитор не
     * подписан на сцену и объект, то значение произвольное
     *
     * @param[in] port Порт для подписания
     */
    void SubscribeObjectPosition(ports::PortIn<renderer::Point>* port);

    /**
     * @brief Подписка на изменение углов объекта
     *
     * Подписывает переданный порт на изменение углов текущего выбранного объетка. Если монитор не
     * подписан на сцену и объект, то значение произвольное
     *
     * @param[in] port Порт для подписания
     */
    void SubscribeObjectAngles(ports::PortIn<ObjectAngles>* port);

    /**
     * @brief Подписка на изменение масштаба объекта
     *
     * Подписывает переданный порт на изменение масштаба текущего выбранного объетка. Если монитор
     * не подписан на сцену и объект, то значение произвольное
     *
     * @param[in] port Порт для подписания
     */
    void SubscribeObjectScale(ports::PortIn<float>* port);

    /**
     * @brief Получение указателя на порт сцены
     *
     * Возвращает указатель на входной порт для подключения сцены
     *
     * @return Указатель на порт сцены
     */
    ports::PortIn<Scene>* GetScenePort();

    /**
     * @brief Получение указателя на порт объекта
     *
     * Возвращает указатель на входной порт для подключения объекта
     *
     * @return Указатель на порт объекта
     */
    ports::PortIn<ObjectId>* GetObjectPort();

private:
    /**
     * @brief Обновление значений в портах
     *
     * Обновляет значения в выходных портах
     */
    void UpdateData();

    ports::PortIn<Scene> scene_;               // информация изменения сцены
    ports::PortIn<ObjectId> selected_object_;  // информация смены объекта

    ports::PortOut<renderer::Point> object_position_;  // позиция объекта
    ports::PortOut<ObjectAngles> object_angles_;       // углы объекта
    ports::PortOut<float> object_scale_;               // масштаб объекта
};

}  // namespace app::models
