#cmake_minimum_required(VERSION 3.31)
#project(BaldMonster)
#
#set(CMAKE_CXX_STANDARD 17)
#
#include_directories(include)
#
#file(GLOB SOURCES src/*.cpp)
#add_executable(MyGameProject ${SOURCES}
#        src/main.cpp
#        include/DropEntry.h
#        include/MonsterBase.h
#        include/MonsterDefinition.h
#        include/MonsterLoader.h
#        src/MonsterBase.cpp
#        src/MonsterLoader.cpp
#        src/BossMonster.cpp
#        include/BossMonster.h
#)
#
##add_executable(BaldMonster
##        .idea/shelf/Uncommitted_changes_before_Checkout_at_2025-06-24_오후_2_54_[Changes]/shelved.patch
##        .idea/shelf/Uncommitted_changes_before_Checkout_at_2025-06-24_오후_2_54_[Changes]1/shelved.patch
##        .idea/shelf/Uncommitted_changes_before_Checkout_at_2025-06-24__2_54__Changes_.xml
##        .idea/.gitignore
##        .idea/BaldMonster.iml
##        .idea/editor.xml
##        .idea/indexLayout.xml
##        .idea/material_theme_project_new.xml
##        .idea/modules.xml
##        .idea/vcs.xml
##        .idea/workspace.xml
##        .gitignore
##        README.md)

cmake_minimum_required(VERSION 3.31)
project(BaldMonster)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")
add_executable(BaldMonster ${SOURCES})
