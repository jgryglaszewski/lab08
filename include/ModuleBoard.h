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

    const RobotModule* operator[](size_t i) const;
    RobotModule* operator[](size_t i);

    double operator()() const;

    void tickAll();



private:
    std::vector<RobotModule*> modules;

};

