#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include <vector>

class FileUtils {
public:
    static std::string getExecutablePath();
    static std::string getConfigPath(const std::string& filename);
    static bool fileExists(const std::string& path);
    static std::vector<std::string> findConfigFile(const std::string& filename);
};

#endif // FILE_UTILS_H