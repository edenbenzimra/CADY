#include <iostream>
#include "ComponentManager.h"
#include "ConfigLoader.h"

int main() {
    // Load configuration
    ConfigLoader configLoader("../Config/config.json");
    std::vector<std::string> filePaths = configLoader.getTextFilePaths();

    // Initialize Component Manager and load components
    ComponentManager manager;
    manager.initializeTemperaturePatterns();
    manager.initializeVoltagePatterns();
    manager.loadComponentsFromFiles(filePaths);

    manager.printComponents();

    return 0;
}
