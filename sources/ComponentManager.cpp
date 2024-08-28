#include "ComponentManager.h"


void ComponentManager::initializeTemperaturePatterns() {
    mTempPatterns["Temperature range"] = std::regex(R"(([+-]?[0-9]+(?:\.[0-9]+)?)\s*°C\s*to\s*([+-]?[0-9]+(?:\.[0-9]+)?)\s*°C)", std::regex::icase);
    // Add more patterns as needed
}

void ComponentManager::initializeVoltagePatterns() {
    mVoltPatterns["Voltage range"] = std::regex(R"(([0-9]+(?:\.[0-9]+)?)\s*V\s*to\s*([0-9]+(?:\.[0-9]+)?)\s*V)", std::regex::icase);
    // Add more patterns as needed
}

void ComponentManager::loadComponentsFromFiles(const std::vector<std::string>& filePaths) {
    for (const auto& path : filePaths) {
        parseComponentFile(path);
    }
}

void ComponentManager::parseComponentFile(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string line;
    std::string name;
    bool voltageRangeSet = false;
    bool temperatureRangeSet = false;

    std::filesystem::path filePathObj(filePath);
    std::string fileNameWithoutExt = filePathObj.stem().string();

    Component component;
    component.setName(fileNameWithoutExt);
    
    // Read entire file content into a string
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    temperatureRangeSet = parseTemperatureRange(content, &component);
    voltageRangeSet = parseVoltRange(content, &component);

    if (component.getTemperatureRange().first == std::nanf("") && component.getTemperatureRange().second == std::nanf(""))
    {
        temperatureRangeSet = false;
        std::cerr << "File: " << filePath << "file has more than one temperature range for an item which are not identical -> NAN" << std::endl;
    }

    if (component.getVoltageRange().first == std::nanf("") && component.getVoltageRange().second == std::nanf(""))
    {
        voltageRangeSet = false;
        std::cerr << "File: " << filePath << "file has more than one voltage range for an item which are not identical -> NAN" << std::endl;
    }

    if (voltageRangeSet && temperatureRangeSet) {
        components.emplace_back(component);
    }
    else {
        std::cerr << "Invalid data in file: " << filePath << std::endl;
    }
}

bool ComponentManager::parseTemperatureRange(const std::string& line, Component* component) {
    for (const auto& [key, pattern] : mTempPatterns) {
        std::smatch match;
        if (std::regex_search(line, match, pattern) && match.size() == 3) {
            if (component->mIsTemperatureRangeSet)
            {
                if (component->getTemperatureRange().first != std::stof(match[1].str()) || component->getTemperatureRange().second != std::stof(match[2].str()))
                {
                    component->setTemperatureRange(std::nanf(""), std::nanf(""));
                }
            }
            component->setTemperatureRange(std::stof(match[1].str()), std::stof(match[2].str()));
            return true;
        }
    }
    return false;
}

bool ComponentManager::parseVoltRange(const std::string& line, Component* component) {
    for (const auto& [key, pattern] : mVoltPatterns) {
        std::smatch match;
        if (std::regex_search(line, match, pattern) && match.size() == 3) {
            if (component->mIsVoltageRangeSet)
            {
                if (component->getVoltageRange().first != std::stof(match[1].str()) || component->getVoltageRange().second != std::stof(match[2].str()))
                {
                    component->setVoltageRange(std::nanf(""), std::nanf(""));
                }
            }
            component->setVoltageRange(std::stof(match[1].str()), std::stof(match[2].str()));
            return true;
        }
    }
    return false;
}

void ComponentManager::printComponentsWithinOperatingConditions(float voltage, float temperature)
{
    // Print all components in the vector
    std::cout << "The following components can operate under the given conditions:"  << std::endl; // Optional: Add a line break between components
    std::cout << "Temperature:" << temperature << std::endl; // Optional: Add a line break between components
    std::cout << "Voltage:" << voltage << std::endl; // Optional: Add a line break between components
    for (const auto& component : components) {
        if (component.isWithinOperatingConditions(voltage, temperature))
        {
            component.printComponent();
            std::cout << std::endl; // Optional: Add a line break between components
        }
    }
}

