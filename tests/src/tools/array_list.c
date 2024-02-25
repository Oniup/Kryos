/// ------------------------------------------------------------------------ ///
/// This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) ///
/// @file array_list.c                                                       ///
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

#include "kryos-tests/tools/array_list.h"
#include "kryos-tests/framework.h"
#include <kryos-tools/containers/array_list.h>

void create_empty_instance(test_output_t* p_out) {
    ARRAY_LIST(i32) p_list = create_array_list(i32);
    usize size = get_array_list_size(p_list);
    IS_EQUALS(size, 0, "Empty array list size isn't correct");
    usize capacity = get_array_list_capacity(p_list);
    IS_EQUALS(capacity, ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT,
              "Empty array list capacity isn't correct");
    destroy_array_list(p_list);
}

void create_with_specified_capacity(test_output_t* p_out) {
    ARRAY_LIST(i32) p_list = create_array_list_with_capacity(i32, 10);
    usize size = get_array_list_size(p_list);
    IS_EQUALS(size, 0, "Array list size isn't correct");
    usize capacity = get_array_list_capacity(p_list);
    IS_EQUALS(capacity, 10, "Array list capacity isn't correct");
    destroy_array_list(p_list);
}

void push_data_back(test_output_t* p_out) {
    ARRAY_LIST(i32) p_list = create_array_list(i32);
    for (usize i = 0; i < ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT + 1; i++) {
        i32* tmp = push_array_list(p_list, i + 1);
        CHECK_IF(tmp != NULL, "Pushing data to back at index %zu resulted in array list of NULL",
                 i);
    }
    usize size = get_array_list_size(p_list);
    usize capacity = get_array_list_capacity(p_list);
    IS_EQUALS(size, ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT + 1,
              "Array list size isn't correct (%zu), should be %zu", size,
              ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT + 1);
    IS_EQUALS(capacity, ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT * 2,
              "Array list capacity isn't correct (%zu), should be %zu", capacity,
              ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT * 2);
    for (usize i = 0; i < size; i++) {
        IS_EQUALS(p_list[i], i + 1, "Array list element isn't correct value");
    }
    destroy_array_list(p_list);
}

void push_data_front(test_output_t* p_out) {
    ARRAY_LIST(i32) p_list = create_array_list(i32);
    usize target_size = ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT * 2 + 1;
    for (usize i = 0; i < target_size; i++) {
        i32* tmp = push_front_array_list(p_list, i + 1);
        CHECK_IF(tmp != NULL, "Pushing data to front at index %zu resulted in array list of NULL",
                 i);
    }
    usize size = get_array_list_size(p_list);
    usize capacity = get_array_list_capacity(p_list);
    IS_EQUALS(size, target_size, "Array list size isn't correct (%zu), should be %zu", size,
              target_size);
    IS_EQUALS(capacity, ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT * 3,
              "Array list capacity isn't correct (%zu), should be %zu", capacity,
              ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT * 3);
    usize value = size;
    for (usize i = 0; i < size; i++) {
        IS_EQUALS(p_list[i], value, "Array list element isn't correct value(%zu), should be %zu",
                  p_list[i], value);
        value -= 1;
    }
    destroy_array_list(p_list);
}

void insert_data(test_output_t* p_out) {
}

void push_array_back(test_output_t* p_out) {
    ARRAY_LIST(i32) array_list = create_array_list(i32);
    push_array_list(array_list, 1, 2, 3, 4, 5);
    push_array_list(array_list, 1, 2, 3, 4, 5);
    push_array_list(array_list, 1, 2, 3, 4, 5);
    usize size = get_array_list_size(array_list);
    IS_EQUALS(size, 15, "Array list size isn't correct");
    usize capacity = get_array_list_capacity(array_list);
    IS_EQUALS(capacity, ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT,
              "Array list capacity isn't correct");
    i32 value = 1;
    for (usize i = 0; i < size; i++) {
        if (i % 5 == 0) {
            value = 1;
        }
        IS_EQUALS(array_list[i], value, "Incorrect value at index %zu", i);
        value++;
    }
    destroy_array_list(array_list);
}

void push_array_front(test_output_t* p_out) {
    ARRAY_LIST(i32) p_list = create_array_list(i32);
    push_front_array_list(p_list, 1, 2, 3, 4, 5);
    push_front_array_list(p_list, 1, 2, 3, 4, 5);
    push_front_array_list(p_list, 1, 2, 3, 4, 5);
    usize size = get_array_list_size(p_list);
    IS_EQUALS(size, 15, "Array list size isn't correct");
    usize capacity = get_array_list_capacity(p_list);
    IS_EQUALS(capacity, ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT,
              "Array list capacity isn't correct");
    i32 value = 1;
    for (usize i = 0; i < size; i++) {
        if (i % 5 == 0) {
            value = 1;
        }
        IS_EQUALS(p_list[i], value, "Incorect value at index %zu", i);
        value++;
    }
    destroy_array_list(p_list);
}

void insert_array(test_output_t* p_out) {
    ARRAY_LIST(i32) p_list = create_array_list(i32);
    push_array_list(p_list, 1, 2, 3, 4, 5);
    usize size = get_array_list_size(p_list);
    IS_EQUALS(size, 5, "Empty array list size isn't correct");
    usize capacity = get_array_list_capacity(p_list);
    IS_EQUALS(capacity, ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT,
              "Empty array list capacity isn't correct");
    for (usize i = 0; i < size; i++) {
        IS_EQUALS(p_list[i], i + 1, "Incorrect value at index %zu", i);
    }
    insert_array_list(p_list, 3, 10, 11, 12);
    size = get_array_list_size(p_list);
    IS_EQUALS(size, 8, "Array list size isn't correct, should be 8 not %zu", size);
    capacity = get_array_list_capacity(p_list);
    IS_EQUALS(capacity, ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT,
              "Array list capacity isn't correct, should be %zu, not %zu",
              ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT, capacity);
    i32 j = 1;
    i32 k = 10;
    for (usize i = 0; i < size; i++) {
        if (i > 2 && i < 6) {
            IS_EQUALS(p_list[i], k, "Incorrect value at index %zu", i);
            k++;
        } else {
            IS_EQUALS(p_list[i], j, "Incorrect value at index %zu", i);
            j++;
        }
    }
    destroy_array_list(p_list);
}

void array_list_tests() {
    TEST_TABLE() {
        ADD_TEST(create_empty_instance), ADD_TEST(create_with_specified_capacity),
        ADD_TEST(push_data_back),        ADD_TEST(push_data_front),
        ADD_TEST(insert_data),           ADD_TEST(push_array_back),
        ADD_TEST(push_array_front),      ADD_TEST(insert_array),
    };
    EXECUTE_TEST_TABLE("Array List");
}
