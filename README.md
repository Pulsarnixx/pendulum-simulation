# 🌟 Pendulum Simulation

The project for an engineering thesis at the Wroclaw University of Technology. 
For this purpose, I wrote a basic graphics engine based on GLFW and OpenGL and a pendulum motion simulation application based on it.
---
## 📋 Requirements

The code was written with modern Debian/Ubuntu systems in mind.

Before running the project, make sure you have the following tools and packages installed:
* C++ compiler
* CMake
* X11 and Wayland dependecies for GLFW

To install all dependecies try this command:
```bash
sudo apt-get install build-essential cmake xorg-dev libwayland-dev
libxkbcommon-dev wayland-protocols extra-cmake-modules
```
---

## 🚀 How to Run

Follow these steps to build and run the program:

1. **Clone the repository with git modules**:
   ```bash
   git clone --recurse-submodules https://github.com/Pulsarnixx/pendulum-simulation.git
   ```
2. **Go to repository and run bash script**:
   ```bash
   cd pendulum-simulation
   ./config.sh run
   ```
 ## 📄 License
 This project is licensed under the MIT License. Third party dependency used by this software and described in License file.

