#include "Component.h"

// Getters
std::string Component::getName() const {
    return name;
}

std::pair<float, float> Component::getVoltageRange() const {
    return voltageRange;
}

std::pair<float, float> Component::getTemperatureRange() const {
    return temperatureRange;
}

// Setters
void Component::setName(const std::string& newName) {
    name = newName;
    mIsNameSet = true;
}

void Component::setVoltageRange(float min, float max) {
    voltageRange.first = min;
    voltageRange.second = max;
    mIsVoltageRangeSet = true;

}

void Component::setTemperatureRange(float min, float max) {
    temperatureRange.first = min;
    temperatureRange.second = max;
    mIsTemperatureRangeSet = true;

}

// Function to print the members of the class
void Component::printComponent() const {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Voltage Range: " << printRange(voltageRange) << std::endl;
    std::cout << "Temperature Range: " << printRange(temperatureRange) << std::endl;
}

std::string Component::printRange(const std::pair<float, float>& range) const {
    return "(" + std::to_string(range.first) + ", " + std::to_string(range.second) + ")";
}