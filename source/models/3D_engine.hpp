/**
 * @file
 * @brief Работа с 3D
 */

#pragma once

#include <renderer/image.hpp>
#include <renderer/renderer.hpp>
#include <renderer/scene.hpp>
#include <string>

#include "../utils/ports.hpp"

namespace app {
namespace models {

enum Width : size_t;
enum Height : size_t;

/**
 * @brief Производит операции, связанные с 3D
 */
class Engine {
    /**
     * @brief Тип хранимой сцены
     */
    using Scene = renderer::Scene;

public:
    /**
     * @brief Тип ID камеры
     */
    using CameraId = renderer::Scene::CameraId;

    /**
     * @brief Тип ID объекта
     */
    using ObjectId = renderer::Scene::ObjectId;

    /**
     * @brief Тип изображения
     */
    using Image = renderer::Image;

    /**
     * @brief Создание 3D движка
     *
     * Создает 3D движок со сценой без объектов и одной камерой, которая становится выбранной.
     * Изначальные размеры выходного изображения 0 x 0 пикселей
     */
    Engine();

    /**
     * @brief Подписка на изменение текущей камеры
     *
     * Подписывает переданный порт на изменение текущей выбранной камеры
     *
     * @param[in] port Порт для подписания
     */
    void SubscribeSelectedCamera(ports::PortIn<CameraId>* port);

    /**
     * @brief Подписка на изменение списка доступных камер
     *
     * Подписывает переданный порт на изменение списка доступных камер
     *
     * @param[in] port Порт для подписания
     */
    void SubscribeAvailableCameras(ports::PortIn<std::vector<CameraId>>* port);

    /**
     * @brief Подписка на изменение текущего объекта
     *
     * Подписывает переданный порт на изменение текущего выбранного объекта. Если ни одного объекта
     * в сцене нет, то могут передаться произвольные значения
     *
     * @param[in] port Порт для подписания
     *
     * @todo Логика работы в случае отсутствия объектов кажется странной, стоит разобраться, как это
     * исправить
     */
    void SubscribeSelectedObject(ports::PortIn<ObjectId>* port);

    /**
     * @brief Подписка на изменение списка доступных объектов
     *
     * Подписывает переданный порт на изменение списка доступных объектов
     *
     * @param[in] port Порт для подписания
     */
    void SubscribeAvailableObjects(ports::PortIn<std::vector<ObjectId>>* port);

    /**
     * @brief Подписка на изменение изображения
     *
     * Подписывает переданный порт на изменение изображения с выбранной камеры
     *
     * @param[in] port Порт для подписания
     */
    void SubscribeImage(ports::PortIn<Image>* port);

    /**
     * @brief Подписка на изменение сцены
     *
     * Подписывает переданный порт на изменение сцены
     *
     * @param[in] port Порт для подписания
     */
    void SubscribeScene(ports::PortIn<Scene>* port);

    /**
     * @brief Изменение размеров изображения
     *
     * Устанавливает новые размеры выходного изображения
     *
     * @param[in] width Новая ширина
     * @param[in] height Новая высота
     */
    void Resize(const Width width, const Height height);

    /**
     * @brief Загрузка объекта из файла
     *
     * Загружает объект из obj файла по переданному пути и делает его выбранным. В случае ошибки
     * загрузки не делает ничего
     *
     * @param[in] path Путь
     */
    void LoadObjectFromFile(const std::string& path);

    /**
     * @brief Изменение выбора камеры
     *
     * Заменят текущую выбранную камеру на переданную. Требуется, чтобы новая камера присутствовала
     * в сцене
     *
     * @param[in] new_camera_id ID новой выбранной камеры
     */
    void SwitchCamera(const CameraId new_camera_id);

    /**
     * @brief Изменение выбора объекта
     *
     * Заменят текущий выбранный объект на переданный. Требуется, чтобы новый объект присутствовал
     * в сцене
     *
     * @param[in] new_object_id ID новой выбранной камеры
     */
    void SwitchObject(const ObjectId new_object_id);

    /**
     * @brief Установка новой позиции выбранной камеры
     *
     * Перемещает текущую выбранную камеру в заданную позицию. Не меняет направление взгляда камеры
     *
     * @param[in] new_position Новая позиция
     */
    void SetCameraPosition(const renderer::Vector& new_position);

    /**
     * @brief Установка новых углов выбранной камеры
     *
     * Меняет углы направления взгляда текущей выбранной камеры на заданные. Не меняет позицию
     * камеры
     *
     * @param[in] new_yaw Новый угол рыскания
     * @param[in] new_pitch Новый угол тангажа
     */
    void SetCameraAngles(const float new_yaw, const float new_pitch);

    /**
     * @brief Перемещение выбранной камеры
     *
     * Перемещает камеру на заданное расстояние вперед по направлению взгляда, вправо относительно
     * направления взгляда и вверх относительно оси Z сцены. Отрицательные значения перемещают
     * камеру назад/влево/вниз соответсвенно
     *
     * @param[in] forward_distance Дистанция сдвига вперед
     * @param[in] right_distance Дистанция сдвига вправо
     * @param[in] up_distance Дистанция сдвига вверх
     */
    void MoveCamera(const float forward_distance, const float right_distance,
                    const float up_distance);

    /**
     * @brief Поворот камеры
     *
     * Поворачивает камеру на заданный угол онтосительно вертикали и на заданный угол относительно
     * горизонтали. Положительные значения соответсвуют повороту против часовой стрелки/вверх,
     * отрицательные - по часовой стрелке/вниз
     */
    void RotateCamera(const float yaw_offset, const float pitch_offset);

private:
    /**
     * @todo Тут бы хорошо подошел дополнительный вид порта, который можно подписывать на несколько
     * других, с ограничением "нельзя передавать данные, только уведомления", либо отдельный класс,
     * который хранит внутри данные и зовет void(void) callback при их изменении. Пока нужно
     * подключить callback к одному PortIn и дергать Notify при изменении других данных
     */
    void Render();

    ports::PortIn<Scene> on_scene_change_;  // запускает внутренние процессы при изменении сцены
    ports::PortOut<Scene> scene_;

    ports::PortOut<CameraId> selected_camera_;                 // текущая камера
    ports::PortOut<std::vector<CameraId>> available_cameras_;  // все камеры

    ports::PortOut<ObjectId> selected_object_;                 // текущий объект
    ports::PortOut<std::vector<ObjectId>> available_objects_;  // все объекты

    ports::PortOut<Image> rendered_image_;

    renderer::Renderer renderer_;

    // параметры выходного изображения
    size_t width_ = 0;
    size_t height_ = 0;
};

}  // namespace models
}  // namespace app
