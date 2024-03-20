/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file result.hpp                                                         *
 * ------------------------------------------------------------------------ *
 * @copyright (c) 2024 Oniup (https://github.com/Oniup)                     *
 *                                                                          *
 * Licensed under the Apache License, Version 2.0 (the "License");          *
 * you may not use this file except in compliance with the License.         *
 * You may obtain a copy of the License at                                  *
 *                                                                          *
 *   http://www.apache.org/licenses/LICENSE-2.0                             *
 *                                                                          *
 * Unless required by applicable law or agreed to in writing, software      *
 * distributed under the License is distributed on an "AS IS" BASIS,        *
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
 * See the License for the specific language governing permissions and      *
 * limitations under the License.                                           *
 * ------------------------------------------------------------------------ */

#ifndef KRYOS__TOOLS__RESULT_HPP
#define KRYOS__TOOLS__RESULT_HPP

#include "kryos-tools/debug.hpp"
#include <cstdarg>
#include <cstdio>

#define MAX_RSEULT_ERROR_MESSAGE_SIZE 2000

template <typename T>
struct KRYOS_API Result {
    enum class Status {
        Undefined,
        Ok,
        Failed,
        Fatal,
    };

    T data = {};
    Status status = Status::Undefined;
    const char* error_message;

    static Result ok(T&& data) {
        return Result {
            .data = static_cast<T&&>(data),
            .status = Status::Ok,
            .error_message = nullptr,
        };
    }

    static Result failed(T&& data, const char* error_message_format, ...) {
        va_list args;
        va_start(args, error_message_format);
        Result result {
            .data = static_cast<T&&>(data),
            .status = Status::Failed,
            .error_message = setErrorMessage(error_message_format, args),
        };
        va_end(args);
        return result;
    }

    static Result fatalError(const char* error_message_format, ...) {
        va_list args;
        va_start(args, error_message_format);
        Result result {
            .data = {},
            .status = Status::Fatal,
            .error_message = setErrorMessage(error_message_format, args),
        };
        va_end(args);
        return result;
    }

    inline bool isOk() const { return status == Status::Ok; }
    inline bool isFatal() const { return status == Status::Fatal; }

    T&& unwrap() {
        if (!isOk() || isFatal()) {
            ASSERT("Result Failed: %s", error_message);
        }
        return static_cast<T&&>(data);
    }

    T&& unwrapAnyway() {
        if (!isOk() || isFatal()) {
            ERROR("Result Failed: %s", error_message);
        }
        return static_cast<T&&>(data);
    }

private:
    static const char* setErrorMessage(const char* error_message_format, va_list args) {
        static char buffer[MAX_RSEULT_ERROR_MESSAGE_SIZE];
        std::vsnprintf(buffer, MAX_RSEULT_ERROR_MESSAGE_SIZE, error_message_format, args);
        return buffer;
    }
};

#endif
