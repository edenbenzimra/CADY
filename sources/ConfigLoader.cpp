#include "ConfigLoader.h"


std::vector<std::string> ConfigLoader::getTextFilePaths() const {
    std::ifstream configFile(configFilePath);
    if (!configFile.is_open()) {
        std::cerr << "Failed to open config file: " << configFilePath << std::endl;
        return {};
    }

    // Check if the file is empty
    configFile.seekg(0, std::ios::end);
    std::streampos fileSize = configFile.tellg();
    configFile.seekg(0, std::ios::beg);

    if (fileSize <= 0) {
        std::cerr << "Config file is empty or cannot be read." << std::endl;
        return {};
    }

    nlohmann::json configJson;
    configJson = nlohmann::json::parse(configFile);


    std::vector<std::string> filePaths;
    try {
        // Iterate through files in the directory
        for (const auto& entry : std::filesystem::directory_iterator(configJson["file_paths"])) {
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                filePaths.push_back(entry.path().string());
            }
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
        return {};
    }


    return filePaths;
}