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

#include "kryos-tests/tools/containers.hpp"

#include "kryos-tests/framework.hpp"
#include "kryos-tools/containers/memory_allocator.hpp"

void allocateAndDestroy(TestOutput& out) {
    usize size = sizeof(i32);
    Result<void*> result = createHeapAllocation(size);
    IS_EQUALS(result.error_message, NO_ERROR_MESSAGE, "%s", result.error_message);

    i32* data = (i32*)result.data;
    *data = 43;
    IS_EQUALS(getHeapAllocationSize(data), size, "Incorrect size, should be %zu", size);
    IS_EQUALS(getHeapAllocationCapacity(data), size, "Incorrect capacity, should be %zu", size);
    IS_EQUALS(*data, 43, "Incorrect value, should be 43");
    destroyHeapAllocation(data);

    size = sizeof(i32) * 10;
    result = createHeapAllocation(size);
    IS_EQUALS(result.error_message, NO_ERROR_MESSAGE, "%s", result.error_message);

    data = (i32*)result.data;
    for (i32 i = 0; i < 10; i++) {
        data[i] = i + 1;
    }
    IS_EQUALS(getHeapAllocationSize(data), size, "Incorrect size, should be %zu", size);
    IS_EQUALS(getHeapAllocationCapacity(data), size, "Incorrect capacity, should be %zu", size);
    for (i32 i = 0; i < 10; i++) {
        IS_EQUALS(data[i], i + 1, "Incorrect value given at index %d, should be %d", i, i + 1);
    }
    destroyHeapAllocation(data);
}

void resizeCapacityAndResize(TestOutput& out) {
    Result<void*> result = createHeapAllocation(sizeof(i32) * 10);
    IS_EQUALS(result.error_message, NO_ERROR_MESSAGE, "%s", result.error_message);
    i32* data = (i32*)result.data;
    for (i32 i = 0; i < 10; i++) {
        data[i] = i + 1;
    }
    for (i32 i = 0; i < 10; i++) {
        IS_EQUALS(data[i], i + 1, "Incorrect value given at index %d, should be %d", i, i + 1);
    }

    result = resizeHeapAllocation(data, sizeof(i32) * 20);
    IS_EQUALS(result.error_message, NO_ERROR_MESSAGE, "%s", result.error_message);
    data = (i32*)result.data;
    for (i32 i = 10; i < 20; i++) {
        data[i] = i + 1;
    }
    for (i32 i = 0; i < 20; i++) {
        IS_EQUALS(data[i], i + 1, "Incorrect value given at index %d, should be %d", i, i + 1);
    }

    result = resizeHeapAllocation(data, sizeof(i32) * 5);
    IS_EQUALS(result.error_message, NO_ERROR_MESSAGE, "%s", result.error_message);
    data = (i32*)result.data;
    for (usize i = 0; i < 5; i++) {
        data[i] = i + 2;
    }
    destroyHeapAllocation(data);
}

void insertSizeAtPosition(TestOutput& out) {
    usize size = sizeof(i32) * 10;
    Result<void*> result = createHeapAllocation(size);
    IS_EQUALS(result.error_message, NO_ERROR_MESSAGE, "%s", result.error_message);

    i32* data = (i32*)result.data;
    for (i32 i = 0; i < 10; i++) {
        data[i] = i + 1;
    }
    IS_EQUALS(getHeapAllocationSize(data), size, "Incorrect size, should be %zu", size);
    IS_EQUALS(getHeapAllocationCapacity(data), size, "Incorrect capacity, should be %zu", size);

    usize insert_size = sizeof(i32) * 5;
    usize position = sizeof(i32) * 2;
    result = insertHeapAllocation(data, insert_size, position);
    IS_EQUALS(result.error_message, NO_ERROR_MESSAGE, "%s", result.error_message);

    data = (i32*)result.data;
    for (i32 i = 2; i < 7; i++) {
        data[i] = i * 10;
    }
    IS_EQUALS(getHeapAllocationSize(data), size + insert_size, "Incorrect size, should be %zu",
              size + insert_size);
    IS_EQUALS(getHeapAllocationCapacity(data), size + insert_size,
              "Incorrect capacity, should be %zu", size + insert_size);
    i32 j = 1;
    for (i32 i = 0; i < 12; i++) {
        if (i > 1 && i < 7) {
            IS_EQUALS(data[i], i * 10,
                      "Incorrect value (%d) given at index %d (inserted), should be %d", data[i], i,
                      i * 1);
        } else {
            IS_EQUALS(data[i], j, "Incorrect value (%d) given at index %d, should be %d", data[i],
                      i, j);
            j++;
        }
    }
    destroyHeapAllocation(data);
}

namespace tools::containers {

void memoryAllocator() {
    TEST_TABLE() {
        ADD_TEST(allocateAndDestroy),
        ADD_TEST(resizeCapacityAndResize),
        ADD_TEST(insertSizeAtPosition),
    };
    EXECUTE_TEST_TABLE("Memory Allocation");
}

} // namespace tools::containers
