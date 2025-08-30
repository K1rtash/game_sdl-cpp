#include "../lib/file_utils.h"
#include <iostream>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <limits.h>
#endif

namespace fs = std::filesystem;

std::string FileUtils::getExecutablePath() {
#ifdef _WIN32
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    return std::string(path);
#else
    char path[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", path, PATH_MAX);
    return std::string(path, (count > 0) ? count : 0);
#endif
}

std::string FileUtils::getConfigPath(const std::string& filename) {
    std::string exePath = getExecutablePath();
    fs::path exeDir = fs::path(exePath).parent_path();
    
    // Rutas posibles donde buscar
    std::vector<fs::path> possiblePaths = {
        fs::current_path() / filename,           // Directorio actual
        exeDir / filename,                       // Donde está el .exe
        exeDir / "config" / filename,            // Subcarpeta config/
        exeDir / ".." / filename,                // Una carpeta arriba
        fs::current_path() / "config" / filename // Config en directorio actual
    };
    
    for (const auto& path : possiblePaths) {
        if (fileExists(path.string())) {
            return path.string();
        }
    }
    
    // Si no se encuentra, devolver la ruta junto al ejecutable
    return (exeDir / filename).string();
}

bool FileUtils::fileExists(const std::string& path) {
    return fs::exists(path);
}

std::vector<std::string> FileUtils::findConfigFile(const std::string& filename) {
    std::vector<std::string> foundPaths;
    std::string exePath = getExecutablePath();
    fs::path exeDir = fs::path(exePath).parent_path();
    
    std::vector<fs::path> searchPaths = {
        fs::current_path(),
        exeDir,
        exeDir / "config",
        exeDir / "..",
        fs::current_path() / "config"
    };
    
    for (const auto& dir : searchPaths) {
        fs::path potentialPath = dir / filename;
        if (fileExists(potentialPath.string())) {
            foundPaths.push_back(potentialPath.string());
        }
    }
    
    return foundPaths;
}