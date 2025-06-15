add_library(smellmap smellmap.cpp)

target_include_directories(smellmap PUBLIC "${PROJECT_SOURCE_DIR}/src/includes")

target_link_libraries(smellmap
    PUBLIC SFML::Graphics
    bug
)
