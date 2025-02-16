#include "app_gui.hpp"

namespace app {

AppGUI::AppGUI() : view_{main_window_.RenderRegion()} {
    main_window_.show();
}

}  // namespace app
