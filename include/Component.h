#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <utility>
#include <iostream>

class Component {
public:
    Component(const std::string& name, std::pair<float, float> voltageRange, std::pair<float, float> temperatureRange)
        : name(name), voltageRange(voltageRange), temperatureRange(temperatureRange) {}
    Component(){}

    bool mIsNameSet = false;
    bool mIsVoltageRangeSet = false;
    bool mIsTemperatureRangeSet = false;

    void printComponent() const;

    // Getters
    std::string getName()const;
    std::pair<float, float> getVoltageRange()const;
    std::pair<float, float> getTemperatureRange()const;

    // Setters
    void setName(const std::string& newName);
    void setVoltageRange(float min, float max);
    void setTemperatureRange(float min, float max);

private:
    std::string name;
    std::pair<float, float> voltageRange;
    std::pair<float, float> temperatureRange;

    std::string Component::printRange(const std::pair<float, float>& range) const;
};

#endif // COMPONENT_H
