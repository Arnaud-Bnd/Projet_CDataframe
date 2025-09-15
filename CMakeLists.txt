cmake_minimum_required(VERSION 3.26)
project(Projet_CDataframe C CXX)

# Standards de langages
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

# S'assurer que les standards sont requis
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Extensions des compilateurs (optionnel, peut être désactivé)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

# Exécutable principal
add_executable(Projet_CDataframe 
    main.c
    column.c
    column.h
    cdataframe.h
    cdataframe.c
    features.h
    features.c
)

# Si tu veux forcer la compilation en C++ même pour les fichiers .c
# set_source_files_properties(main.c column.c cdataframe.c features.c 
#                              PROPERTIES LANGUAGE CXX)

# Options de compilation recommandées
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_options(Projet_CDataframe PRIVATE -Wall -Wextra -Werror)
endif()

# Définir des macros pour la compatibilité C/C++
target_compile_definitions(Projet_CDataframe PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:__cplusplus>
)

