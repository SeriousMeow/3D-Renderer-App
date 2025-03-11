#include "engine_controller.hpp"

#include <QFileDialog>

namespace app::controllers {

EngineController::EngineController(models::Engine* engine, Ui::MainWindow* ui)
    : engine_{engine}, ui_{ui} {
    {
        assert(engine and "EngineController: engine не может быть nullptr");
        assert(ui and "EngineController: ui не может быть nullptr");
    }
    ui->RenderRegion->setFixedSize(800, 600);
    QSize render_region_size = ui->RenderRegion->size();
    engine->Resize(models::Width{static_cast<size_t>(render_region_size.width())},
                   models::Height{static_cast<size_t>(render_region_size.height())});

    connect(ui->LoadFileButton, &QPushButton::clicked, this, &EngineController::LoadFile);

    connect(ui->CameraUpdatePosition, &QPushButton::clicked, this,
            &EngineController::ChangeCameraPosition);
    connect(ui->CameraUpdateAngles, &QPushButton::clicked, this,
            &EngineController::ChangeCameraAngles);

    connect(ui->CameraMoveForward, &QPushButton::clicked, this,
            &EngineController::MoveCameraForward);
    connect(ui->CameraMoveBackward, &QPushButton::clicked, this,
            &EngineController::MoveCameraBackward);
    connect(ui->CameraMoveRight, &QPushButton::clicked, this, &EngineController::MoveCameraRight);
    connect(ui->CameraMoveLeft, &QPushButton::clicked, this, &EngineController::MoveCameraLeft);
    connect(ui->CameraMoveUp, &QPushButton::clicked, this, &EngineController::MoveCameraUp);
    connect(ui->CameraMoveDown, &QPushButton::clicked, this, &EngineController::MoveCameraDown);

    connect(ui->CameraRotateUp, &QPushButton::clicked, this, &EngineController::RotateCameraUp);
    connect(ui->CameraRotateDown, &QPushButton::clicked, this, &EngineController::RotateCameraDown);
    connect(ui->CameraRotateRight, &QPushButton::clicked, this,
            &EngineController::RotateCameraRight);
    connect(ui->CameraRotateLeft, &QPushButton::clicked, this, &EngineController::RotateCameraLeft);
}

void EngineController::LoadFile(bool) {
    {
        assert(engine_ and "LoadFile: engine не может быть nullptr");
        assert(ui_ and "LoadFile: ui не может быть nullptr");
    }
    QString filename =
        QFileDialog::getOpenFileName(ui_->centralwidget, "Открыть файл", "", "OBJ Файлы(*obj)");
    if (filename.isEmpty()) {
        return;
    }
    engine_->LoadObjectFromFile(filename.toStdString());
}

void EngineController::ChangeCameraPosition(bool) {
    {
        assert(engine_ and "ChangeCameraPosition: engine не может быть nullptr");
        assert(ui_ and "ChangeCameraPosition: ui не может быть nullptr");
    }
    float new_x = ui_->CameraXSelector->value();
    float new_y = ui_->CameraYSelector->value();
    float new_z = ui_->CameraZSelector->value();
    engine_->SetCameraPosition(renderer::Vector{new_x, new_y, new_z});
}

void EngineController::ChangeCameraAngles(bool) {
    {
        assert(engine_ and "ChangeCameraAngles: engine не может быть nullptr");
        assert(ui_ and "ChangeCameraAngles: ui не может быть nullptr");
    }
    float new_yaw = ui_->CameraYawSelector->value();
    float new_pitch = ui_->CameraPitchSelector->value();
    engine_->SetCameraAngles(new_yaw, new_pitch);
}

void EngineController::MoveCameraForward(bool) {
    engine_->MoveCamera(ui_->TranslateStep->value(), 0, 0);
}

void EngineController::MoveCameraBackward(bool) {
    engine_->MoveCamera(-(ui_->TranslateStep->value()), 0, 0);
}

void EngineController::MoveCameraRight(bool) {
    engine_->MoveCamera(0, ui_->TranslateStep->value(), 0);
}

void EngineController::MoveCameraLeft(bool) {
    engine_->MoveCamera(0, -(ui_->TranslateStep->value()), 0);
}

void EngineController::MoveCameraUp(bool) {
    engine_->MoveCamera(0, 0, ui_->TranslateStep->value());
}

void EngineController::MoveCameraDown(bool) {
    engine_->MoveCamera(0, 0, -(ui_->TranslateStep->value()));
}

void EngineController::RotateCameraUp(bool) {
    engine_->RotateCamera(0, ui_->RotateStep->value());
}

void EngineController::RotateCameraDown(bool) {
    engine_->RotateCamera(0, -(ui_->RotateStep->value()));
}

void EngineController::RotateCameraRight(bool) {
    engine_->RotateCamera(-(ui_->RotateStep->value()), 0);
}

void EngineController::RotateCameraLeft(bool) {
    engine_->RotateCamera(ui_->RotateStep->value(), 0);
}

}  // namespace app::controllers
