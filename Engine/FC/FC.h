#pragma once

// Operating systems

#ifdef __linux__
	#define FC_LINUX
#elif defined(_WIN64)
	#define FC_WINDOWS
#else
	#error "Unsupported platform"
#endif


// Compilers

#ifdef __GNUC__
	#define FC_GCC
#elif defined(_MSC_VER)
	#define FC_MSVC
#endif


// Less stupid primitive names

#include <stdint.h>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t	 u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t	i8;

typedef double f64;
typedef float  f32;


// Smart pointers

#include <memory>

template<typename T>
using Ptr = std::unique_ptr<T>;

template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename... Targs>
constexpr Ptr<T> NewPtr(Targs&&... args) { return std::make_unique<T>(std::forward<Targs>(args)...); }

template<typename T, typename... Targs>
constexpr Ref<T> NewRef(Targs&&... args) { return std::make_shared<T>(std::forward<Targs>(args)...); }


// DLL loading

#ifdef FC_GCC
	#define DLL_EXPORT __attribute__((visibility("default")))
	#define DLL_IMPORT
#elif defined(FC_MSVC)
	#define DLL_EXPORT __declspec(dllexport)
	#define DLL_IMPORT __declspec(dllimport)
#else
	#pragma message ("WARNING: Unknown compiler, some features may not work properly")
#endif


// Exceptions

#include <stdexcept>

using RuntimeException = std::runtime_error;


// Misc. Debug

#ifdef FC_GCC
	#include <signal.h>
	#define FC_DEBUG_BREAK raise(SIGTRAP)
#elif defined(FC_MSVC)
	#define FC_DEBUG_BREAK() __debugbreak()
#endif

#ifdef FC_GCC 
	#define FC_PRETTY_FUNC __PRETTY_FUNCTION__
#elif defined(FC_MSVC)
	#define FC_PRETTY_FUNC() __FUNCSIG__
#endif

#define CSTR(a) #a
#define EXPAND(a) CSTR(a)
#define FC_FILE_INFO (__FILE__ ": " EXPAND(__LINE__))

#define FC_ERROR(...) __VA_ARGS__

#define FC_WARNING(...) __VA_ARGS__

#ifdef FC_DEBUG_ASSERT_ENABLE
	#define FC_ASSERT(a, ...) { if ( !(a) ) { FC_ERROR(__VA_ARGS__); } }
	#define FC_ASSERT_BREAK(a, ...) { if ( !(a) ) { FC_WARNING(__VA_ARGS__); FC_DEBUG_BREAK(); } }
#else
	#define FC_ASSERT(a, ...)
	#define FC_ASSERT_BREAK(a, ...)
#endif



// Profiler

#ifdef FC_DEBUG_PROFILE_ENABLE
	#include <Debug/Profiler.h>

	#define FC_PROFILE_SCOPE(name) \
		static Profiler::Sample _fc_profile_sample(name); \
		ScopeSampler _fc_profile_scope_sampler(_fc_profile_sample);

	#define FC_PROFILE_FUNC() FC_PROFILE_SCOPE(String(FC_FILE_INFO) + ": " + FC_PRETTY_FUNC)
	
#else
	#define FC_PROFILE_SCOPE(name)
	#define FC_PROFILE_FUNC()
#endif
