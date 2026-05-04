#ifndef RADIO_MODULE_H
#define RADIO_MODULE_H

class RadioModule : public RobotModule {
    public:
        RadioModule(string, string, double);
        double operator()();
        double current();
        void tick();
        void reset();
        string diagnostic();
        string type();
    private:
        double channel;
        double packets;
}


#endif