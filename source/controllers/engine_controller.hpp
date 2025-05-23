/**
 * @file
 * @brief Управление движком через интерфейс
 */

#pragma once

#include <QObject>

#include "../interface/ui_main_window.h"
#include "../models/3D_engine.hpp"
#include "qlistwidget.h"

namespace app {
/**
 * @brief Контроллеры приложения
 */
namespace controllers {
/**
 * @brief Управляет движком через интерфейс
 */
class EngineController : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Создание контроллера
     *
     * Создает контроллер, управляющий переданным движком через переданный интерфейс
     *
     * @param[in] engine Движок
     * @param[in] ui Интерфейс
     */
    EngineController(models::Engine* engine, Ui::MainWindow* ui);

private slots:
    /**
     * Срабатывает при нажатии кнопки "Загрузить файл"
     */
    void LoadFile(bool);

    /**
     * Срабатывает при изменении координат камеры в интерфейсе
     */
    void ChangeCameraPosition(double);

    /**
     * Срабатывает при изменении углов камеры в интерфейсе
     */
    void ChangeCameraAngles(double);

    /**
     * Срабатывает при нажатии кнопки "Вперед"
     */
    void MoveCameraForward(bool);

    /**
     * Срабатывает при нажатии кнопки "Назад"
     */
    void MoveCameraBackward(bool);

    /**
     * Срабатывает при нажатии кнопки "Вправо"
     */
    void MoveCameraRight(bool);

    /**
     * Срабатывает при нажатии кнопки "Влево"
     */
    void MoveCameraLeft(bool);

    /**
     * Срабатывает при нажатии кнопки "Вверх"
     */
    void MoveCameraUp(bool);

    /**
     * Срабатывает при нажатии кнопки "Вниз"
     */
    void MoveCameraDown(bool);

    /**
     * Срабатывает при нажатии кнопки "Наклон вверх"
     */
    void RotateCameraUp(bool);

    /**
     * Срабатывает при нажатии кнопки "Наклон вниз"
     */
    void RotateCameraDown(bool);

    /**
     * Срабатывает при нажатии кнопки "Поворот вправо"
     */
    void RotateCameraRight(bool);

    /**
     * Срабатывает при нажатии кнопки "Поворот влево"
     */
    void RotateCameraLeft(bool);

    /**
     * Срабатывает при изменении координат объекта в интерфейсе
     */
    void ChangeObjectPosition(double);

    /**
     * Срабатывает при изменении углов объекта в интерфейсе
     */
    void ChangeObjectAngles(double);

    /**
     * Срабатывает при изменении масштаба объекта в интерфейсе
     */
    void ChangeObjectScale(double);

    /**
     * Срабатывает при смене камеры в интерфейсе
     */
    void ChangeCamera(QListWidgetItem* current, QListWidgetItem*);

    /**
     * Срабатывает при смене объекта в интерфейсе
     */
    void ChangeObject(QListWidgetItem* current, QListWidgetItem*);

    /**
     * Срабатывает при нажатии кнопки "Добавить камеру"
     */
    void SpawnCamera(bool);

private:
    models::Engine* engine_;
    Ui::MainWindow* ui_;
};
}  // namespace controllers

}  // namespace app
