#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include "Component.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <regex>
#include <filesystem>

using Patterns = std::unordered_map<std::string, std::regex>;

class ComponentManager {
public:
    void loadComponentsFromFiles(const std::vector<std::string>& filePaths);
    void initializeTemperaturePatterns();
    void initializeVoltagePatterns();
    void printComponents();
private:
    
    Patterns mTempPatterns;
    Patterns mVoltPatterns;
    std::vector<Component> components;
    void parseComponentFile(const std::string& filePath);
    bool parseTemperatureRange(const std::string& line, Component* component);
    bool parseVoltRange(const std::string& line, Component* component);
};
#endif // COMPONENTMANAGER_H