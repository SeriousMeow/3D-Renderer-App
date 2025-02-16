/**
 * @file
 * @brief Взаимодействие с областью отрисовки рендерера
 */

#pragma once

#include <QLabel>
#include <renderer/image.hpp>

namespace app {

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
     * @brief Отрисовка изображения
     *
     * Требуется, чтобы размеры изображения совпадали с размером области отрисовки
     *
     * @param[in] image Изображение
     */
    void Draw(const renderer::Image& image);

private:
    QLabel* render_region_;
};

}  // namespace app
