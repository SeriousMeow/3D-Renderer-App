/**
 * @file
 * @brief Обновление списка объектов
 */
#pragma once

#include <QListWidget>

#include "../models/3D_engine.hpp"
#include "../utils/ports.hpp"

namespace app::gui {

/**
 * @brief Обновляет список объектов в интерфейсе
 */
class ObjectsList {
public:
    using ObjectId = models::Engine::ObjectId;

    /**
     * @brief Создание ObjectsList
     *
     * @param[in] objects_list Список с объектами
     */
    ObjectsList(QListWidget* objects_list);

    /**
     * @brief Получение указателя на порт списка объектов
     *
     * Возвращает указатель на входной порт для подключения списка объектов
     *
     * @return Указатель на порт списка объектов
     */
    ports::PortIn<std::vector<ObjectId>>* GetObjectsListPort();

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
     * Обновляет список объектов в интерфейсе
     */
    void UpdateObjectsList(const std::vector<ObjectId>& new_objects_list);

    /**
     * Обновляет выбранный объект в списке
     */
    void UpdateSelectedObject(const ObjectId new_object_id);

    QListWidget* objects_list_field_;
    ports::PortIn<std::vector<ObjectId>> objects_list_;
    ports::PortIn<ObjectId> selected_object_;
};

}  // namespace app::gui
