cmake_minimum_required (VERSION 3.14)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project ("Wonderful Gambling Paradise")

set(SFML_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/include/SFML")
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")


find_package(SFML 3.0 REQUIRED COMPONENTS Graphics Window System)

include(cmake/function.cmake)

# Базовые классы логики карты и колоды
add_subdirectory(src/core/model/card)
add_subdirectory(src/core/model/deck)

# Базовые классы отображения карты и колоды в SFML
add_subdirectory(src/core/view/card_renderer)
add_subdirectory(src/core/view/deck_renderer)

# Сторонние классы
add_subdirectory(src/core/TVector)

# Классы Пасьянса "Косынка"
add_subdirectory(src/games/solitaire/card_position)
add_subdirectory(src/games/solitaire/klondike/field)
add_subdirectory(src/games/solitaire/klondike/field_renderer)
add_subdirectory(src/games/solitaire/klondike/game)

# Классы игры "Scoundrel"
add_subdirectory(src/games/scoundrel/card_position)
add_subdirectory(src/games/scoundrel/field)
add_subdirectory(src/games/scoundrel/field_renderer)
add_subdirectory(src/games/scoundrel/game)

# Main игры
add_subdirectory(src/main)