/**
 * @file
 * @brief Взаимодействие с областью отрисовки рендерера
 */

#pragma once

#include <QLabel>
#include <renderer/image.hpp>
#include <renderer/renderer.hpp>
#include <renderer/scene.hpp>

#include "../utils/ports.hpp"

namespace app {

namespace gui {
/**
 * @brief Класс взаимодействия с областью отрисовки
 */
class View {
public:
    /**
     * @brief Создание View
     *
     * @param[in] render_region QLabel, на который будет отрисовываться изображение
     */
    explicit View(QLabel* render_region);

    /**
     * @brief Получение указателя на порт сцены
     *
     * Возвращает указатель на входной порт для подключения сцены
     *
     * @return Указатель на порт сцены
     */
    ports::PortIn<renderer::Image>* GetImagePort();

private:
    /**
     * @brief Отрисовка изображения
     *
     * Требуется, чтобы размеры изображения совпадали с размером области отрисовки
     *
     * @param[in] image Изображение
     */
    void Draw(const renderer::Image& image);
    QLabel* render_region_;
    ports::PortIn<renderer::Image> image_port_;
};
}  // namespace gui
}  // namespace app
