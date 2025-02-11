cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    Renderer_App
    VERSION 0.0.1
    DESCRIPTION "Курсовой проект по созданию 3D рендерера на C++: приложение"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)


include(cmake/external_libs.cmake)

# ---- Declare library ----

add_library(
    Renderer_App_lib OBJECT
)

target_include_directories(
    Renderer_App_lib ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(Renderer_App_lib PUBLIC cxx_std_20)

target_include_directories(Renderer_App_lib INTERFACE "${Renderer_SOURCE_DIR}/source/")
target_link_libraries(Renderer_App_lib PRIVATE Renderer::Renderer)

target_link_libraries(Renderer_App_lib PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)

# ---- Declare executable ----

add_executable(Renderer_App_exe)
add_executable(Renderer_App::exe ALIAS Renderer_App_exe)

set_property(TARGET Renderer_App_exe PROPERTY OUTPUT_NAME Renderer_App)

target_compile_features(Renderer_App_exe PRIVATE cxx_std_20)

target_link_libraries(Renderer_App_exe PRIVATE Renderer_App_lib)

# ---- Add sources ----

add_subdirectory(source)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT Renderer_App_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of Renderer_App"
  )
endif()

include(cmake/dev-mode.cmake)
