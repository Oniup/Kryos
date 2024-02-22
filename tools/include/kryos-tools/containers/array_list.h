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

typedef enum array_list_insert_type {
    ARRAY_LIST_INSERT_TYPE_FRONT,
    ARRAY_LIST_INSERT_TYPE_BACK,
    ARRAY_LIST_INSERT_TYPE_ANY,
} array_list_insert_type_t;

typedef struct array_list {
    b8 failed;
    void* p_array;
} array_list_result_t;

KRYAPI void destroy_array_list(void* p_list);

KRYAPI array_list_result_t intl_create_array_list(usize type_size, usize count);

KRYAPI usize intl_get_array_list_size(void* p_list, usize type_size);
KRYAPI usize intl_get_array_list_capacity(void* p_list, usize type_size);

KRYAPI array_list_result_t intl_resize_array_list(void* p_list, usize type_size, usize count);
KRYAPI array_list_result_t intl_resize_array_list_capacity(void* p_list, usize type_size,
                                                           usize capacity_count);

KRYAPI array_list_result_t intl_push_array_list_data(void* p_list, usize type_size,
                                                     array_list_insert_type_t insert_type,
                                                     usize count, usize pos, void* p_data);

KRYAPI array_list_result_t intl_push_array_list_data_back(void* p_list, usize size, void* p_data);
KRYAPI array_list_result_t intl_push_array_list_data_front(void* p_list, usize size, void* p_data);
KRYAPI array_list_result_t intl_insert_array_list_data(void* p_list, usize position, usize size,
                                                       void* p_data);

#define ARRAY_LIST(T) T*

#define EMPTY_ARRAY_LIST                \
    (array_list_result_t) {             \
        .passed = false, .p_list = NULL \
    }

#define create_empty_array_list(T)                                         \
    ({                                                                     \
        array_list_result_t result = intl_create_array_list(sizeof(T), 0); \
        if (result.failed) {                                               \
            ERROR("Failed to create empty array list");                    \
        }                                                                  \
        (T*)result.p_array;                                                \
    })

#define create_array_list(T, count)                                            \
    ({                                                                         \
        array_list_result_t result = intl_create_array_list(sizeof(T), count); \
        if (result.failed) {                                                   \
            ERROR("Failed to create array list");                              \
        }                                                                      \
        (T*)result.p_array;                                                    \
    })

#define get_array_list_size(p_list) intl_get_array_list_size(p_list, sizeof(*p_list))
#define get_array_list_capacity(p_list) intl_get_array_list_capacity(p_list, sizeof(*p_list))

#define push_copy_array_list_data(p_list, p_data) \
    intl_push_array_list_data(p_list, sizeof(*p_list), ARRAY_LIST_INSERT_TYPE_BACK, 1, 0, p_data)

#define push_copy_array_list_array(p_list, p_array, count)                                    \
    intl_push_array_list_data(p_list, sizeof(*p_list), ARRAY_LIST_INSERT_TYPE_BACK, count, 0, \
                              p_array)

#define insert_copy_array_list_data(p_list, p_data, position)                                   \
    intl_push_array_list_data(p_list, sizeof(*p_list), ARRAY_LIST_INSERT_TYPE_ANY, 1, position, \
                              p_data)

#define insert_copy_array_list_array(p_list, p_array, count, position)                    \
    intl_push_array_list_data(p_list, sizeof(*p_list), ARRAY_LIST_INSERT_TYPE_ANY, count, \
                              position, p_array)

#define push_array_list_data(p_list, data)            \
    ({                                                \
        typeof(*p_list) intl_tmp = data;              \
        push_copy_array_list_data(p_list, &intl_tmp); \
    })

#define push_array_list_array(p_list, array)          \
    ({                                                \
        typeof(*p_list) intl_tmp = array;             \
        push_copy_array_list_data(p_list, &intl_tmp); \
    })

#define insert_array_list_data(p_list, p_data, position)

#define insert_array_list_array(p_list, p_array, position)

#ifdef __cplusplus
}
#endif
#endif
