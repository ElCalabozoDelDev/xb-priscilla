cmake_minimum_required(VERSION 3.10)

# Especifica Clang como compilador
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

# # Integración con vcpkg
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/build/vcpkg_installed/x64-windows/share")

# Nombre del proyecto
project(xb-priscilla VERSION 1.0 LANGUAGES CXX)

# Configuración de CMake
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Configuración de C++ estándar
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Recursivamente busca todos los archivos .cpp dentro del directorio src/
file(GLOB_RECURSE SOURCES app/src/*.cpp)

# Crea el ejecutable en la carpeta _bin
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Crea el ejecutable
add_executable(${PROJECT_NAME} ${SOURCES})

# # Añadir el directorio de third_party a los include directories
# target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/third_party)

# # Busca recursivamente todos los archivos .cpp en third_party y agrégalos a las fuentes del proyecto
# file(GLOB_RECURSE THIRD_PARTY_SOURCES ${CMAKE_SOURCE_DIR}/third_party/*.cpp)

# # Agrega los archivos de implementación de third_party al proyecto
# target_sources(${PROJECT_NAME} PRIVATE ${THIRD_PARTY_SOURCES})

# Busca e incluye las dependencias desde vcpkg
find_package(Crow CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Enlaza las dependencias
target_link_libraries(${PROJECT_NAME} PUBLIC Crow::Crow)
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)

# Configura los directorios de inclusión
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_SOURCE_DIR}/app/include
)

# Comando personalizado para copiar config.json al directorio del ejecutable
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/config.json"  # Ruta al archivo de configuración en la raíz del proyecto
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/config.json"  # Copia al directorio donde está el ejecutable
)