add_library(game game.cpp)

target_include_directories(game PUBLIC "${PROJECT_SOURCE_DIR}/src/includes")

target_link_libraries(game 
    PUBLIC SFML::Graphics
    bug
)