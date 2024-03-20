/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file memory_allocator.cpp                                               *
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

#include "kryos-tools/containers/memory_allocator.hpp"
#include <cstdlib>
#include <memory.h>

usize getHeapAllocationSize(void* data) {
    if (data == nullptr) {
        return 0;
    }
    internal::HeapAllocatedHeader* header = internal::getHeapAllocationDataHeader(data);
    return header->size;
}

usize getHeapAllocationCapacity(void* data) {
    if (data == nullptr) {
        return 0;
    }
    internal::HeapAllocatedHeader* header = internal::getHeapAllocationDataHeader(data);
    return header->capacity;
}

bool setHeapAllocationSize(void* data, usize size) {
    internal::HeapAllocatedHeader* header = internal::getHeapAllocationDataHeader(data);
#ifndef NDEBUG
    if (size <= header->capacity) {
        header->size = size;
    } else {
        return false;
    }
#else
    header->size = size;
#endif
    return true;
}

Result<void*> createHeapAllocation(usize size) {
    internal::HeapAllocatedHeader* header =
        (internal::HeapAllocatedHeader*)malloc(sizeof(internal::HeapAllocatedHeader) + size);
    if (header == nullptr) {
        return Result<void*>::fatal(nullptr, "Failed to allocate memory, malloc returned nullptr");
    }
    header->size = size;
    header->capacity = size;
    return Result<void*>::copyOk(internal::getHeapAllocationHeaderData(header));
}

void destroyHeapAllocation(void* data) {
    if (data != nullptr) {
        internal::HeapAllocatedHeader* header = internal::getHeapAllocationDataHeader(data);
        free(header);
    }
}

Result<void*> resizeHeapAllocation(void* data, usize size) {
    internal::HeapAllocatedHeader* header = internal::getHeapAllocationDataHeader(data);
    return internal::resizeHeapAllocationSize(header, data, size);
}

Result<void*> insertHeapAllocation(void* data, usize size, usize pos) {
    internal::HeapAllocatedHeader* header = internal::getHeapAllocationDataHeader(data);
    if (header->size < pos) {
        return Result<void*>::copyFailed(
            data, "Cannot insert block into dynamic allocation, position is greater "
                  "than the size");
    }
    Result<void*> resize = internal::resizeHeapAllocationSize(header, data, header->size + size);
    if (!resize.isOk()) {
        return resize;
    }
    data = resize.data;
    bool copyed = memcpy((char*)data + (pos + size), (char*)data + pos, size) != nullptr;
    if (!copyed) {
        return Result<void*>::copyFailed(
            data, "Failed to insert chunk of memory into allocation; \"memcpy\" failed and "
                  "returned nullptr");
    }
    return Result<void*>::copyOk(data);
}

Result<void*> resizeHeapAllocationCapacity(void* data, usize capacity) {
    if (data == nullptr) {
        return Result<void*>::fatal(
            "Cannot resize the capacity to %zu of dynamic allocation, data its nullptr", capacity);
    }
    internal::HeapAllocatedHeader* header = internal::getHeapAllocationDataHeader(data);
    return internal::resizeHeapAllocationCapacity(header, data, capacity);
}

namespace internal {

HeapAllocatedHeader* getHeapAllocationDataHeader(void* data) {
    HeapAllocatedHeader* header = (HeapAllocatedHeader*)data;
    header = header - 1;
    return header;
}

void* getHeapAllocationHeaderData(HeapAllocatedHeader* header) {
    header = header + 1;
    return (void*)header;
}

Result<void*> resizeHeapAllocationSize(HeapAllocatedHeader* header, void* data, usize size) {
    if (size > header->size) {
        Result<void*> result = resizeHeapAllocationCapacity(header, data, size);
        if (!result.isOk()) {
            return result;
        }
        header = getHeapAllocationDataHeader(result.data);
    }
    header->size = size;
    return Result<void*>::copyOk(getHeapAllocationHeaderData(header));
}

Result<void*> resizeHeapAllocationCapacity(HeapAllocatedHeader* header, void* data, usize size) {
    HeapAllocatedHeader* tmp =
        (HeapAllocatedHeader*)realloc(header, sizeof(HeapAllocatedHeader) + size);
    if (tmp == nullptr) {
        return Result<void*>::copyFailed(
            data,
            "Failed to resize memory allocation capacity; realloc failed and returned nullptr");
    }
    header = tmp;
    header->capacity = size;
    data = getHeapAllocationHeaderData(header);
    return Result<void*>::copyOk(data);
}

} // namespace internal
