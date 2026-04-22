cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Zbierz wszystkie pliki zrodlowe projektu
add_executable(main
    src/main.cpp
    src/core/AssetManager.cpp
    src/core/Camera.cpp
    src/core/Game.cpp
    src/core/MapBackground.cpp
    src/entities/Player.cpp
    src/entities/enemy/Enemy.cpp
    src/entities/enemy/GreenSlime.cpp
    src/weapons/Arrow.cpp
    src/ui/InGameInterface.cpp
)

target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Audio)

# Katalog src/ jako katalog include
target_include_directories(main PRIVATE src)

# Kopiowanie folderu assets – obok exe (build/bin/) i do build/ (na wypadek uruchomienia z build/)
add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:main>/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets
    COMMENT "Kopiowanie assets/..."
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)