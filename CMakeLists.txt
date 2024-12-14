cmake_minimum_required(VERSION 3.16)
project(Overlord)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL2_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL2")
include_directories(${SDL2_DIR}/include)
link_directories(${SDL2_DIR}/lib)

set(SDL2_ttf_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL_TTF")
include_directories(${SDL2_ttf_DIR}/include)
link_directories(${SDL2_ttf_DIR}/lib)

set(freetype_DIR "${CMAKE_SOURCE_DIR}/vendor/Freetype")
include_directories(${freetype_DIR}/include)
link_directories(${freetype_DIR}/lib)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(PNG REQUIRED)
find_package(BZip2 REQUIRED)
find_package(ZLIB REQUIRED)

set(GAME_HEADER_FILES
    src/game/frame/Frame.h
    src/game/GameHandler.h
    src/game/player/Player.h
    src/game/target/Target.h
    src/window/Window.h
)

set(GAME_SOURCE_FILES
    src/game/frame/Frame.cpp
    src/game/GameHandler.cpp
    src/game/player/Player.cpp
    src/game/target/Target.cpp
    src/window/Window.cpp
)

set(AI_HEADER_FILES
    src/game/ai/Ai.h
    src/game/ai/Inputs.h
    src/game/ai/neuralNetwork/layer/Layer.h
    src/game/ai/neuralNetwork/NeuralNetwork.h
    src/game/ai/neuralNetwork/nodes/Node.h
)

set(AI_SOURCE_FILES
    src/game/ai/Ai.cpp
    src/game/ai/Inputs.cpp
    src/game/ai/neuralNetwork/layer/Layer.cpp
    src/game/ai/neuralNetwork/NeuralNetwork.cpp
    src/game/ai/neuralNetwork/nodes/Node.cpp
)

set(STATS_HEADER_FILES
    src/statsWindow/StatsWindow.h
    src/window/drawable/graph/Graph.h
)

set(STATS_SOURCE_FILES
    src/statsWindow/StatsWindow.cpp
    src/window/drawable/graph/Graph.cpp
)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  set(
    CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} -Werror -fsanitize=undefined -fsanitize=address"
  )
endif()

add_executable(Overlord 
    src/main.cpp
    ${GAME_HEADER_FILES}
    ${GAME_SOURCE_FILES}
)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  target_link_options(
    Overlord
    BEFORE PUBLIC -fsanitize=undefined PUBLIC -fsanitize=address
  )
endif()

target_include_directories(Overlord PRIVATE 
    ${SDL2_INCLUDE_DIR}
)

target_link_libraries(Overlord 
    ${PNG_LIBRARIES}
    ${BZIP2_LIBRARIES}
    ${ZLIB_LIBRARIES}
)

target_link_libraries(Overlord
    SDL2 
    dl 
    SDL2_ttf 
    freetype
    png
    z
    bz2
)

add_executable(RunOverlord 
    src/runAi.cpp
    ${GAME_HEADER_FILES}
    ${GAME_SOURCE_FILES}
    ${AI_HEADER_FILES}
    ${AI_SOURCE_FILES}

)

target_include_directories(RunOverlord PRIVATE 
    ${SDL2_INCLUDE_DIR}
)

target_link_libraries(RunOverlord
    SDL2 
    dl 
    SDL2_ttf 
    freetype
    png
    z
    bz2
)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  target_link_options(
    RunOverlord
    BEFORE PUBLIC -fsanitize=undefined PUBLIC -fsanitize=address
  )
endif()


# todo make these private
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

add_executable(TrainOverlord 
    src/trainAi.cpp
    ${GAME_HEADER_FILES}
    ${GAME_SOURCE_FILES}
    ${AI_HEADER_FILES}
    ${AI_SOURCE_FILES}
    ${STATS_HEADER_FILES}
    ${STATS_SOURCE_FILES}
)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  target_link_options(
    TrainOverlord
    BEFORE PUBLIC -fsanitize=undefined PUBLIC -fsanitize=address
  )
endif()

target_include_directories(TrainOverlord PRIVATE 
    ${SDL2_INCLUDE_DIR}
)

target_link_libraries(TrainOverlord 
    SDL2 
    dl 
    SDL2_ttf 
    freetype
    png
    z
    bz2
)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

