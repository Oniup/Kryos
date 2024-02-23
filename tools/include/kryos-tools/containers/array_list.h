/// ------------------------------------------------------------------------ ///
/// This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) ///
/// @file array_list.h                                                       ///
/// ------------------------------------------------------------------------ ///
/// @copyright (c) 2024 Oniup (https://github.com/Oniup)                     ///
///                                                                          ///
/// Licensed under the Apache License, Version 2.0 (the "License");          ///
/// you may not use this file except in compliance with the License.         ///
/// You may obtain a copy of the License at                                  ///
///                                                                          ///
///   http://www.apache.org/licenses/LICENSE-2.0                             ///
///                                                                          ///
/// Unless required by applicable law or agreed to in writing, software      ///
/// distributed under the License is distributed on an "AS IS" BASIS,        ///
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. ///
/// See the License for the specific language governing permissions and      ///
/// limitations under the License.                                           ///
/// ------------------------------------------------------------------------ ///

#ifndef KRYOS__TOOLS_CONTAINERS__ARRAY_LIST_H
#define KRYOS__TOOLS_CONTAINERS__ARRAY_LIST_H
#ifdef __cplusplus
extern "C" {
#endif

#include "kryos-tools/debug.h"
#include "kryos-tools/defines.h"

#define ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT 20

typedef struct array_list_result {
    b8 failed;
    void* p_data;
} array_list_result_t;

KRYAPI void destroy_array_list(void* p_list);

KRYAPI usize intl_get_array_list_size(void* p_list, usize type_size);
KRYAPI usize intl_get_array_list_capacity(void* p_list, usize type_size);

KRYAPI array_list_result_t intl_create_array_list_uninitialized(usize type_size,
                                                                usize capacity_count);

KRYAPI array_list_result_t intl_resize_array_list_size(void* p_list, usize type_size, usize count);

/// @brief Resizes capacity by intervals of the `ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT` *
/// `type_size`.
///
/// @param `p_list` Array list instance. Cannot be a NULL value otherwise will fail.
/// @param `type_size` Size of the array list type bytes.
/// @param `count` Number of new instances required to fit in the new capacity (adds the current
/// capacity size to this new size for the total size).
///
/// @return Result struct determining whether the function failed.
KRYAPI array_list_result_t intl_resize_array_list_capacity(void* p_list, usize type_size,
                                                           usize count);

array_list_result_t intl_push_array_list_data_back(void* p_list, usize type_size, usize count,
                                                   void* p_data);

array_list_result_t intl_push_array_list_data_front(void* p_list, usize type_size, usize count,
                                                    void* p_data);

#define ARRAY_LIST(T) T*

#define create_array_list_uninitialized(T, count)                                            \
    ({                                                                                       \
        array_list_result_t result = intl_create_array_list_uninitialized(sizeof(T), count); \
        if (result.failed) {                                                                 \
            ERROR("Failed to create empty array list");                                      \
        }                                                                                    \
        result.p_data;                                                                       \
    })

#define create_array_list(T) \
    create_array_list_uninitialized(T, ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT)

#define get_array_list_size(p_list) intl_get_array_list_size(p_list, sizeof(*p_list))
#define get_array_list_capacity(p_list) intl_get_array_list_capacity(p_list, sizeof(*p_list))

#define push_array_list_copy(p_list, count, p_copy)                                 \
    ({                                                                              \
        array_list_result_t result =                                                \
            intl_push_array_list_data_back(p_list, sizeof(*p_list), count, p_copy); \
        if (result.failed) {                                                        \
            ERROR("Failed to push data (count: %zu) into array list", count);       \
        }                                                                           \
        p_list = (typeof(p_list))result.p_data;                                     \
    })

#define push_front_array_list_copy(p_list, count, p_copy)                              \
    ({                                                                                 \
        array_list_result_t result =                                                   \
            intl_push_array_list_data_front(p_list, sizeof(*p_list), count, p_copy);   \
        if (result.failed) {                                                           \
            ERROR("Failed to push data (count: %zu) to front into array list", count); \
        }                                                                              \
        p_list = (typeof(p_list))result.p_data;                                        \
    })

#define push_array_list(p_list, ...)                                              \
    ({                                                                            \
        typeof(*p_list) array_list_tmp_data[] = {__VA_ARGS__};                    \
        push_array_list_copy(p_list, COMPILE_TIME_GET_VA_ARGS_COUNT(__VA_ARGS__), \
                             array_list_tmp_data);                                \
    })

#define push_front_array_list(p_list, ...)                                              \
    ({                                                                                  \
        typeof(*p_list) array_list_tmp_data[] = {__VA_ARGS__};                          \
        push_front_array_list_copy(p_list, COMPILE_TIME_GET_VA_ARGS_COUNT(__VA_ARGS__), \
                                   array_list_tmp_data);                                \
    })

#ifdef __cplusplus
}
#endif
#endif
