// 6. `StartupSequence`
//    - przechowuje wskaźniki do wybranych modułów,
//    - nie jest właścicielem modułów,
//    - nie usuwa żadnych obiektów,
//    - pozwala uruchomić, zatrzymać i zresetować wszystkie moduły,
//    - pozwala odczytać liczbę modułów,
//    - udostępnia moduły przez operator `[]`.

#pragma once

#include <vector>
#include "RobotModule.h"

class StartupSequence{
public:
    StartupSequence(std::vector<RobotModule*> v);

    void startAll() const;

    void stopAll() const;

    std::size_t size() const;

    const RobotModule* operator[](std::size_t i) const;

    void resetAll() const;


private:
    std::vector<RobotModule*> sequence;
};