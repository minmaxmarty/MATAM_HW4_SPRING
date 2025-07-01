cmake_minimum_required(VERSION 3.31)
project(HW4_2425B)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(Events)
include_directories(Players)

add_executable(HW4_2425B
        Events/Event.h
        main.cpp
        MatamStory.cpp
        MatamStory.h
        Utilities.cpp
        Utilities.h
        Players/Player.cpp
        Players/Player.h
        Players/Job.cpp
        Players/Job.h
        Players/Character.cpp
        Players/Character.h
        Events/Monster.cpp
        Events/Monster.h
        Factory.cpp
        Factory.h
        MyExceptions.h
        Events/Event.cpp
)
