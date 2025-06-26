cmake_minimum_required(VERSION 3.31)
project(manager)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/external/json)
include_directories(include/Character)
include_directories(include/GameManager)
include_directories(include/Item)
include_directories(include/Monster)

add_executable(manager
        include/Character/Character.h
        include/GameManager/BattleSystem.h
        include/GameManager/GameManager.h
        include/Item/AttackItem.h
        include/Item/Bible.h
        include/Item/Brush.h
        include/Item/DropEntry.h
        include/Item/HealingItem.h
        include/Item/Item.h
        include/Item/ItemFactory.h
        include/Monster/BossMonster.h
        include/Monster/MonsterBase.h
        include/Monster/MonsterDefinition.h
        include/Monster/MonsterLoader.h
        include/UObjectBase.h
        src/Character/Character.cpp
        src/GameManager/BattleSystem.cpp
        src/GameManager/GameManager.cpp
        src/Item/AttackItem.cpp
        src/Item/HealingItem.cpp
        src/Item/Item.cpp
        src/Monster/BossMonster.cpp
        src/Monster/MonsterBase.cpp
        src/Monster/MonsterLoader.cpp
        src/main.cpp
        src/UObjectBase.cpp
        include/Util/Util.h
        src/Util/Util.cpp
        include/Save/SaveManager.h
        src/Save/SaveManager.cpp)
