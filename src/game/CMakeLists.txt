# Coursework game
add_library(game
  game.cpp
)
target_link_libraries(game
  game-engine
)
target_include_directories(game INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Game Engine
add_library(game-engine
  game-engine.cpp
)
target_link_libraries(game-engine
  game-player
  game-room
  game-enemies
  game-inventory
  game-items
 )

# Room
add_library(game-room
  room.cpp
)
target_link_libraries(game-room
  game-generics
  game-enemies
)

# Items
add_library(game-items
  items.cpp
)
target_link_libraries(game-items
  game-generics
)

# Enemies
add_library(game-enemies
  enemies.cpp
)
target_link_libraries(game-enemies
  game-generics
)

# Player
add_library(game-player
  player.cpp
)
target_link_libraries(game-player
  game-inventory
  game-generics
)

# Inventory
add_library(game-inventory
  inventory.cpp
)
target_link_libraries(game-inventory
  game-generics
)

# Generics
add_library(game-generics
  generics.cpp
)
