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

typedef struct _kint_array_list_result {
    b8 failed;
    void* p_data;
} _kint_array_list_result_t;

/// @brief Releases memory allocated back to the OS.
///
/// @warning If data type has heap allocated memory, you'll need to deal with that before popping,
/// otherwise there will be a memory leak.
///
/// @param `p_list` Target array list to destroy.
void destroy_array_list(void* p_list);

/// @brief Get the number of elements within the array list.
///
/// @param `p_list` Array list to get length.
/// @param `type_size` Size of the array list type in bytes.
///
/// @return The size/length of the array list.
usize _kint_get_array_list_size(void* p_list, usize type_size);

/// @brief Get the max space available for new elements that doesn't require a heap allocation call.
///
/// @param `p_list` Array list to get length.
/// @param `type_size` Size of the array list type in bytes.
///
/// @return Max buffer size.
usize _kint_get_array_list_capacity(void* p_list, usize type_size);

/// @brief Creates an empty array with a given capacity size.
///
/// @param `type_size` Size of the array list type in bytes.
/// @param `count` Number of new instances required to fit in the new capacity (adds the current
/// capacity size to this new size for the total size).
///
/// @return Result struct determining whether the function failed and a pointer to the array list as
/// a `void*`.
_kint_array_list_result_t _kint_create_array_list_with_capacity(usize type_size, usize count);

/// @brief Resizes size of the array list. If the size exceeds the capacity, will also resize the
/// capacity by intervals of the `ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT` * type_size.
///
/// @param `p_list` Array list instance. Cannot be a NULL value otherwise will fail.
/// @param `type_size` Size of the array list type in bytes.
/// @param `count` Number of new instances required to fit in the new capacity (adds the current
/// capacity size to this new size for the total size).
///
/// @return Result struct determining whether the function failed and a pointer to the array list as
/// a `void*`.
_kint_array_list_result_t _kint_resize_array_list_size(void* p_list, usize type_size, usize count);

/// @brief Resizes capacity by intervals of the `ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT` *
/// `type_size`.
///
/// @param `p_list` Array list instance. Cannot be a NULL value otherwise will fail.
/// @param `type_size` Size of the array list type in bytes.
/// @param `count` Number of new instances required to fit in the new capacity (adds the current
/// capacity size to this new size for the total size).
///
/// @return Result struct determining whether the function failed and a pointer to the array list as
/// a `void*`.
_kint_array_list_result_t _kint_resize_array_list_capacity(void* p_list, usize type_size,
                                                           usize count);

/// @brief Copies the given data into the back of array list.
///
/// @param `p_list` Array list instance. Cannot be a NULL value otherwise will fail.
/// @param `type_size` Size of the array list type in bytes.
/// @param `count` Number of new instances required to fit in the new capacity (adds the current
/// capacity size to this new size for the total size).
/// @param `p_data` Pointer to data for copying. Must be the same type as the array list
///
/// @return Result struct determining whether the function failed and a pointer to the array list as
/// a `void*`.
_kint_array_list_result_t _kint_push_array_list_data_back(void* p_list, usize type_size,
                                                          usize count, void* p_data);

/// @brief Copies the given data into the front of array list and shifts the original data down the
/// buffer by the size of the insert data.
///
/// @param `p_list` Array list instance. Cannot be a NULL value otherwise will fail.
/// @param `type_size` Size of the array list type in bytes.
/// @param `count` Number of new instances required to fit in the new capacity (adds the current
/// capacity size to this new size for the total size).
/// @param `p_data` Pointer to data for copying. Must be the same type as the array list
///
/// @return Result struct determining whether the function failed and a pointer to the array list as
/// a `void*`.
_kint_array_list_result_t _kint_push_array_list_data_front(void* p_list, usize type_size,
                                                           usize count, void* p_data);

/// @brief Inserts the given data into the specified position of array list. It inserts space of
/// size same to the insert data, the copies it to that new space.
///
/// @param `p_list` Array list instance. Cannot be a NULL value otherwise will fail.
/// @param `type_size` Size of the array list type in bytes.
/// @param `position` Specifics where to insert the data into the array list.
/// @param `count` Number of new instances required to fit in the new capacity (adds the current
/// capacity size to this new size for the total size).
/// @param `p_data` Pointer to data for copying. Must be the same type as the array list
///
/// @return Result struct determining whether the function failed and a pointer to the array list as
/// a `void*`.
_kint_array_list_result_t _kint_insert_array_list(void* p_list, usize type_size, usize position,
                                                  usize count, void* p_data);

/// @brief Removes the given number of elements from the back of the array list.
///
/// @warning If data type has heap allocated memory, you'll need to deal with that before popping,
/// otherwise there will be a memory leak.
///
/// @param `p_list` Array list instance. Cannot be a NULL value otherwise will fail.
/// @param `type_size` Size of the array list type in bytes.
/// @param `count` Number of elements to be removed.
///
/// @return Result struct determining whether the function failed and a pointer to the array list as
/// a `void*`.
_kint_array_list_result_t _kint_pop_array_list_back(void* p_list, usize type_size, usize count);

/// @brief Removes the given number of elements from the front of the array list.
///
/// @warning If data type has heap allocated memory, you'll need to deal with that before popping,
/// otherwise there will be a memory leak.
///
/// @param `p_list` Array list instance. Cannot be a NULL value otherwise will fail.
/// @param `type_size` Size of the array list type in bytes.
/// @param `count` Number of elements to be removed.
///
/// @return Result struct determining whether the function failed and a pointer to the array list as
/// a `void*`.
_kint_array_list_result_t _kint_pop_array_list_front(void* p_list, usize type_size, usize count);

/// @brief Removes the given number of elements starting at a target position/index of the array
/// list.
///
/// @warning If data type has heap allocated memory, you'll need to deal with that before popping,
/// otherwise there will be a memory leak.
///
/// @param `p_list` Array list instance. Cannot be a NULL value otherwise will fail.
/// @param `type_size` Size of the array list type in bytes.
/// @param `position` Start of the target popping elements.
/// @param `count` Number of elements to be removed.
///
/// @return Result struct determining whether the function failed and a pointer to the array list as
/// a `void*`.
_kint_array_list_result_t _kint_pop_array_list_at(void* p_list, usize type_size, usize position,
                                                  usize count);

#define ARRAY_LIST(T) T*

#define create_array_list_with_capacity(T, count)                    \
    ({                                                               \
        _kint_array_list_result_t result =                           \
            _kint_create_array_list_with_capacity(sizeof(T), count); \
        if (result.failed) {                                         \
            ERROR("Failed to create empty array list");              \
        }                                                            \
        result.p_data;                                               \
    })

#define create_array_list(T) \
    create_array_list_with_capacity(T, ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT)

/// @brief Get the number of elements within the array list.
///
/// @param `p_list` Array list to get length.
///
/// @return The size/length of the array list.
#define get_array_list_size(p_list) _kint_get_array_list_size(p_list, sizeof(*p_list))

/// @brief Get the max space available for new elements that doesn't require a heap allocation call.
///
/// @param `p_list` Array list to get length.
///
/// @return Max buffer size.
#define get_array_list_capacity(p_list) _kint_get_array_list_capacity(p_list, sizeof(*p_list))

/// @brief Copies the given data into the back of array list.
///
/// @param `p_list` Array list instance. Cannot be a NULL value otherwise will fail.
/// @param `count` Number of new instances required to fit in the new capacity (adds the current
/// capacity size to this new size for the total size).
/// @param `p_copy` Data for copying. Must be the same type as the array list
#define push_array_list_copy(p_list, count, p_copy)                                  \
    ({                                                                               \
        _kint_array_list_result_t result =                                           \
            _kint_push_array_list_data_back(p_list, sizeof(*p_list), count, p_copy); \
        if (result.failed) {                                                         \
            ERROR("Failed to push data (count: %zu) into array list", count);        \
        }                                                                            \
        p_list = (typeof(p_list))result.p_data;                                      \
    })

/// @brief Copies the given data into the front of array list.
///
/// @param `p_list` Array list instance. Cannot be a NULL value otherwise will fail.
/// @param `count` Number of new instances required to fit in the new capacity (adds the current
/// capacity size to this new size for the total size).
/// @param `p_copy` Data for copying. Must be the same type as the array list
#define push_front_array_list_copy(p_list, count, p_copy)                              \
    ({                                                                                 \
        _kint_array_list_result_t result =                                             \
            _kint_push_array_list_data_front(p_list, sizeof(*p_list), count, p_copy);  \
        if (result.failed) {                                                           \
            ERROR("Failed to push data (count: %zu) to front into array list", count); \
        }                                                                              \
        p_list = (typeof(p_list))result.p_data;                                        \
    })

/// @brief Inserts the given data into the specified position of array list. It inserts space of
/// size same to the insert data, the copies it to that new space
///
/// @param `p_list` Array list instance. Cannot be a NULL value otherwise will fail.
/// @param `position` Specifics where to insert the data into the array list.
/// @param `count` Number of new instances required to fit in the new capacity (adds the current
/// capacity size to this new size for the total size).
/// @param `p_data` Data for copying. Must be the same type as the array list
#define insert_array_list_copy(p_list, position, count, p_copy)                           \
    ({                                                                                    \
        _kint_array_list_result_t result =                                                \
            _kint_insert_array_list(p_list, sizeof(*p_list), position, count, p_copy);    \
        if (result.failed) {                                                              \
            ERROR("Failed to insert data (count: %zu) to position (%zu) into array list", \
                  position, count);                                                       \
        }                                                                                 \
        p_list = (typeof(p_list))result.p_data;                                           \
    })

/// @brief Copies the given data into the back of array list.
///
/// @param `p_list` Array list instance. Cannot be a NULL value otherwise will fail.
#define push_array_list_back(p_list, ...)                                         \
    ({                                                                            \
        typeof(*p_list) _kint_data[] = {__VA_ARGS__};                             \
        push_array_list_copy(p_list, GET_VA_ARGS_COUNT(__VA_ARGS__), _kint_data); \
    })

/// @brief Copies the given data into the front of array list.
///
/// @param `p_list` Array list instance. Cannot be a NULL value otherwise will fail.
#define push_array_list_front(p_list, ...)                                              \
    ({                                                                                  \
        typeof(*p_list) _kint_data[] = {__VA_ARGS__};                                   \
        push_front_array_list_copy(p_list, GET_VA_ARGS_COUNT(__VA_ARGS__), _kint_data); \
    })

/// @brief Inserts the given data into the specified position of array list. It inserts space of
/// size same to the insert data, the copies it to that new space
///
/// @param `p_list` Array list instance. Cannot be a NULL value otherwise will fail.
/// @param `position` Specifics where to insert the data into the array list.
#define insert_array_list(p_list, position, ...)                                              \
    ({                                                                                        \
        typeof(*p_list) _kint_data[] = {__VA_ARGS__};                                         \
        insert_array_list_copy(p_list, position, GET_VA_ARGS_COUNT(__VA_ARGS__), _kint_data); \
    })

/// @brief Removes the given number of elements from the back of the array list.
///
/// @warning If data type has heap allocated memory, you'll need to deal with that before popping,
/// otherwise there will be a memory leak.
///
/// @param `p_list` Array list instance. Cannot be a NULL value otherwise will fail.
/// @param `count` Number of elements to be removed.
///
/// @return Result struct determining whether the function failed and a pointer to the array list as
/// a `void*`.
#define pop_array_list_back(p_list, count)                                 \
    ({                                                                     \
        _kint_array_list_result_t _kint_result =                           \
            _kint_pop_array_list_back(p_list, sizeof(*p_list), count);     \
        if (_kint_result.failed) {                                         \
            ERROR("Failed to pop back %zu elements in array list", count); \
        }                                                                  \
        p_list = (typeof(p_list))_kint_result.p_data;                      \
    })

/// @brief Removes the given number of elements from the front of the array list.
///
/// @warning If data type has heap allocated memory, you'll need to deal with that before popping,
/// otherwise there will be a memory leak.
///
/// @param `p_list` Array list instance. Cannot be a NULL value otherwise will fail.
/// @param `count` Number of elements to be removed.
///
/// @return Result struct determining whether the function failed and a pointer to the array list as
/// a `void*`.
#define pop_array_list_front(p_list, count)                                 \
    ({                                                                      \
        _kint_array_list_result_t _kint_result =                            \
            _kint_pop_array_list_front(p_list, sizeof(*p_list), count);     \
        if (_kint_result.failed) {                                          \
            ERROR("Failed to pop front %zu elements in array list", count); \
        }                                                                   \
        p_list = (typeof(p_list))_kint_result.p_data;                       \
    })

/// @brief Removes the given number of elements starting at a target position/index of the array
/// list.
///
/// @warning If data type has heap allocated memory, you'll need to deal with that before popping,
/// otherwise there will be a memory leak.
///
/// @param `p_list` Array list instance. Cannot be a NULL value otherwise will fail.
/// @param `position` Start of the target popping elements.
/// @param `count` Number of elements to be removed.
///
/// @return Result struct determining whether the function failed and a pointer to the array list as
/// a `void*`.
#define pop_array_list_at(p_list, position, count)                                               \
    ({                                                                                           \
        _kint_array_list_result_t _kint_result =                                                 \
            _kint_pop_array_list_at(p_list, sizeof(*p_list), position, count);                   \
        if (_kint_result.failed) {                                                               \
            ERROR("Failed to pop %zu elements at position %zu  in array list", count, position); \
        }                                                                                        \
        p_list = (typeof(p_list))_kint_result.p_data;                                            \
    })

#ifdef __cplusplus
}
#endif
#endif
