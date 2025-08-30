#include "../lib/logger.h"

// Constructor
Logger::Logger(const std::string& nombreArchivo, Level nivel, bool mostrarConsola) 
    : nivelActual(nivel), mostrarEnConsola(mostrarConsola) {
    
    archivo.open(nombreArchivo, std::ios::app);
    if (archivo.is_open()) {
        // Obtener fecha y hora actual para la sesión
        auto ahora = std::chrono::system_clock::now();
        std::time_t tiempo = std::chrono::system_clock::to_time_t(ahora);
        std::tm* tiempo_local = std::localtime(&tiempo);
        
        archivo << "\n=== K1rtash Games - " 
                << std::put_time(tiempo_local, "%d/%m/%Y %H:%M:%S") 
                << " ===\n";
    }
}

// Destructor
Logger::~Logger() {
    if (archivo.is_open()) {
        archivo << "=== End of the log ===\n\n";
        archivo.close();
    }
}

// Obtener timestamp con milisegundos
std::string Logger::obtenerTimestamp() {
    auto ahora = std::chrono::system_clock::now();
    auto since_epoch = ahora.time_since_epoch();
    auto segundos = std::chrono::duration_cast<std::chrono::seconds>(since_epoch);
    auto milisegundos = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch - segundos);
    
    std::time_t tiempo = std::chrono::system_clock::to_time_t(ahora);
    std::tm* tiempo_local = std::localtime(&tiempo);
    
    std::stringstream ss;
    ss << "["
       << std::setfill('0') << std::setw(2) << tiempo_local->tm_hour << ":"
       << std::setfill('0') << std::setw(2) << tiempo_local->tm_min << ":"
       << std::setfill('0') << std::setw(2) << tiempo_local->tm_sec << "."
       << std::setfill('0') << std::setw(3) << milisegundos.count()
       << "]";
    
    return ss.str();
}

// Convertir nivel a texto
std::string Logger::nivelToTexto(Level nivel) {
    switch(nivel) {
        case DEBUG:    return "DEBUG";
        case INFO:     return "INFO";
        case WARNING:  return "WARNING";
        case ERROR:    return "ERROR";
        case CRITICAL: return "CRITICAL";
        default:       return "UNKNOWN";
    }
}

// Método principal de escritura
void Logger::escribir(Level nivel, const std::string& mensaje) {
    // Solo escribir si el nivel es suficiente
    if (nivel < nivelActual) {
        return;
    }
    
    std::string timestamp = obtenerTimestamp();
    std::string nivelTexto = nivelToTexto(nivel);
    
    std::string linea = timestamp + " [" + nivelTexto + "] " + mensaje;
    
    // Mostrar en consola
    if (mostrarEnConsola) {
        std::cout << linea << '\n';
    }
    
    // Escribir en archivo
    if (archivo.is_open()) {
        archivo << linea << '\n';
    }
}

// Métodos públicos específicos
void Logger::debug(const std::string& mensaje) {
    escribir(DEBUG, mensaje);
}

void Logger::info(const std::string& mensaje) {
    escribir(INFO, mensaje);
}

void Logger::warning(const std::string& mensaje) {
    escribir(WARNING, mensaje);
}

void Logger::error(const std::string& mensaje) {
    escribir(ERROR, mensaje);
}

void Logger::critical(const std::string& mensaje) {
    escribir(CRITICAL, mensaje);
}

// Configuración
void Logger::setNivel(Level nuevoNivel) {
    nivelActual = nuevoNivel;
}

void Logger::setMostrarConsola(bool mostrar) {
    mostrarEnConsola = mostrar;
}