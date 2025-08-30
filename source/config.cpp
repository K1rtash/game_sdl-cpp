#include "../lib/config.h"
#include <iostream>
#include <fstream>
#include <filesystem>  // Necesita C++17 o superior

// Para evitar escribir std::filesystem:: todo el tiempo
namespace fs = std::filesystem;

ConfigLoader::ConfigLoader(const std::string& filename) {
    // Debug: mostrar dónde estamos buscando
    std::cout << "Buscando options.txt en: " << fs::current_path() << std::endl;
    
    std::ifstream archivo(filename);
    
    if (!archivo.is_open()) {
        std::cerr << "ERROR: No se pudo abrir '" << filename << "'" << std::endl;
        std::cerr << "Directorio actual: " << fs::current_path() << std::endl;
        
        // Listar archivos en el directorio actual para debug
        std::cerr << "Archivos en el directorio:" << std::endl;
        try {
            for (const auto& entry : fs::directory_iterator(".")) {
                std::cerr << " - " << entry.path().filename() << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error al listar directorio: " << e.what() << std::endl;
        }
        
        return;
    }
    
    std::cout << "Archivo '" << filename << "' abierto correctamente" << std::endl;
    
    std::string linea;
    int lineCount = 0;
    while (std::getline(archivo, linea)) {
        lineCount++;
        
        // Saltar líneas vacías y comentarios
        if (linea.empty() || linea[0] == '#') {
            continue;
        }
        
        // Buscar el signo igual
        size_t pos = linea.find('=');
        if (pos != std::string::npos) {
            std::string clave = linea.substr(0, pos);
            std::string valor = linea.substr(pos + 1);
            
            // Eliminar espacios en blanco
            clave.erase(0, clave.find_first_not_of(" \t"));
            clave.erase(clave.find_last_not_of(" \t") + 1);
            
            valor.erase(0, valor.find_first_not_of(" \t"));
            valor.erase(valor.find_last_not_of(" \t") + 1);
            
            configuraciones[clave] = valor;
            std::cout << "Config: " << clave << " = " << valor << std::endl;
        }
    }
    
    archivo.close();
    std::cout << "Procesadas " << lineCount << " líneas, " 
              << configuraciones.size() << " configuraciones cargadas" << std::endl;
}