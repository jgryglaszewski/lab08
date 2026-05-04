#ifndef MOTOR_MODULE_H
#define MOTOR_MODULE_H

#include <string>

using std::string;
using std::to_string;

class MotorModule : public RobotModule{
    public:
        MotorModule(string, string, double);
        double operator()();
        double current();
        void tick();
        void reset();
        string diagnostic();
        string type();
    private:
        double load;
        double heat;
};

#endif