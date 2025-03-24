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

    connect(ui->ObjectUpdatePosition, &QPushButton::clicked, this,
            &EngineController::ChangeObjectPosition);
    connect(ui->ObjectUpdateAngles, &QPushButton::clicked, this,
            &EngineController::ChangeObjectAngles);
    connect(ui->ObjectUpdateScale, &QPushButton::clicked, this,
            &EngineController::ChangeObjectScale);

    connect(ui->CameraSelector, &QListWidget::currentItemChanged, this,
            &EngineController::ChangeCamera);
    connect(ui->ObjectSelector, &QListWidget::currentItemChanged, this,
            &EngineController::ChangeObject);

    connect(ui->SpawnCamera, &QPushButton::clicked, this, &EngineController::SpawnCamera);
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
    {
        assert(engine_ and "MoveCameraForward: engine не может быть nullptr");
        assert(ui_ and "MoveCameraForward: ui не может быть nullptr");
    }

    engine_->MoveCamera(ui_->TranslateStep->value(), 0, 0);
}

void EngineController::MoveCameraBackward(bool) {
    {
        assert(engine_ and "MoveCameraBackward: engine не может быть nullptr");
        assert(ui_ and "MoveCameraBackward: ui не может быть nullptr");
    }
    engine_->MoveCamera(-(ui_->TranslateStep->value()), 0, 0);
}

void EngineController::MoveCameraRight(bool) {
    {
        assert(engine_ and "MoveCameraRight: engine не может быть nullptr");
        assert(ui_ and "MoveCameraRight: ui не может быть nullptr");
    }
    engine_->MoveCamera(0, ui_->TranslateStep->value(), 0);
}

void EngineController::MoveCameraLeft(bool) {
    {
        assert(engine_ and "MoveCameraLeft: engine не может быть nullptr");
        assert(ui_ and "MoveCameraLeft: ui не может быть nullptr");
    }
    engine_->MoveCamera(0, -(ui_->TranslateStep->value()), 0);
}

void EngineController::MoveCameraUp(bool) {
    {
        assert(engine_ and "MoveCameraUp: engine не может быть nullptr");
        assert(ui_ and "MoveCameraUp: ui не может быть nullptr");
    }
    engine_->MoveCamera(0, 0, ui_->TranslateStep->value());
}

void EngineController::MoveCameraDown(bool) {
    {
        assert(engine_ and "MoveCameraDown: engine не может быть nullptr");
        assert(ui_ and "MoveCameraDown: ui не может быть nullptr");
    }
    engine_->MoveCamera(0, 0, -(ui_->TranslateStep->value()));
}

void EngineController::RotateCameraUp(bool) {
    {
        assert(engine_ and "RotateCameraUp: engine не может быть nullptr");
        assert(ui_ and "RotateCameraUp: ui не может быть nullptr");
    }
    engine_->RotateCamera(0, ui_->RotateStep->value());
}

void EngineController::RotateCameraDown(bool) {
    {
        assert(engine_ and "RotateCameraDown: engine не может быть nullptr");
        assert(ui_ and "RotateCameraDown: ui не может быть nullptr");
    }
    engine_->RotateCamera(0, -(ui_->RotateStep->value()));
}

void EngineController::RotateCameraRight(bool) {
    {
        assert(engine_ and "RotateCameraRight: engine не может быть nullptr");
        assert(ui_ and "RotateCameraRight: ui не может быть nullptr");
    }
    engine_->RotateCamera(-(ui_->RotateStep->value()), 0);
}

void EngineController::RotateCameraLeft(bool) {
    {
        assert(engine_ and "RotateCameraLeft: engine не может быть nullptr");
        assert(ui_ and "RotateCameraLeft: ui не может быть nullptr");
    }
    engine_->RotateCamera(ui_->RotateStep->value(), 0);
}

void EngineController::ChangeObjectPosition(bool) {
    {
        assert(engine_ and "ChangeObjectPosition: engine не может быть nullptr");
        assert(ui_ and "ChangeObjectPosition: ui не может быть nullptr");
    }
    float new_x = ui_->ObjectXSelector->value();
    float new_y = ui_->ObjectYSelector->value();
    float new_z = ui_->ObjectZSelector->value();
    engine_->SetObjectPosition(renderer::Vector{new_x, new_y, new_z});
}

void EngineController::ChangeObjectAngles(bool) {
    {
        assert(engine_ and "ChangeObjectAngles: engine не может быть nullptr");
        assert(ui_ and "ChangeObjectAngles: ui не может быть nullptr");
    }
    float new_x_angle = ui_->ObjectXAngleSelector->value();
    float new_y_angle = ui_->ObjectYAngleSelector->value();
    float new_z_angle = ui_->ObjectZAngleSelector->value();
    engine_->SetObjectAngles(new_x_angle, new_y_angle, new_z_angle);
}

void EngineController::ChangeObjectScale(bool) {
    {
        assert(engine_ and "ChangeObjectScale: engine не может быть nullptr");
        assert(ui_ and "ChangeObjectScale: ui не может быть nullptr");
    }
    float new_scale = ui_->ObjectScaleSelector->value();
    engine_->SetObjectScale(new_scale);
}

void EngineController::ChangeCamera(QListWidgetItem* current, QListWidgetItem*) {
    {
        assert(engine_ and "ChangeCamera: engine не может быть nullptr");
    }
    renderer::Scene::CameraId new_camera = current->text().toULong();
    engine_->SwitchCamera(new_camera);
}

void EngineController::ChangeObject(QListWidgetItem* current, QListWidgetItem*) {
    {
        assert(engine_ and "ChangeObject: engine не может быть nullptr");
    }
    renderer::Scene::ObjectId new_object = current->text().toULong();
    engine_->SwitchObject(new_object);
}

void EngineController::SpawnCamera(bool) {
    {
        assert(engine_ and "SpawnCamera: engine не может быть nullptr");
    }
    engine_->SpawnCamera();
}

}  // namespace app::controllers
