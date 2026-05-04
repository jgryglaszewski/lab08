#ifndef MOTOR_MODULE_H
#define MOTOR_MODULE_H

#include "RobotModule.h"
#include <string>

using std::string;
using std::to_string;

class MotorModule : public RobotModule{
    public:
        MotorModule(string, string, double);
        double operator()() const;
        double current() const;
        void tick();
        void reset();
        string diagnostic() const;
        string type() const;
    private:
        double heat;    
        double load;
        
};

#endif