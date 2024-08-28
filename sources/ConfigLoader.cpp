#include "ConfigLoader.h"

void ConfigLoader::loadConfig() {
    std::ifstream configFile(configFilePath);
    if (!configFile.is_open()) {
        std::cerr << "Failed to open config file: " << configFilePath << std::endl;
        return;
    }

    // Check if the file is empty
    configFile.seekg(0, std::ios::end);
    std::streampos fileSize = configFile.tellg();
    configFile.seekg(0, std::ios::beg);

    if (fileSize <= 0) {
        std::cerr << "Config file is empty or cannot be read." << std::endl;
        return;
    }

    try {
        configFile >> configJson;

        // Parse and validate additional float values
        if (configJson.contains("condition_temperature") && configJson["condition_temperature"].is_number()) {
            conditionTemperature = configJson["condition_temperature"].get<float>();
        }
        else {
            std::cerr << "Invalid or missing 'condition_temperature' in config file." << std::endl;
        }

        if (configJson.contains("condition_voltage") && configJson["condition_voltage"].is_number()) {
            conditionVoltage = configJson["condition_voltage"].get<float>();
        }
        else {
            std::cerr << "Invalid or missing 'condition_voltage' in config file." << std::endl;
        }

    }
    catch (const nlohmann::json::parse_error& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
    }
    catch (const nlohmann::json::type_error& e) {
        std::cerr << "JSON type error: " << e.what() << std::endl;
    }
}

std::vector<std::string> ConfigLoader::getTextFilePaths() const {
    std::vector<std::string> filePaths;
    try {
        if (configJson.contains("file_paths") && configJson["file_paths"].is_string()) {
            std::string filePathsDir = configJson["file_paths"].get<std::string>();

            // Iterate through files in the directory
            for (const auto& entry : std::filesystem::directory_iterator(filePathsDir)) {
                if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                    filePaths.push_back(entry.path().string());
                }
            }
        }
        else {
            std::cerr << "Invalid or missing 'file_paths' in config file." << std::endl;
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    return filePaths;
}


float ConfigLoader::getconditionTemperature() const {
    return conditionTemperature;
}

float ConfigLoader::getconditionVoltage() const {
    return conditionVoltage;
}