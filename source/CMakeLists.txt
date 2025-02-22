target_sources(Renderer_App_exe PRIVATE main.cpp except.cpp app.cpp app_gui.cpp
                                        app_kernel.cpp)

add_subdirectory(interface)
add_subdirectory(models)
