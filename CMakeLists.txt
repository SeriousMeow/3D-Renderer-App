cmake_minimum_required(VERSION 3.16)

include(cmake/prelude.cmake)

project(
  Renderer_App
  VERSION 0.0.1
  DESCRIPTION "Курсовой проект по созданию 3D рендерера на C++: приложение"
  HOMEPAGE_URL "https://example.com/"
  LANGUAGES CXX)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

include(cmake/external_libs.cmake)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# ---- Declare executable ----

qt_add_executable(Renderer_App_exe MANUAL_FINALIZATION)

add_executable(Renderer_App::exe ALIAS Renderer_App_exe)

set_property(TARGET Renderer_App_exe PROPERTY OUTPUT_NAME Renderer_App)

target_compile_features(Renderer_App_exe PRIVATE cxx_std_20)

target_include_directories(Renderer_App_exe
                           PRIVATE "${Renderer_SOURCE_DIR}/source/")
target_link_libraries(Renderer_App_exe PRIVATE Renderer::Renderer)
target_link_libraries(Renderer_App_exe PRIVATE Qt6::Widgets)

# ---- Add sources ----

add_subdirectory(source)

# ---- Qt finalize ----

qt_finalize_executable(Renderer_App_exe)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT Renderer_App_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
    AUTHOR_WARNING "Developer mode is intended for developers of Renderer_App")
endif()

include(cmake/dev-mode.cmake)
