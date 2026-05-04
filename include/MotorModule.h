#ifndef MOTOR_MODULE_H
#define MOTOR_MODULE_H

#include <string>

using std::string;

class MotorModule : public RobotModule{
    public:
        MotorModule();
        double operator()();
        double current();
        void tick();
        void reset();
        string diagnostic();
    private:
        double load;
        double heat;
};

#endif