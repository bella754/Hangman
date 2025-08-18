cmake_minimum_required(VERSION 3.16)
project(hangman LANGUAGES CXX)

# C++-Standard & Warnungen
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Warnings (GCC/Clang)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Alle .cpp aus src/
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Executable
add_executable(hangman ${SRC_FILES})

# Public Headers in include/
target_include_directories(hangman PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)

# Optional: Definiere einen Makro-Pfad für Daten (falls du ihn im Code nutzen willst)
# Dann könntest du z. B. std::ifstream file(std::string(DATA_DIR) + "/words.txt");
#target_compile_definitions(hangman PRIVATE
#  DATA_DIR="${CMAKE_CURRENT_BINARY_DIR}/data"
#)

# Datenordner ins Build-Verzeichnis kopieren (bei Konfiguration & Re-Config)
add_custom_target(copy_data ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          "${CMAKE_SOURCE_DIR}/data"
          "${CMAKE_CURRENT_BINARY_DIR}/data"
  BYPRODUCTS "${CMAKE_CURRENT_BINARY_DIR}/data"
  COMMENT "Copying data/ to build directory"
)
add_dependencies(hangman copy_data)
