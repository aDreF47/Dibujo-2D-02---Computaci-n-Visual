# Dibujo OpenGL

Este es un proyecto de OpenGL que renderiza un dibujo utilizando **GLFW**, **GLAD** y **GLM**.

## 📦 Requisitos

Asegúrate de tener instaladas las siguientes dependencias:

### **Windows (MSYS2 - MinGW)**
```sh
pacman -S mingw-w64-x86_64-glfw mingw-w64-x86_64-glew mingw-w64-x86_64-gcc
```

### **Linux (Ubuntu/Debian)**
```sh
sudo apt update
sudo apt install libglfw3-dev libglew-dev libgl1-mesa-dev libglu1-mesa-dev
```

### **MacOS (Homebrew)**
```sh
brew install glfw glew
```

## 🔧 Compilación y Ejecución

Si usas `g++`:

```sh
g++ -o dibujo src/main.cpp src/glad.c -Iinclude -Llib -lglfw3dll -ldl -lopengl32 -lgdi32
```

Si usas **CMake**, crea una carpeta `build/` y compila:

```sh
mkdir build && cd build
cmake ..
make
./dibujo
```

## 📜 Estructura del Proyecto
```
Dibujo 2D 02-SegundoTrabajoLaboratorio/
│── include/        # Cabeceras de OpenGL, GLFW, GLM
│── lib/            # Librerías precompiladas
│── src/            # Código fuente
│── .vscode/        # Configuración de VS Code (ignorado en .gitignore)
│── CMakeLists.txt  # Archivo de CMake (opcional)
│── README.md       # Instrucciones de compilación
│── .gitignore      # Archivos a ignorar en Git
```

## 🚀 Notas

- Si tienes problemas con `glad`, verifica que esté correctamente referenciado.
- Para agregar más configuraciones de compilación, edita `CMakeLists.txt` o el comando `g++` según tu sistema operativo.
- Asegúrate de que todas las librerías necesarias estén en `include/` y `lib/` para evitar errores de compilación.

Cualquier duda, ¡pregunta! 😊

