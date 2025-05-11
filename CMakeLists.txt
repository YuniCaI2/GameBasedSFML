cmake_minimum_required(VERSION 3.10)
project(sfmlTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "${CMAKE_SOURCE_DIR}/ProgramCode/SFML/SFML-2.6.2/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Add executable with source files
# 搜索主目录中的文件
file(GLOB MAIN_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/ProgramCode/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ProgramCode/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ProgramCode/*.hpp"
)

# 搜索Component目录中的文件
file(GLOB COMPONENT_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/ProgramCode/Component/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ProgramCode/Component/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ProgramCode/Component/*.hpp"
)

# 搜索GameObjectType目录中的文件
file(GLOB GAMEOBJECT_TYPE_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/ProgramCode/GameObjectType/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/ProgramCode/GameObjectType/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/ProgramCode/GameObjectType/*.hpp"
)

# 合并所有源文件
set(PROJECT_SOURCES ${MAIN_SOURCES} ${COMPONENT_SOURCES} ${GAMEOBJECT_TYPE_SOURCES}
        ProgramCode/EnemyAI.cpp
        ProgramCode/EnemyAI.h
        ProgramCode/Component/EnemyAttackComponent.cpp
)

# 添加可执行文件
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# Link SFML libraries to the target
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
)

# Copy SFML DLLs to the executable directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/ProgramCode/SFML/SFML-2.6.2/bin"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
# 最后一个是生成器表达式，代表着生成可执行文件的目录