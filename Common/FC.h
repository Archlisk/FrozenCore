#pragma once

#include <stddef.h>
#include <stdint.h>
#include <memory>
#include <string>
#include <stdexcept>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

template<typename T>
using Ptr = std::unique_ptr<T>;

template<typename T>
using Ref = std::shared_ptr<T>;

using String = std::string;

using RuntimeException = std::runtime_error;

template<typename T, typename... Targs>
constexpr Ptr<T> MakePtr(Targs&&... args) { return std::make_unique(std::forward<Targs>(args)...); }

template<typename T, typename... Targs>
constexpr Ref<T> MakeRef(Targs&&... args) { return std::make_shared(std::forward<Targs>(args)...); }
