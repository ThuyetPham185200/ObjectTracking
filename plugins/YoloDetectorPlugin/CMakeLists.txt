cmake_minimum_required(VERSION 3.10)
project(YoloDetectorPlugin)

set(CMAKE_CXX_STANDARD 17)

add_library(YoloDetector SHARED 
    YoloDetector.cpp 
    YoloDetectorPlugin.cpp
)

target_include_directories(YoloDetector PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)

# Link to any required libs (e.g., Qt5, OpenCV) if needed
