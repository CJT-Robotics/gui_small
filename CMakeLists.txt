cmake_minimum_required(VERSION 3.8)
project(gui_small)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
set(BACKEND_DIR ${CMAKE_CURRENT_SOURCE_DIR}/backends)


include_directories(
  ${IMGUI_DIR}
  ${BACKEND_DIR}
)

add_library(imgui SHARED
backends/imgui_impl_opengl3.cpp 
backends/imgui_impl_glfw.cpp
imgui/imgui.cpp
imgui/imgui_demo.cpp
imgui/imgui_draw.cpp
imgui/imgui_widgets.cpp
imgui/imgui_tables.cpp
)

add_executable(gui_small src/main.cpp src/DataRepository.cpp  
src/synchronization.cpp src/window.cpp src/transferNode.cpp src/controller_stationary.cpp)

target_link_libraries(gui_small  imgui -lglfw -lOpenGL)


install(TARGETS
  gui_small
  DESTINATION lib/${PROJECT_NAME})


ament_target_dependencies(gui_small rclcpp std_msgs)



if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(${PROJECT_NAME}_tutorial_test test/tutorial_test.cpp)
  target_include_directories(${PROJECT_NAME}_tutorial_test PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    

  )
  ament_target_dependencies(${PROJECT_NAME}_tutorial_test
    std_msgs 
  )
  
  target_link_libraries(${PROJECT_NAME}_tutorial_test)
endif()



  ament_package()