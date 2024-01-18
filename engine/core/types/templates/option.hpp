/**
 * @file option.hpp
 *
 * This file is part of the Kryos Engine (See AUTHORS.md)
 * GitHub Repository: https://github.com/Oniup/kryos
 *
 * @copyright
 * Copyright (c) 2023-present Oniup (https://github.com/Oniup/)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef KRYOS__CORE_TYPES_TEMPLATES__OPTION_HPP
#define KRYOS__CORE_TYPES_TEMPLATES__OPTION_HPP

#include "core/log.hpp"

#include <type_traits>

#define KUNWRAP(opt) \
    opt.unwrap(__FILE__, __LINE__, "Cannot unwrap value from option as there is none")

#define KEXPECTS(opt, fmt, ...) opt.unwrap(__FILE__, __LINE__, fmt, __VA_ARGS__)

namespace kryos {

enum class OptState {
    ok,
    none,
    failed,
};

template <typename T>
class Opt {
public:
    static inline constexpr Opt none() { return Opt(); }
    static inline constexpr Opt some(const T& val) { return Opt(val, OptState::ok); }
    static inline constexpr Opt failed(const T& val) { return Opt(val, OptState::failed); }

    static inline constexpr Opt some(T&& val) {
        return Opt(static_cast<std::remove_reference_t<T>&&>(val), OptState::ok);
    }

    static inline constexpr Opt failed(T&& val) {
        return Opt(static_cast<std::remove_reference_t<T>&&>(val), OptState::failed);
    }

    Opt()
          : m_state(OptState::none) {}

    constexpr Opt(const T& val, OptState state)
          : m_state(state), m_val(val) {}

    constexpr Opt(T&& val, OptState state)
          : m_state(state), m_val(static_cast<std::remove_reference_t<T>&&>(val)) {
        if constexpr (std::is_pointer_v<T>) {
            val = nullptr;
        }
    }

    inline OptState status() const { return m_state; }
    inline T& value() { return m_val; }
    inline const T& value() const { return m_val; }

    T&& unwrap(const char* file, uint32_t line, const char* fmt, ...) {
        if (status() != kryos::OptState::ok) {
            va_list args;
            va_start(args, fmt);
            assert_unwrap(file, line, fmt, args);
        }
        return static_cast<std::remove_reference_t<T>&&>(m_val);
    }

    T&& unwrap(const char* file, uint32_t line, const char* fmt, va_list args) {
        if (status() != kryos::OptState::ok) {
            assert_unwrap(file, line, fmt, args);
        }
        return static_cast<std::remove_reference_t<T>&&>(m_val);
    }

private:
    void assert_unwrap(const char* file, uint32_t line, const char* fmt, ...) {
        va_list args;
        va_start(args, fmt);
        assert_unwrap(file, line, fmt, args);
    }

    void assert_unwrap(const char* file, uint32_t line, const char* fmt, va_list args) {
        impl_assert(file, line, fmt, args);
    }

    OptState m_state;
    T m_val;
};

} // namespace kryos

#endif
