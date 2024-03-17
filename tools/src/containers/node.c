/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file node.c                                                             *
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

#include "kryos-tools/containers/node.h"
#include "kryos-tools/containers/memory_allocator.h"
#include "kryos-tools/debug.h"
#include <memory.h>

node_t* get_node(void* p_node_data) {
    node_t* p_node = (node_t*)p_node_data;
    return p_node - 1;
}

void* get_node_data(node_t* p_node) {
    return p_node + 1;
}

void* get_node_next(void* p_node_data) {
    node_t* p_node = get_node(p_node_data);
    if (p_node->p_next != NULL) {
        return get_node_data(p_node->p_next);
    }
    return NULL;
}

void* get_node_previous(void* p_node_data) {
    node_t* p_node = get_node(p_node_data);
    if (p_node->p_previous != NULL) {
        return get_node_data(p_node->p_previous);
    }
    return NULL;
}

void* create_node_copy(usize data_size, void* p_data) {
    allocated_memory_result_t result = create_dynamic_allocation(sizeof(node_t) + data_size);
    if (result.error_message != NO_ERROR_MESSAGE) {
        ERROR("Failed to create node: %s", result.error_message);
        return NULL;
    }
    node_t* p_node = (node_t*)result.p_data;
    p_node->p_next = NULL;
    p_node->p_previous = NULL;
    void* p_node_data = get_node_data(p_node);
    memcpy(p_node_data, p_data, data_size);
    return p_node_data;
}

void* append_node_next(void* p_node_data, usize data_size, void* p_data) {
    node_t* p_new = get_node(create_node_copy(data_size, p_data));
    if (p_new == NULL) {
        ERROR("Failed to append new node to the right (p_next)");
        return NULL;
    }
    node_t* p_node = get_node(p_node_data);
    p_new->p_next = p_node->p_next;
    p_new->p_previous = p_node;
    if (p_node->p_next != NULL) {
        node_t* p_next = p_node->p_next;
        p_next->p_previous = p_new;
    }
    p_node->p_next = p_new;
    return get_node_data(p_new);
}

void* append_node_previous(void* p_node_data, usize data_size, void* p_data) {
    node_t* p_new = get_node(create_node_copy(data_size, p_data));
    if (p_new == NULL) {
        ERROR("Failed to append new node to the left (p_previous)");
        return NULL;
    }
    node_t* p_node = get_node(p_node_data);
    p_new->p_next = p_node;
    p_new->p_previous = p_node->p_previous;
    if (p_node->p_previous != NULL) {
        node_t* p_previous = p_node->p_previous;
        p_previous->p_next = p_new;
    }
    p_node->p_previous = p_new;
    return get_node_data(p_new);
}

void* destroy_node(void* p_node_data) {
    void* p_next = get_node_next(p_node_data);
    node_t* p_node = get_node(p_node_data);
    destroy_dynamic_allocation(p_node);
    return p_next;
}

void destroy_nodes_right(void* p_node_data) {
    void* p_next = p_node_data;
    while (p_next != NULL) {
        p_next = destroy_node(p_next);
    }
}

void destroy_nodes_left(void* p_node_data) {
    void* p_previous = p_node_data;
    while (p_previous != NULL) {
        void* p_next = get_node_previous(p_previous);
        destroy_node(p_previous);
        p_previous = p_next;
    }
}
