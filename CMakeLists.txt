cmake_minimum_required(VERSION 3.10)
project(ObjectTracking)

set(CMAKE_CXX_STANDARD 17)

# GStreamer
find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0>=1.0)

# Qt (optional if used)
find_package(Qt5 REQUIRED COMPONENTS Core)

# Add plugins subdirectories
add_subdirectory(plugins/YoloDetectorPlugin)
add_subdirectory(plugins/YahooTrackerPlugin)

# Include paths
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Factories
    ${CMAKE_CURRENT_SOURCE_DIR}/Strategies
    ${CMAKE_CURRENT_SOURCE_DIR}/plugins/YoloDetectorPlugin
    ${CMAKE_CURRENT_SOURCE_DIR}/plugins/YahooTrackerPlugin
    ${GSTREAMER_INCLUDE_DIRS}
)

# Main sources
add_executable(${PROJECT_NAME}
    main.cpp
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    ${GSTREAMER_LIBRARIES}
    Qt5::Core
    dl
)

# Post-build copy .so to binary folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/YoloDetectorPlugin/build/libYoloDetector.so
        ${CMAKE_CURRENT_SOURCE_DIR}/plugins/YahooTrackerPlugin/build/libYahooTracker.so
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
