message("Generating the build files for the graphics library")

# Setup Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(GRAPHICS_SOURCES
  ${PROJECT_SOURCE_DIR}/src/graphics/src/MainWindow.cpp
  ${PROJECT_SOURCE_DIR}/src/graphics/src/HistoryTable.cpp
  ${PROJECT_SOURCE_DIR}/src/graphics/src/HistoryModel.cpp
  ${PROJECT_SOURCE_DIR}/src/graphics/src/HistoryTableItem.cpp
  ${PROJECT_SOURCE_DIR}/src/graphics/src/FailureBannerWidget.cpp

  ${PROJECT_SOURCE_DIR}/src/graphics/src/EventDetailWidget.cpp
  ${PROJECT_SOURCE_DIR}/src/graphics/src/FailureListItem.cpp
  ${PROJECT_SOURCE_DIR}/src/graphics/src/FailureListModel.cpp
  ${PROJECT_SOURCE_DIR}/src/graphics/src/FailureListWidget.cpp
  ${PROJECT_SOURCE_DIR}/src/graphics/src/FailureConfigureWidget.cpp
  ${PROJECT_SOURCE_DIR}/src/graphics/src/CircleStatusWidget.cpp
  ${PROJECT_SOURCE_DIR}/src/graphics/src/StatusBarWidget.cpp

  # Headers using MOC need to be added to the sources for AUTOMOC to treat them
  ${PROJECT_SOURCE_DIR}/src/graphics/include/MainWindow.h
  ${PROJECT_SOURCE_DIR}/src/graphics/include/HistoryTable.h
  ${PROJECT_SOURCE_DIR}/src/graphics/include/HistoryModel.h
  ${PROJECT_SOURCE_DIR}/src/graphics/include/HistoryTableItem.h

  ${PROJECT_SOURCE_DIR}/src/graphics/include/EventDetailWidget.h
  ${PROJECT_SOURCE_DIR}/src/graphics/include/FailureConfigureWidget.h
  ${PROJECT_SOURCE_DIR}/src/graphics/include/FailureListWidget.h
  ${PROJECT_SOURCE_DIR}/src/graphics/include/FailureBannerWidget.h
  ${PROJECT_SOURCE_DIR}/src/graphics/include/FailureListItem.h
  ${PROJECT_SOURCE_DIR}/src/graphics/include/FailureListModel.h
  ${PROJECT_SOURCE_DIR}/src/graphics/include/CircleStatusWidget.h
  ${PROJECT_SOURCE_DIR}/src/graphics/include/StatusBarWidget.h
)
set(GRAPHICS_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/src/graphics/include/ ${PROJECT_SOURCE_DIR}/src/middleware/include/)

add_library(jbox-graphics STATIC ${GRAPHICS_SOURCES})
target_include_directories(jbox-graphics PUBLIC ${GRAPHICS_INCLUDE_DIRS})
target_link_libraries(jbox-graphics PUBLIC Qt5::Widgets Qt5::SerialPort qtwaitingspinner jbox-failures jbox-results jbox-ui jbox-com)
