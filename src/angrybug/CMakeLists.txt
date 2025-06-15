add_library(angrybug angrybug.cpp)

target_include_directories(angrybug PUBLIC "${PROJECT_SOURCE_DIR}/src/includes")

target_link_libraries(angrybug
    PUBLIC SFML::Graphics
    bug
    )
