/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file array_list.cpp                                                     *
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

// void destroy_array_list(void* p_list) {
//     destroy_dynamic_allocation(p_list);
// }
//
// usize _kint_get_array_list_size(void* p_list, usize type_size) {
//     usize size = get_dynamic_allocation_size(p_list);
//     if (size > 0) {
//         size = size / type_size;
//     }
//     return size;
// }
//
// usize _kint_get_array_list_capacity(void* p_list, usize type_size) {
//     usize capacity = get_dynamic_allocation_capacity(p_list);
//     if (capacity > 0) {
//         capacity = capacity / type_size;
//     }
//     return capacity;
// }
//
// _kint_array_list_result_t _kint_create_array_list_with_capacity(usize type_size, usize count) {
//     allocated_memory_result_t result = create_dynamic_allocation(type_size * count);
//     if (result.error_message != NO_ERROR_MESSAGE) {
//         ERROR(
//             "Failed to create uninitialized array list of size %zu, type_size: %zu, count: %zu: %s",
//             type_size * count, type_size, count, result.error_message);
//         return (_kint_array_list_result_t) {.failed = true, .p_data = nullptr};
//     }
//     void* p_data = result.p_data;
//     set_dynamic_allocation_size(p_data, 0);
//     return (_kint_array_list_result_t) {.failed = false, .p_data = p_data};
// }
//
// _kint_array_list_result_t _kint_resize_array_list_size(void* p_list, usize type_size, usize count) {
//     usize capacity = get_dynamic_allocation_capacity(p_list);
//     usize new_size = get_dynamic_allocation_size(p_list) + type_size * count;
//     if (new_size > capacity) {
//         _kint_array_list_result_t result =
//             _kint_resize_array_list_capacity(p_list, type_size, count);
//         if (result.failed) {
//             return result;
//         }
//         p_list = result.p_data;
//     }
//     bool result = set_dynamic_allocation_size(p_list, new_size);
//     if (!result) {
//         ERROR("Failed to resize array list to %zu, type_size: %zu, count: %zu", type_size * count,
//               type_size, count);
//         return (_kint_array_list_result_t) {.failed = true, .p_data = p_list};
//     }
//     return (_kint_array_list_result_t) {.failed = false, .p_data = p_list};
// }
//
// _kint_array_list_result_t _kint_resize_array_list_capacity(void* p_list, usize type_size,
//                                                            usize count) {
//     usize capacity_increase =
//         (usize)ceil((f64)(type_size * count) / (f64)ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT);
//     allocated_memory_result_t result = resize_dynamic_allocation_capacity(
//         p_list, get_dynamic_allocation_capacity(p_list) +
//                     capacity_increase * (type_size * ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT));
//     if (result.error_message != NO_ERROR_MESSAGE) {
//         ERROR("Failed to resize array list capacity to %zu, type_size: %zu, count: %zu",
//               type_size * count, type_size, count);
//         return (_kint_array_list_result_t) {.failed = true, .p_data = p_list};
//     }
//     p_list = result.p_data;
//     return (_kint_array_list_result_t) {.failed = false, .p_data = p_list};
// }
//
// _kint_array_list_result_t _kint_push_array_list_data_back(void* p_list, usize type_size,
//                                                           usize count, void* p_data) {
//     if (p_list == nullptr) {
//         ERROR("Cannot push data into the back of an empty array list. Type size: %zu, count: %zu "
//               "of `p_data`");
//         return (_kint_array_list_result_t) {.failed = true, .p_data = nullptr};
//     }
//     usize old_size = _kint_get_array_list_size(p_list, type_size);
//     _kint_array_list_result_t result = _kint_resize_array_list_size(p_list, type_size, count);
//     if (result.failed) {
//         return result;
//     }
//     p_list = result.p_data;
//     usize size = _kint_get_array_list_size(p_list, type_size);
//     if (size == 0) {
//         return (_kint_array_list_result_t) {.failed = true, .p_data = p_list};
//     }
//     usize p_data_size = type_size * count;
//     bool copy_result = memcpy((char*)p_list + type_size * old_size, p_data, p_data_size) != nullptr;
//     if (!copy_result) {
//         ERROR("Failed to memcopy data to the back of the array list");
//         return (_kint_array_list_result_t) {.failed = true, .p_data = p_list};
//     }
//     return (_kint_array_list_result_t) {.failed = false, .p_data = p_list};
// }
//
// _kint_array_list_result_t _kint_push_array_list_data_front(void* p_list, usize type_size,
//                                                            usize count, void* p_data) {
//     if (p_list == nullptr) {
//         ERROR("Cannot push data into the front of an empty array list. Type size: %zu, count: "
//               "%zu of `p_data`",
//               type_size, count);
//         return (_kint_array_list_result_t) {.failed = true, .p_data = nullptr};
//     }
//     usize old_size = _kint_get_array_list_size(p_list, type_size);
//     _kint_array_list_result_t result = _kint_resize_array_list_size(p_list, type_size, count);
//     if (result.failed) {
//         return result;
//     }
//     p_list = result.p_data;
//     usize size = _kint_get_array_list_size(p_list, type_size);
//     if (size == 0) {
//         return (_kint_array_list_result_t) {.failed = true, .p_data = p_list};
//     }
//     usize data_size = type_size * count;
//     // Shift old data over
//     bool copy_result = memcpy((char*)p_list + data_size, p_list, old_size * type_size) != nullptr;
//     if (!copy_result) {
//         ERROR("Failed to shift original array list data over to make room for the new data at "
//               "front: memcpy failed");
//         return (_kint_array_list_result_t) {.failed = true, .p_data = p_list};
//     }
//     // Copy New Data
//     copy_result = memcpy(p_list, p_data, data_size) != nullptr;
//     if (!copy_result) {
//         ERROR("Failed to copy new data into free space at front of array list: memcpy failed");
//         return (_kint_array_list_result_t) {.failed = true, .p_data = p_list};
//     }
//     return (_kint_array_list_result_t) {.failed = false, .p_data = p_list};
// }
//
// _kint_array_list_result_t _kint_insert_array_list(void* p_list, usize type_size, usize position,
//                                                   usize count, void* p_data) {
//     if (p_list == nullptr) {
//         ERROR("Cannot insert data into position %zu of an empty array list. Type size: %zu, count: "
//               "%zu of `p_data`",
//               position, type_size, count);
//         return (_kint_array_list_result_t) {.failed = true, .p_data = nullptr};
//     }
//     usize old_size = get_dynamic_allocation_size(p_list);
//     usize insert_size = count * type_size;
//     _kint_array_list_result_t result = _kint_resize_array_list_size(p_list, type_size, count);
//     if (result.failed) {
//         return result;
//     }
//     p_list = result.p_data;
//     usize offset = position * type_size;
//     // Shift data to make room for insert
//     bool copy_result = memcpy((char*)p_list + offset + insert_size, (char*)p_list + offset,
//                               old_size - offset) != nullptr;
//     if (!copy_result) {
//         ERROR("Failed to insert data into array list: memcpy failed to copy and shift data over "
//               "to make room for insert");
//         return (_kint_array_list_result_t) {.failed = true, .p_data = p_list};
//     }
//     copy_result = memcpy((char*)p_list + offset, p_data, insert_size) != nullptr;
//     if (!copy_result) {
//         ERROR("Failed to insert data into array list: memcpy failed copy insert data into "
//               "required space allocated");
//         return (_kint_array_list_result_t) {.failed = true, .p_data = p_list};
//     }
//     return (_kint_array_list_result_t) {.failed = false, .p_data = p_list};
// }
//
// _kint_array_list_result_t _kint_pop_array_list_back(void* p_list, usize type_size, usize count) {
//     if (p_list == nullptr) {
//         ERROR("Cannot pop back %zu elements in array list: p_list is nullptr", count);
//         return (_kint_array_list_result_t) {.failed = true, .p_data = p_list};
//     }
//     usize size = get_dynamic_allocation_size(p_list);
//     usize popping_size = count * type_size;
//     bool result = set_dynamic_allocation_size(p_list, size - popping_size);
//     if (!result) {
//         ERROR("Failed to pop front %zu elements in array list: set dynamic allocation size failed",
//               count);
//         return (_kint_array_list_result_t) {.failed = true, .p_data = p_list};
//     }
//     return (_kint_array_list_result_t) {.failed = false, .p_data = p_list};
// }
//
// _kint_array_list_result_t _kint_pop_array_list_front(void* p_list, usize type_size, usize count) {
//     if (p_list == nullptr) {
//         ERROR("Cannot pop front %zu elements in array list, array list is nullptr", count);
//         return (_kint_array_list_result_t) {.failed = true, .p_data = p_list};
//     }
//     usize size = get_dynamic_allocation_size(p_list);
//     usize popping_size = count * type_size;
//     usize new_size = size - popping_size;
//     bool copy_result = memcpy(p_list, (char*)p_list + popping_size, new_size) != nullptr;
//     if (!copy_result) {
//         ERROR("Failed to pop front %zu elements in array list: memcpy_s failed to copy data to "
//               "front of array list to override the popped",
//               count);
//         return (_kint_array_list_result_t) {.failed = true, .p_data = p_list};
//     }
//     bool result = set_dynamic_allocation_size(p_list, new_size);
//     if (!result) {
//         ERROR("Failed to pop front %zu elements in array list: set dynamic allocation size failed",
//               count);
//         return (_kint_array_list_result_t) {.failed = true, .p_data = p_list};
//     }
//     return (_kint_array_list_result_t) {.failed = false, .p_data = p_list};
// }
//
// _kint_array_list_result_t _kint_pop_array_list_at(void* p_list, usize type_size, usize position,
//                                                   usize count) {
//     if (p_list == nullptr) {
//         ERROR("Cannot pop %zu elements in array list at position %zu: array list is nullptr", count,
//               position);
//         return (_kint_array_list_result_t) {.failed = true, .p_data = p_list};
//     }
//     usize old_size = get_dynamic_allocation_size(p_list);
//     usize popping_size = count * type_size;
//     usize new_size = old_size - popping_size;
//     usize offset = position * type_size;
//     if (count + position > old_size) {
//         ERROR("Cannot pop %zu elements in array list at position %zu: count + position(%zu) = %zu "
//               "is greater than the size of the array list %zu",
//               count, position, count + position, old_size / type_size);
//         return (_kint_array_list_result_t) {.failed = true, .p_data = p_list};
//     }
//     bool result = memcpy((char*)p_list + offset, (char*)p_list + offset + popping_size,
//                          popping_size) != nullptr;
//     if (!result) {
//         ERROR("Cannot pop %zu elements in array list at position %zu: memcpy_s failed to copy data "
//               "after popping data into removed position to setup resize array list buffer",
//               count, position);
//         return (_kint_array_list_result_t) {.failed = true, .p_data = p_list};
//     }
//     bool resize_success = set_dynamic_allocation_size(p_list, new_size);
//     if (!resize_success) {
//         ERROR("Cannot pop %zu elements in array list at position %zu: Failed to resize array list "
//               "size",
//               count, position);
//         return (_kint_array_list_result_t) {.failed = true, .p_data = p_list};
//     }
//     return (_kint_array_list_result_t) {.failed = false, .p_data = p_list};
// }
