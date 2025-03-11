/**
 * @file
 * @brief Главное окно приложения
 */

#pragma once

#include <QMainWindow>
#include <QScopedPointer>

#include "ui_main_window.h"

namespace Ui {  // NOLINT
class MainWindow;
}

namespace app {

/**
 * @brief Элементы GUI приложения
 */
namespace gui {
/**
 * @brief Класс, предоставляющий доступ к интерфейсу приложения
 *
 * Предоставляет доступ к элементам интерфейса для пользователей. Хранит и автоматически
 * инициализирует интерфейс
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

    /**
     * @brief Получение доступа к UI
     *
     * Возвращает указатель на интерфейс, через который можно получить доступ ко всем элементам
     *
     * @return Указатель на интерфейс
     */
    Ui::MainWindow* AccessUi();

private:
    QScopedPointer<Ui::MainWindow> ui_;
};
}  // namespace gui
}  // namespace app
