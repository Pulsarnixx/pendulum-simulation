#pragma once

//-------CORE----------------------
#include "log/log.hpp"
#include "timer/timer.hpp"

#define PX_TIMER Timer
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

//GRAPHICS PRIMITIVES
#include "renderer/primitives/Cube.hpp"
//---------------------------------