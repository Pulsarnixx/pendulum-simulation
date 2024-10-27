#pragma once

//-------CORE-------------------------------
#include "log/log.hpp"
#include "timers/TimeManager.hpp"

//-------MATH-------------------------------
#include <glm/gtc/matrix_transform.hpp>

//-------END CORE---------------------------



//-------GRAPHICS---------------------------
#include "system.hpp"

//-------IMGUI---------------------------               TO REMOVE!!!
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//-------RENDERER---------------------------
#include "renderer/shader.hpp"

//-------RENDERER CORE----------------------
#include "renderer/core/VertexArray.hpp"
#include "renderer/core/VertexBuffer.hpp"
#include "renderer/core/VertexBufferLayout.hpp"
#include "renderer/core/IndexBuffer.hpp"
#include "renderer/core/Textures.hpp"
#include "renderer/core/Mesh.hpp"

//-------RENDERER PRIMITIVES----------------
#include "renderer/primitives/Cube.hpp"


//-------END GRAPHICS-----------------------