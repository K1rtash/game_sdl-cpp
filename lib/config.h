#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <unordered_map>

class ConfigLoader {
private:
    std::unordered_map<std::string, std::string> configuraciones;  // ← Esto debe estar declarado

public:
    ConfigLoader(const std::string& filename = "options.txt");
    
    std::string getString(const std::string& key, const std::string& defaultValue = "");
    int getInt(const std::string& key, int defaultValue = 0);
    float getFloat(const std::string& key, float defaultValue = 0.0f);
    bool getBool(const std::string& key, bool defaultValue = false);
    bool hasKey(const std::string& key);
};

#endif // CONFIG_H