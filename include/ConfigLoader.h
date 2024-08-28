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

    std::vector<std::string> getTextFilePaths() const;

private:
    std::string configFilePath;
};

#endif // CONFIGLOADER_H