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
    ARRAY_LIST(int) tmp = create_array_list(int);
    usize size = get_array_list_size(tmp);
    IS_EQUALS(size, 0, "Empty array list size isn't correct");
    usize capacity = get_array_list_capacity(tmp);
    IS_EQUALS(capacity, ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT,
              "Empty array list capacity isn't correct");
    destroy_array_list(tmp);
}

void create_uninitialized_list(test_output_t* p_out) {
    ARRAY_LIST(int) tmp = create_array_list_uninitialized(int, 10);
    usize size = get_array_list_size(tmp);
    IS_EQUALS(size, 0, "Empty array list size isn't correct");
    usize capacity = get_array_list_capacity(tmp);
    IS_EQUALS(capacity, 10, "Empty array list capacity isn't correct");
    destroy_array_list(tmp);
}

void push_data_back(test_output_t* p_out) {
    ARRAY_LIST(int) array_list = create_array_list(int);
    for (usize i = 0; i < ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT + 1; i++) {
        int* tmp = push_array_list(array_list, i + 1);
        CHECK_IF(tmp != NULL, "Pushing data to back at index %zu resulted in array list of NULL",
                 i);
    }
    usize size = get_array_list_size(array_list);
    usize capacity = get_array_list_capacity(array_list);
    IS_EQUALS(size, ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT + 1,
              "Array list size isn't correct (%zu), should be %zu", size,
              ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT + 1);
    IS_EQUALS(capacity, ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT * 2,
              "Array list capacity isn't correct (%zu), should be %zu", capacity,
              ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT * 2);
    for (usize i = 0; i < size; i++) {
        IS_EQUALS(array_list[i], i + 1, "Array list element isn't correct value");
    }
    destroy_array_list(array_list);
}

void push_data_front(test_output_t* p_out) {
    ARRAY_LIST(int) array_list = create_array_list(int);
    usize target_size = ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT * 2 + 1;
    for (usize i = 0; i < target_size; i++) {
        int* tmp = push_front_array_list(array_list, i + 1);
        CHECK_IF(tmp != NULL, "Pushing data to front at index %zu resulted in array list of NULL",
                 i);
    }
    usize size = get_array_list_size(array_list);
    usize capacity = get_array_list_capacity(array_list);
    IS_EQUALS(size, target_size, "Array list size isn't correct (%zu), should be %zu", size,
              target_size);
    IS_EQUALS(capacity, ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT * 3,
              "Array list capacity isn't correct (%zu), should be %zu", capacity,
              ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT * 3);
    usize value = size;
    for (usize i = 0; i < size; i++) {
        IS_EQUALS(array_list[i], value,
                  "Array list element isn't correct value(%zu), should be %zu", array_list[i],
                  value);
        value -= 1;
    }
    destroy_array_list(array_list);
}

void insert_data(test_output_t* p_out) {
    ARRAY_LIST(int) array_list = create_array_list(int);
    destroy_array_list(array_list);
}

void push_array_back(test_output_t* p_out) {
    ARRAY_LIST(int) array_list = create_array_list(int);
    push_array_list(array_list, 1, 2, 3, 4, 5);
    push_array_list(array_list, 1, 2, 3, 4, 5);
    push_array_list(array_list, 1, 2, 3, 4, 5);
    usize size = get_array_list_size(array_list);
    IS_EQUALS(size, 15, "Empty array list size isn't correct");
    usize capacity = get_array_list_capacity(array_list);
    IS_EQUALS(capacity, ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT,
              "Empty array list capacity isn't correct");
    int value = 1;
    for (usize i = 0; i < size; i++) {
        if (i % 5 == 0) {
            value = 1;
        }
        IS_EQUALS(array_list[i], value, "Incorect value at index %zu", i);
        value++;
    }
    destroy_array_list(array_list);
}

void push_array_front(test_output_t* p_out) {
    ARRAY_LIST(int) array_list = create_array_list(int);
    push_front_array_list(array_list, 1, 2, 3, 4, 5);
    push_front_array_list(array_list, 1, 2, 3, 4, 5);
    push_front_array_list(array_list, 1, 2, 3, 4, 5);
    usize size = get_array_list_size(array_list);
    IS_EQUALS(size, 15, "Empty array list size isn't correct");
    usize capacity = get_array_list_capacity(array_list);
    IS_EQUALS(capacity, ARRAY_LIST_DEFAULT_CAPACITY_INCREASE_COUNT,
              "Empty array list capacity isn't correct");
    int value = 1;
    for (usize i = 0; i < size; i++) {
        if (i % 5 == 0) {
            value = 1;
        }
        IS_EQUALS(array_list[i], value, "Incorect value at index %zu", i);
        value++;
    }
    destroy_array_list(array_list);
}

void insert_array(test_output_t* p_out) {
    ARRAY_LIST(int) array_list = create_array_list(int);
    destroy_array_list(array_list);
}

void array_list_tests() {
    TEST_TABLE() {
        ADD_TEST(create_empty_instance), ADD_TEST(create_uninitialized_list),
        ADD_TEST(push_data_back),        ADD_TEST(push_data_front),
        ADD_TEST(insert_data),           ADD_TEST(push_array_back),
        ADD_TEST(push_array_front),      ADD_TEST(insert_array),
    };
    EXECUTE_TEST_TABLE("Array List");
}
