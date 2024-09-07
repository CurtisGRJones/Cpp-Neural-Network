cmake_minimum_required(VERSION 3.16)
project(Overlord)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL2_INCLUDE_DIR "/usr/include/SDL2")
set(SDL2_LIBRARIES "/usr/lib/x86_64-linux-gnu/libSDL2.so")

find_package(SDL2 REQUIRED)

set(GAME_HEADER_FILES
    src/game/frame/Frame.h
    src/game/GameHandler.h
    src/game/player/Player.h
    src/game/target/Target.h
    src/game/window/Window.h
)

set(GAME_SOURCE_FILES
    src/game/frame/Frame.cpp
    src/game/GameHandler.cpp
    src/game/player/Player.cpp
    src/game/target/Target.cpp
    src/game/window/Window.cpp
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

target_include_directories(Overlord PRIVATE ${SDL2_INCLUDE_DIR})
target_link_libraries(Overlord ${SDL2_LIBRARIES})

add_executable(RunOverlord 
    src/runAi.cpp
    ${GAME_HEADER_FILES}
    ${GAME_SOURCE_FILES}
    ${AI_HEADER_FILES}
    ${AI_SOURCE_FILES}

)

target_include_directories(RunOverlord PRIVATE ${SDL2_INCLUDE_DIR})
target_link_libraries(RunOverlord ${SDL2_LIBRARIES})

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
)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  target_link_options(
    TrainOverlord
    BEFORE PUBLIC -fsanitize=undefined PUBLIC -fsanitize=address
  )
endif()

target_include_directories(TrainOverlord PRIVATE ${SDL2_INCLUDE_DIR})
target_link_libraries(TrainOverlord ${SDL2_LIBRARIES})

