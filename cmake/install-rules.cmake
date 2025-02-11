install(TARGETS Renderer_App_exe RUNTIME COMPONENT Renderer_App_Runtime)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
