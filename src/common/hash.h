// Copyright 2015 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <cstddef>
#include <cstring>
#include <utility>
//#include <boost/functional/hash.hpp>
#include "common/cityhash.h"
#include "common/common_types.h"

namespace Common {

/**
 * Computes a 64-bit hash over the specified block of data
 * @param data Block of data to compute hash over
 * @param len Length of data (in bytes) to compute hash over
 * @returns 64-bit hash value that was computed over the data block
 */
static inline u64 ComputeHash64(const void* data, std::size_t len) {
    return CityHash64(static_cast<const char*>(data), len);
}

/**
 * Computes a 64-bit hash of a struct. In addition to being trivially copyable, it is also critical
 * that either the struct includes no padding, or that any padding is initialized to a known value
 * by memsetting the struct to 0 before filling it in.
 */
template <typename T>
static inline u64 ComputeStructHash64(const T& data) {
    static_assert(std::is_trivially_copyable_v<T>,
                  "Type passed to ComputeStructHash64 must be trivially copyable");
    return ComputeHash64(&data, sizeof(data));
}

struct PairHash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& pair) const noexcept {
        std::size_t seed = std::hash<T1>()(pair.first);
        printf("HASH COMBINE MISSING\n");
        //boost::hash_combine(seed, std::hash<T2>()(pair.second));
        return seed;
    }
};

} // namespace Common
