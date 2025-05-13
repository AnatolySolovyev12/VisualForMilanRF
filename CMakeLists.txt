cmake_minimum_required(VERSION 3.10)

project(VisualForMilanRF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui AxContainer Sql)


set(SOURCES 
"${CMAKE_SOURCE_DIR}/source/RangeTableValue.cpp"
"${CMAKE_SOURCE_DIR}/source/RangeTableValue.h"
"${CMAKE_SOURCE_DIR}/source/ui_RangeTableValue.h"

"${CMAKE_SOURCE_DIR}/source/VisualForMilanRF.cpp"
"${CMAKE_SOURCE_DIR}/source/VisualForMilanRF.h"
"${CMAKE_SOURCE_DIR}/source/ui_VisualForMilanRF.h"


"${CMAKE_SOURCE_DIR}/source/main.cpp"
"${CMAKE_SOURCE_DIR}/source/resource.h"

) # Добавьте сюда ваши файлы


qt6_wrap_ui(UI_HEADERS 
"${CMAKE_SOURCE_DIR}/source/VisualForMilanRF.ui"
"${CMAKE_SOURCE_DIR}/source/RangeTableValue.ui"
)

qt6_add_resources(RESOURCES "${CMAKE_SOURCE_DIR}/source/VisualForMilanRF.qrc")

qt6_wrap_cpp(MOC_SOURCES ${SOURCES})

add_executable(VisualForMilanRF_APP ${SOURCES} ${MOC_SOURCES} ${UI_HEADERS} ${RESOURCES})

target_link_libraries(VisualForMilanRF_APP PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui Qt::AxContainer Qt::Sql)