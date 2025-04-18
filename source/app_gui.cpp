#include "app_gui.hpp"

namespace app {

AppGUI::AppGUI(models::Engine* engine)
    : image_region_{main_window_.AccessUi()->RenderRegion},
      camera_info_{
          main_window_.AccessUi()->CameraXSelector, main_window_.AccessUi()->CameraYSelector,
          main_window_.AccessUi()->CameraZSelector, main_window_.AccessUi()->CameraYawSelector,
          main_window_.AccessUi()->CameraPitchSelector},
      object_info_{
          main_window_.AccessUi()->ObjectXSelector,
          main_window_.AccessUi()->ObjectYSelector,
          main_window_.AccessUi()->ObjectZSelector,
          main_window_.AccessUi()->ObjectXAngleSelector,
          main_window_.AccessUi()->ObjectYAngleSelector,
          main_window_.AccessUi()->ObjectZAngleSelector,
          main_window_.AccessUi()->ObjectScaleSelector,
      },
      objects_list_{main_window_.AccessUi()->ObjectSelector},
      cameras_list_{main_window_.AccessUi()->CameraSelector},
      engine_controller_{engine, main_window_.AccessUi()} {
}

}  // namespace app
