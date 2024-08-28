#include <iostream>
#include "ComponentManager.h"
#include "ConfigLoader.h"

int main() {
    // Load configuration
    ConfigLoader configLoader("../Config/config.json");
    configLoader.loadConfig();
    std::vector<std::string> filePaths = configLoader.getTextFilePaths();
    float conditionTemperature = configLoader.getconditionTemperature();
    float conditionVoltage = configLoader.getconditionVoltage();

    // Initialize Component Manager and load components
    ComponentManager manager;
    manager.initializeTemperaturePatterns();
    manager.initializeVoltagePatterns();
    manager.loadComponentsFromFiles(filePaths);
    manager.printComponentsWithinOperatingConditions(conditionVoltage, conditionTemperature);

    return 0;
}
