#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>

class Logger {
public:
    enum Level {
        DEBUG,
        INFO, 
        WARNING,
        ERROR,
        CRITICAL
    };

    // Constructor
    Logger(const std::string& nombreArchivo = "game.log", 
           Level nivel = INFO, 
           bool mostrarConsola = true);
    
    // Destructor
    ~Logger();
    
    // Métodos para logging
    void debug(const std::string& mensaje);
    void info(const std::string& mensaje);
    void warning(const std::string& mensaje);
    void error(const std::string& mensaje);
    void critical(const std::string& mensaje);
    
    // Configuración
    void setNivel(Level nuevoNivel);
    void setMostrarConsola(bool mostrar);

private:
    std::ofstream archivo;
    Level nivelActual;
    bool mostrarEnConsola;
    
    std::string obtenerTimestamp();
    std::string nivelToTexto(Level nivel);
    void escribir(Level nivel, const std::string& mensaje);
};

#endif // LOGGER_H