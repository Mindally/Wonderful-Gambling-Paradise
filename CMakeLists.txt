cmake_minimum_required (VERSION 3.14)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project ("Wonderful Gambling Paradise")

set(SFML_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/include/SFML")
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")


find_package(SFML 3.0 REQUIRED COMPONENTS Graphics Window System)

include(cmake/function.cmake)

add_subdirectory(src/core/fundamental\ classes/logic/card)
add_subdirectory(src/core/fundamental\ classes/logic/deck)
add_subdirectory(src/core/fundamental\ classes/render/cardRenderer)
add_subdirectory(src/core/fundamental\ classes/render/deckRenderer)
add_subdirectory(src/core/fundamental\ classes/TVector)
add_subdirectory(src/games/solitaire/klondike/cardField)
add_subdirectory(src/games/solitaire/klondike/klondike)
add_subdirectory(src/games/solitaire/klondike/cardFieldRenderer)
add_subdirectory(src/main)