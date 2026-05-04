// Proszę dopisać brakujący kod oraz dodać potrzebne pliki tak,
// aby program kompilował się, wykonywał poprawnie, a wynik działania był
// identyczny jak przedstawiony na końcu pliku.
//
// Nie wolno modyfikować pliku `Main.cpp` 
//
// Temat:
// Symulacja płytki elektronicznej z modułami robota.
//
// Mały robot składa się z kilku modułów elektronicznych.
// Każdy moduł ma identyfikator i nazwę.
// Różne moduły działają inaczej:
// - sensor zbiera próbki,
// - silnik nagrzewa się podczas pracy,
// - moduł radiowy wysyła pakiety.
//
// Wszystkie moduły dziedziczą po jednej abstrakcyjnej klasie bazowej `RobotModule`.
// Dzięki temu płytka może przechowywać różne moduły w jednym wektorze wskaźników
// do klasy bazowej.
//
// Należy zaimplementować:
//
// 1. `RobotModule`
//    - abstrakcyjna klasa bazowa,
//    - przechowuje identyfikator, nazwę i informację, czy moduł jest aktywny,
//    - po utworzeniu moduł jest nieaktywny,
//    - udostępnia podstawowe informacje o module,
//    - pozwala uruchomić i zatrzymać moduł,
//    - posiada metodę `reset()`, która w klasie bazowej zatrzymuje moduł,
//    - definiuje wspólny interfejs dla modułów:
//         * typ modułu,
//         * pobór prądu,
//         * pojedynczy krok symulacji,
//         * diagnostykę tekstową,
//    - posiada operator `()`, który zwraca pobór prądu,
//    - posiada metodę `summary()`, która zwraca tekst:
//         "<type> <name> [id=<id>, current=<current> mA] -> <diagnostic>"
//
// 2. `SensorModule : public RobotModule`
//    - reprezentuje sensor,
//    - ma czułość i liczbę zebranych próbek,
//    - po utworzeniu liczba próbek wynosi 0,
//    - typ: `"SensorModule"`,
//    - gdy moduł jest nieaktywny, pobiera 1 mA,
//    - gdy moduł jest aktywny, pobiera `5 + sensitivity` mA,
//    - `tick()` zwiększa liczbę próbek o `sensitivity`, ale tylko gdy moduł jest aktywny,
//    - `reset()` zatrzymuje moduł i zeruje liczbę próbek,
//    - diagnostyka:
//         * `"SLEEP sensitivity=<sensitivity> samples=<samples>"`
//         * `"ACTIVE sensitivity=<sensitivity> samples=<samples>"`
//
// 3. `MotorModule : public RobotModule`
//    - reprezentuje moduł silnika,
//    - ma obciążenie i umowną temperaturę,
//    - po utworzeniu temperatura wynosi 0,
//    - typ: `"MotorModule"`,
//    - gdy moduł jest nieaktywny, pobiera 0 mA,
//    - gdy moduł jest aktywny, pobiera `load * 120 + heat * 10` mA,
//    - `tick()` zwiększa temperaturę o 2, ale tylko gdy moduł jest aktywny,
//    - `reset()` zatrzymuje moduł i zeruje temperaturę,
//    - diagnostyka:
//         * `"STOPPED load=<load> heat=<heat>"`
//         * `"ACTIVE load=<load> heat=<heat>"`
//
// 4. `RadioModule : public RobotModule`
//    - reprezentuje moduł radiowy,
//    - ma kanał i liczbę wysłanych pakietów,
//    - po utworzeniu liczba pakietów wynosi 0,
//    - typ: `"RadioModule"`,
//    - gdy moduł jest nieaktywny, pobiera 1 mA,
//    - gdy moduł jest aktywny, pobiera `30 + packets` mA,
//    - `tick()` zwiększa liczbę pakietów o numer kanału, ale tylko gdy moduł jest aktywny,
//    - `reset()` zatrzymuje moduł i zeruje liczbę pakietów,
//    - diagnostyka:
//         * `"OFF channel=<channel> packets=<packets>"`
//         * `"ACTIVE channel=<channel> packets=<packets>"`
//
// 5. `ModuleBoard`
//    - przechowuje moduły robota,
//    - jest właścicielem modułów dodanych przez `add`,
//    - usuwa moduły w destruktorze,
//    - pozwala dodać moduł,
//    - pozwala odczytać liczbę modułów,
//    - udostępnia moduły przez operator `[]`,
//    - posiada `tickAll()`,
//    - posiada operator `()`, który zwraca całkowity pobór prądu.
//
// 6. `StartupSequence`
//    - przechowuje wskaźniki do wybranych modułów,
//    - nie jest właścicielem modułów,
//    - nie usuwa żadnych obiektów,
//    - pozwala uruchomić, zatrzymać i zresetować wszystkie moduły,
//    - pozwala odczytać liczbę modułów,
//    - udostępnia moduły przez operator `[]`.
//

#include <iostream>
#include <string>
#include <vector>

#include "RobotModule.h"
#include "ModuleBoard.h"
#include "StartupSequence.h"

int main() {
    ModuleBoard board;

    SensorModule* sensor = new SensorModule("SEN-1", "Distance sensor", 3);
    MotorModule* motor = new MotorModule("MOT-1", "Left motor", 2);
    RadioModule* radio = new RadioModule("RAD-1", "Telemetry radio", 7);

    board.add(sensor);
    board.add(motor);
    board.add(radio);

    StartupSequence sequence(std::vector<RobotModule*>{sensor, motor, radio});

    std::cout << "Initial board state:\n";
    for (std::size_t i = 0; i < board.size(); ++i) {
        std::cout << board[i]->summary() << "\n";
    }

    std::cout << "Initial current draw: " << board() << " mA\n";

    sequence.startAll();

    std::cout << "After startup:\n";
    for (std::size_t i = 0; i < board.size(); ++i) {
        std::cout << board[i]->summary() << "\n";
    }

    std::cout << "Current draw after startup: " << board() << " mA\n";

    board.tickAll();

    std::cout << "After one simulation tick:\n";
    for (std::size_t i = 0; i < board.size(); ++i) {
        std::cout << board[i]->summary() << "\n";
    }

    std::cout << "Current draw after tick: " << board() << " mA\n";

    std::cout << "Individual currents:\n";
    for (std::size_t i = 0; i < board.size(); ++i) {
        std::cout << board[i]->getName()
                  << ": "
                  << (*board[i])()
                  << " mA\n";
    }

    board[1]->reset();

    std::cout << "After resetting only motor:\n";
    for (std::size_t i = 0; i < board.size(); ++i) {
        std::cout << board[i]->summary() << "\n";
    }

    std::cout << "Current draw after motor reset: " << board() << " mA\n";

    const StartupSequence& constSequence = sequence;
    const RobotModule* firstModule = constSequence[0];

    std::cout << "First module in startup sequence: "
              << firstModule->getName()
              << " -> "
              << firstModule->diagnostic()
              << "\n";

    sequence.resetAll();

    std::cout << "After full reset:\n";
    for (std::size_t i = 0; i < board.size(); ++i) {
        std::cout << board[i]->summary() << "\n";
    }

    std::cout << "Final current draw: " << board() << " mA\n";

    return 0;
}

/* Oczekiwany wynik działania programu:
Initial board state:
SensorModule Distance sensor [id=SEN-1, current=1 mA] -> SLEEP sensitivity=3 samples=0
MotorModule Left motor [id=MOT-1, current=0 mA] -> STOPPED load=2 heat=0
RadioModule Telemetry radio [id=RAD-1, current=1 mA] -> OFF channel=7 packets=0
Initial current draw: 2 mA
After startup:
SensorModule Distance sensor [id=SEN-1, current=8 mA] -> ACTIVE sensitivity=3 samples=0
MotorModule Left motor [id=MOT-1, current=240 mA] -> ACTIVE load=2 heat=0
RadioModule Telemetry radio [id=RAD-1, current=30 mA] -> ACTIVE channel=7 packets=0
Current draw after startup: 278 mA
After one simulation tick:
SensorModule Distance sensor [id=SEN-1, current=8 mA] -> ACTIVE sensitivity=3 samples=3
MotorModule Left motor [id=MOT-1, current=260 mA] -> ACTIVE load=2 heat=2
RadioModule Telemetry radio [id=RAD-1, current=37 mA] -> ACTIVE channel=7 packets=7
Current draw after tick: 305 mA
Individual currents:
Distance sensor: 8 mA
Left motor: 260 mA
Telemetry radio: 37 mA
After resetting only motor:
SensorModule Distance sensor [id=SEN-1, current=8 mA] -> ACTIVE sensitivity=3 samples=3
MotorModule Left motor [id=MOT-1, current=0 mA] -> STOPPED load=2 heat=0
RadioModule Telemetry radio [id=RAD-1, current=37 mA] -> ACTIVE channel=7 packets=7
Current draw after motor reset: 45 mA
First module in startup sequence: Distance sensor -> ACTIVE sensitivity=3 samples=3
After full reset:
SensorModule Distance sensor [id=SEN-1, current=1 mA] -> SLEEP sensitivity=3 samples=0
MotorModule Left motor [id=MOT-1, current=0 mA] -> STOPPED load=2 heat=0
RadioModule Telemetry radio [id=RAD-1, current=1 mA] -> OFF channel=7 packets=0
Final current draw: 2 mA
*/
