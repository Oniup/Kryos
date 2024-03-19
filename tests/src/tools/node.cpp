/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file node.cpp                                                             *
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

#include "kryos-tests/tools/containers.hpp"

#include "kryos-tests/framework.hpp"
#include "kryos-tools/containers/node.hpp"

void create(TestOutput& out) {
    i32* p_data = create_node(420);
    node_t* p_node = get_node(p_data);
    IS_EQUALS(*p_data, 420, "Value is incorrect");
    IS_EQUALS(p_node->p_next, NULL, "p_next node should be NULL");
    IS_EQUALS(p_node->p_previous, NULL, "p_previous node should be NULL");
    destroy_node(p_data);
}

void appendNext(TestOutput& out) {
    // i32* p_root = create_node(1);
    // i32* p_tail = append_nodes_next(p_root, 5, 2, 1, 7, 4, 6);
    // i32 correct_values[] = {1, 5, 2, 1, 7, 4, 6};
    // i32* p_current = p_root;
    // i32 i = 0;
    // while (p_current != NULL) {
    //     IS_EQUALS(*p_current, correct_values[i], "Incorrect value at node %d", i);
    //     p_current = get_node_next(p_current);
    //     i++;
    // }
    // destroy_nodes_right(p_root);
}

void appendPrevious(TestOutput& out) {
    // i32* p_root = create_node(1);
    // i32* p_tail = append_nodes_previous(p_root, 5, 2, 1, 7, 4, 6);
    // IS_EQUALS(get_node(p_root)->p_next, NULL, "Next from root should be NULL");
    // i32 correct_values[] = {1, 5, 2, 1, 7, 4, 6};
    // i32* p_current = p_root;
    // i32 i = 0;
    // while (p_current != NULL) {
    //     IS_EQUALS(*p_current, correct_values[i], "Incorrect value at node %d", i);
    //     p_current = get_node_previous(p_current);
    //     i++;
    // }
    // destroy_nodes_left(p_root);
}

namespace tools::containers {

void nodes() {
    TEST_TABLE() {
        ADD_TEST(create),
        ADD_TEST(appendNext),
        ADD_TEST(appendPrevious),
    };
    EXECUTE_TEST_TABLE("Nodes");
}

} // namespace tools::containers
