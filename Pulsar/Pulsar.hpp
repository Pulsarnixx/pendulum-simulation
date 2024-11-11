#pragma once



//-------CORE-------------------------------
#include "log/log.hpp"
#include "timers/TimeManager.hpp"

//-------DEPENDECIES------------------------
#include <glad.h>
#include <GLFW/glfw3.h>

//-------MATH-------------------------------
#include <glm/gtc/matrix_transform.hpp>


//-------END CORE---------------------------



//-------GRAPHICS---------------------------
#include "system.hpp"

//-------RENDERER---------------------------
#include "renderer/shader.hpp"
#include "renderer/camera.hpp"

//-------RENDERER CORE----------------------
#include "renderer/core/Textures.hpp"
#include "renderer/core/Mesh.hpp"

//-------RENDERER PRIMITIVES----------------
#include "renderer/primitives/Circle.hpp"
#include "renderer/primitives/Square.hpp"

#include "renderer/primitives/Cube.hpp"
#include "renderer/primitives/Sphere.hpp"


//-------END GRAPHICS-----------------------