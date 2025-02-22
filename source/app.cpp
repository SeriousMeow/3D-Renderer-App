#include "app.hpp"

namespace app {

App::App() : AppKernel{}, AppGUI{} {
    scene_.SubscribeScenePort(view_.GetScenePort());
}

}  // namespace app
