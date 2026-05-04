// 5. `ModuleBoard`
//    - przechowuje moduły robota,
//    - jest właścicielem modułów dodanych przez `add`,
//    - usuwa moduły w destruktorze,
//    - pozwala dodać moduł,
//    - pozwala odczytać liczbę modułów,
//    - udostępnia moduły przez operator `[]`,
//    - posiada `tickAll()`,
//    - posiada operator `()`, który zwraca całkowity pobór prądu.

#pragma once

#include "RobotModule.h"
#include <vector>

class ModuleBoard{
public:
    ~ModuleBoard();

    void add(RobotModule* r);

    std::size_t size();

    const ModuleBoard* operator[](size_t i) const;
    ModuleBoard* operator[](size_t i);



private:
    std::vector<RobotModule*> modules;

};

