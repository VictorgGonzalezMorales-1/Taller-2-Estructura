cmake_minimum_required(VERSION 3.28)
project(Taller-2-Estructura)

set(CMAKE_CXX_STANDARD 20)

add_executable(Taller-2-Estructura
        main.cpp
        estructuras/Node.h
        estructuras/List.h
        estructuras/Queue.h
        estructuras/Stack.h
        dominio/Paciente.cpp
        dominio/Paciente.h
        logica/Sistema.cpp
        logica/Sistema.h)
