#pragma once

#include "GameEngine/Core.h"

#include <spdlog/spdlog.h>

namespace GameEngine {

	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define GE_CORE_TRACE(...)			::GameEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GE_CORE_INFO(...)			::GameEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GE_CORE_WARN(...)			::GameEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GE_CORE_ERROR(...)			::GameEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GE_CORE_CRITICAL(...)		::GameEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define GE_TRACE(...)				::GameEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GE_INFO(...)				::GameEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GE_WARN(...)				::GameEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GE_ERROR(...)				::GameEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GE_CRITICAL(...)			::GameEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)
