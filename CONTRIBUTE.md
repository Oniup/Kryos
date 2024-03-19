# Contributing Guidelines

Thank you for considering a contribution to our project! Please follow the guidelines below
when contributing code:

## How to Contribute

We welcome contributions in the form of new features, bug fixes, and improvements. To do so,
please follow these steps:

* Fork the repo.
* Create a pull request for new feature/fixes.

## Code Standards

To ensure high-quality and maintainable code, we have established the following standards:

* All code must be C++23 compilable with Clang, GCC and MSVC.
* Do not use the standard library, use engine types instead.
* Code should be compilable on both UNIX/POSIX and Windows platforms.
* Code with warnings will not be accepted; please address any warnings.
* Whenever possible, include tests for new features using the test framework.
* Each file must begin with the specified license statement:

```cpp
/* ------------------------------------------------------------------------ *
 * This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) *
 * @file [FILENAME]                                                         *
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
```

### Code Style

* Limit lines to a maximum of 100 characters.
* Provide Doxygen comments with detailed descriptions for all public functions and types.
* Maintain consistent formatting with the project's style, preferably using clang-format.
* Use spaces for indentation instead of tabs.

### Naming Conventions

* Format header guards as `KRYOS__[MOD]__[DIR]_[FILE]_HPP`
* Use `.cpp` and `.hpp` extensions.
* `snake_case` for variables, `camelCase` for functions/methods, `PascalCase` for types, enum
  values, and `UPPER_SNAKE_CASE` for macros.
* Internal public functions should be in the `internal` namespace.
* Ensure that opening curly brackets are always on the same line as the function declaration.
* Follow the common patterns and styles as the rest of the codebase to be consistent.
