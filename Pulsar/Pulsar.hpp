#pragma once

//-------CORE----------------------
#include "log/log.hpp"
#include "timer/timer.hpp"

#define PX_TIMER Timer
#define PX_LOG Log
//---------------------------------

//-------GRAPHICS----------------------
#include "system.hpp"
#include "renderer/shader.hpp"
#include "renderer/core/VertexArray.hpp"
#include "renderer/core/VertexBuffer.hpp"
#include "renderer/core/VertexBufferLayout.hpp"
#include "renderer/core/IndexBuffer.hpp"
#define PX System
//---------------------------------