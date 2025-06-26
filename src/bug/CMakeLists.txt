add_library(bug bug.cpp)

target_include_directories(bug PUBLIC "${PROJECT_SOURCE_DIR}/src/includes")

target_link_libraries(bug
    PUBLIC SFML::Graphics
    food
    )
