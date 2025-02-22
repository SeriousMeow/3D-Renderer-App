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

    /**
     * @brief Получение указателя на порт сцены
     *
     * Возвращает указатель на входной порт для подключения сцены
     *
     * @return Указатель на порт сцены
     */
    ports::PortIn<renderer::Scene>* GetScenePort();

private:
    /**
     * @brief Рендеринг сцены
     *
     * Рендерит переданную сцену с использованием сохраненной камеры
     *
     * @param[in] scene Сцена для рендеринга
     */
    void RenderScene(const renderer::Scene& scene);

    QLabel* render_region_;
    ports::PortIn<renderer::Scene> scene_port_;
    renderer::Scene::CameraId camera_id_ = 0;
    renderer::Renderer renderer_;
};

}  // namespace app
