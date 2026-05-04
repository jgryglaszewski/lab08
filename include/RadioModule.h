#ifndef RADIO_MODULE_H
#define RADIO_MODULE_H

#include "RobotModule.h"
#include <string>

using std::string;

class RadioModule : public RobotModule {
    public:
        RadioModule(string, string, double);
        ~RadioModule() = default;
        double operator()() const;
        double current() const;
        void tick();
        void reset();
        string diagnostic() const;
        string type() const;
    private:
        double channel;
        double packets;
};


#endif