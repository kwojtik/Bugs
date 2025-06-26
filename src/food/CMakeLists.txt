add_library(food food.cpp)

target_include_directories(food PUBLIC "${PROJECT_SOURCE_DIR}/src/includes")

target_link_libraries(food
    PUBLIC SFML::Graphics
    )
