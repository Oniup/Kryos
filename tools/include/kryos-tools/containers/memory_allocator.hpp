/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file memory_allocator.hpp                                               *
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

#ifndef KRYOS__TOOLS_CONTAINERS__MEMORY_ALLOCATOR_HPP
#define KRYOS__TOOLS_CONTAINERS__MEMORY_ALLOCATOR_HPP

#include "kryos-tools/defines.hpp"
#include "kryos-tools/result.hpp"

usize getHeapAllocationSize(void* data);
usize getHeapAllocationCapacity(void* data);

/**
 * @brief Sets the memory allocation size in bytes using std::malloc
 * @warning The size cannot exceed the reserved capacity size, use `resizeHeapAllocation` or
 * `resizeHeapAllocationCapacity` instead
 *
 * @param data Pointer to data
 * @param size Size in bytes to set
 */
bool setHeapAllocationSize(void* data, usize size);

Result<void*> createHeapAllocation(usize size);

void destroyHeapAllocation(void* data);

Result<void*> resizeHeapAllocation(void* data, usize size);
Result<void*> insertHeapAllocation(void* data, usize size, usize position);
Result<void*> resizeHeapAllocationCapacity(void* data, usize capacity);

namespace internal {

/**
 * @class AllocatorHeader
 * @brief Dynamic memory allocator structure
 */
struct HeapAllocatedHeader {
    usize size;
    usize capacity;
};

HeapAllocatedHeader* getHeapAllocationDataHeader(void* data);
void* getHeapAllocationHeaderData(HeapAllocatedHeader* header);
// @warning Does not check if header is NULL, call `resizeHeapAllocation` to also
// check null validity
Result<void*> resizeHeapAllocationSize(HeapAllocatedHeader* header, void* data, usize size);
// @warning Does not check if header is NULL, call `resizeHeapAllocationCapacity`
// to also check null validity
Result<void*> resizeHeapAllocationCapacity(HeapAllocatedHeader* header, void* data, usize size);

} // namespace internal

#endif
