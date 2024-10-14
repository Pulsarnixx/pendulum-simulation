#pragma once

//-------CORE----------------------
#include "log/log.hpp"
#include "timers/TimeManager.hpp"

#define PX_LOG Log
//---------------------------------

//-------GRAPHICS----------------------
#include "system.hpp"
#define PX System

#include "renderer/shader.hpp"

//GRAPHICS CORE
#include "renderer/core/VertexArray.hpp"
#include "renderer/core/VertexBuffer.hpp"
#include "renderer/core/VertexBufferLayout.hpp"
#include "renderer/core/IndexBuffer.hpp"
#include "renderer/core/Textures.hpp"

//GRAPHICS PRIMITIVES
#include "renderer/primitives/Cube.hpp"
//---------------------------------