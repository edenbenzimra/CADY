#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

class ConfigLoader {
public:
    ConfigLoader(const std::string& configFilePath) : configFilePath(configFilePath) {}

    void loadConfig();
    std::vector<std::string> getTextFilePaths() const;
    float getconditionTemperature() const;
    float getconditionVoltage() const;

private:
    nlohmann::json configJson;
    std::string configFilePath;
    float conditionTemperature = 0.0f;
    float conditionVoltage = 0.0f;
};

#endif // CONFIGLOADER_H