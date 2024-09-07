cmake_minimum_required(VERSION 3.16)
project(Overlord)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL2_INCLUDE_DIR "/usr/include/SDL2")
set(SDL2_LIBRARIES "/usr/lib/x86_64-linux-gnu/libSDL2.so")

find_package(SDL2 REQUIRED)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  set(
    CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} -Werror -fsanitize=undefined -fsanitize=address"
  )
endif()

add_executable(Overlord 
    src/main.cpp
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
SET(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
SET(CMAKE_HAVE_THREADS_LIBRARY 1)
SET(CMAKE_USE_WIN32_THREADS_INIT 0)
SET(CMAKE_USE_PTHREADS_INIT 1)
SET(THREADS_PREFER_PTHREAD_FLAG ON)

add_executable(TrainOverlord 
    src/trainAi.cpp
)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  target_link_options(
    TrainOverlord
    BEFORE PUBLIC -fsanitize=undefined PUBLIC -fsanitize=address
  )
endif()

target_include_directories(TrainOverlord PRIVATE ${SDL2_INCLUDE_DIR})
target_link_libraries(TrainOverlord ${SDL2_LIBRARIES})

