/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file node.hpp                                                             *
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

#ifndef KRYOS__TOOLS_CONTAINERS__NODE_HPP
#define KRYOS__TOOLS_CONTAINERS__NODE_HPP

#include "kryos-tools/defines.hpp"

typedef struct node {
    struct node* p_next;
    struct node* p_previous;
} node_t;

node_t* get_node(void* p_node_data);
void* get_node_data(node_t* p_node);
void* get_node_next(void* p_node_data);
void* get_node_previous(void* p_node_data);

void* create_node_copy(usize data_size, void* p_data);
void* append_node_next(void* p_node_data, usize data_size, void* p_data);
void* append_node_previous(void* p_node_data, usize data_size, void* p_data);
void* destroy_node(void* p_node_data);
void destroy_nodes_right(void* p_node_data);
void destroy_nodes_left(void* p_node_data);

#define create_node(rvalue)                                                     \
    ({                                                                          \
        typeof(rvalue) _kint_temp = rvalue;                                     \
        typeof(rvalue)* _kint_node =                                            \
            (typeof(rvalue)*)create_node_copy(sizeof(_kint_temp), &_kint_temp); \
        _kint_node;                                                             \
    })

#define append_nodes_next(p_node_data, ...)                           \
    ({                                                                \
        typeof(*p_node_data) _kint_data[] = {__VA_ARGS__};            \
        typeof(p_node_data) _kint_current = p_node_data;              \
        for (usize i = 0; i < GET_VA_ARGS_COUNT(__VA_ARGS__); ++i) {  \
            _kint_current = (typeof(p_node_data))append_node_next(    \
                _kint_current, sizeof(*p_node_data), &_kint_data[i]); \
        }                                                             \
        _kint_current;                                                \
    })

#define append_nodes_previous(p_node_data, ...)                        \
    ({                                                                 \
        typeof(*p_node_data) _kint_data[] = {__VA_ARGS__};             \
        typeof(p_node_data) _kint_current = p_node_data;               \
        for (usize i = 0; i < GET_VA_ARGS_COUNT(__VA_ARGS__); ++i) {   \
            _kint_current = (typeof(p_node_data))append_node_previous( \
                _kint_current, sizeof(*p_node_data), &_kint_data[i]);  \
        }                                                              \
        _kint_current;                                                 \
    })

#endif
