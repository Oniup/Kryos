/// ------------------------------------------------------------------------ ///
/// This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) ///
/// @file dyarray.h                                                          ///
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

#ifndef KRYOS__TOOLS__DYARRAY_H
#define KRYOS__TOOLS__DYARRAY_H
#ifdef __cplusplus
extern "C" {
#endif

#include "kryos-tools/debug.h"
#include "kryos-tools/defines.h"

typedef enum DYARRAY_insert_type {
    DYARRAY_INSERT_TYPE_FRONT,
    DYARRAY_INSERT_TYPE_BACK,
    DYARRAY_INSERT_TYPE_ANY,
} DYARRAY_insert_type_t;

typedef struct dyarray_result {
    b8 failed;
    void* p_dyarray;
} dyarray_result_t;

KRYAPI void destroy_dyarray(void* p_dyarray);

KRYAPI dyarray_result_t intl_create_dyarray(usize type_size, usize count);

KRYAPI usize intl_get_dyarray_size(void* p_dyarray, usize type_size);
KRYAPI usize intl_get_dyarray_capacity(void* p_dyarray, usize type_size);

KRYAPI dyarray_result_t intl_resize_dyarray(void* p_dyarray, usize type_size, usize count);
KRYAPI dyarray_result_t intl_resize_dyarray_capacity(void* p_dyarray, usize type_size,
                                                     usize capacity_count);

KRYAPI dyarray_result_t intl_push_dyarray_data(void* p_dyarray, usize type_size,
                                               DYARRAY_insert_type_t insert_type, usize count,
                                               usize pos, void* p_data);

KRYAPI dyarray_result_t intl_push_dyarray_data_back(void* p_dyarray, usize size, void* p_data);
KRYAPI dyarray_result_t intl_push_dyarray_data_front(void* p_dyarray, usize size, void* p_data);
KRYAPI dyarray_result_t intl_insert_dyarray_data(void* p_dyarray, usize position, usize size,
                                                 void* p_data);

#define DYARRAY(T) T*

#define EMPTY_DYARRAY                      \
    (dyarray_result_t) {                   \
        .passed = false, .p_dyarray = NULL \
    }

#define create_dyarray(T, count)                                      \
    ({                                                                \
        DYARRAY_result_t res = intl_create_dyarray(sizeof(T), count); \
        if (res.err_msg == NULL) {                                    \
            ERROR("Failed to create dynamic list: %s", res.err_msg);  \
        }                                                             \
        res.p_dyarray;                                                \
    })

#define get_dyarray_size(p_dyarray) intl_get_dyarray_size(p_dyarray, sizeof(*p_dyarray))

#define push_copy_dyarray_data(p_dyarray, p_data) \
    intl_push_dyarray_data(p_dyarray, sizeof(*p_dyarray), DYARRAY_INSERT_TYPE_BACK, 1, 0, p_data)

#define push_copy_dyarray_array(p_dyarray, p_array, count)                                    \
    intl_push_dyarray_data(p_dyarray, sizeof(*p_dyarray), DYARRAY_INSERT_TYPE_BACK, count, 0, \
                           p_array)

#define insert_copy_dyarray_data(p_dyarray, p_data, position)                                   \
    intl_push_dyarray_data(p_dyarray, sizeof(*p_dyarray), DYARRAY_INSERT_TYPE_ANY, 1, position, \
                           p_data)

#define insert_copy_dyarray_array(p_dyarray, p_array, count, position)                    \
    intl_push_dyarray_data(p_dyarray, sizeof(*p_dyarray), DYARRAY_INSERT_TYPE_ANY, count, \
                           position, p_array)

#define push_dyarray_data(p_dyarray, data)     \
    ({                                         \
        typeof(p_dyarray) tmp = data;          \
        push_copy_dyarray_data(p_dyarray, tmp) \
    })

#define push_dyarray_array(p_dyarray, array)     \
    ({                                           \
        typeof(p_dyarray) tmp = array;           \
        push_copy_dyarray_data(p_dyarray, array) \
    })

#define insert_dyarray_data(p_dyarray, p_data, position)

#define insert_dyarray_array(p_dyarray, p_array, position)

#ifdef __cplusplus
}
#endif
#endif
