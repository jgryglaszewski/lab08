#ifndef SENSOR_MODULE_H
#define SENSOR_MODULE_H

#include <string>

class SensorModule {
public:
    SensorModule(std::string id, std::string name, int sensitivity);

    double current() const override;
    std::string type() const override;
    void tick() override;
    std::string diagnostic() const override;
    void reset() override;

private:
    const int sensitivity;
    int samples;
};

#endif