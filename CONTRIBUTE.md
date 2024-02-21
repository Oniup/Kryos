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

* All code must be pure C99 compilable with Clang, GCC and MSVC. We do not except C++ code.
* Code should be compilable on both UNIX/POSIX and Windows platforms.
* Code with warnings will not be accepted; please address any warnings.
* Whenever possible, include tests for new features.
* Each file must begin with the specified license statement:

```c
/// ------------------------------------------------------------------------ ///
/// This file is part of Kryos Engine (https://github.com/Oniup/KryosEngine) ///
/// @file [FILENAME]                                                         ///
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
```

### Code Style

* Limit lines to a maximum of 90 characters.
* Provide Doxygen comments with detailed descriptions for all public functions and types.
* Maintain consistent formatting with the project's style, preferably using clang-format.
* Use spaces for indentation instead of tabs.

### Naming Conventions

* Format header guards as `KRYOS__[MOD]__[DIR]_[FILE]_H`
* Use `.c`, `.h` extensions.
* Use `snake_case` for variable, struct and functions and `UPPER_SNAKE_CASE` for constants;
  enum fields and macros
* Prefix pointer types that are in function parameters or struct fields with `p_` indicating
  that the memory needs to be handled
* Whenever adding `typedef` to type declaration, must add `_t` with the exception of core
  primitive types such as `u32`, `f64`, `b8`, etc...
* Prefix internal functions and types that are not private (definition in `.c` file) with
  `intl_` and include a comment stating `INTERNAL USE ONLY` at the top of the Doxygen comment.
    ```c
    /// INTERNAL USE ONLY
    /// @brief ...
    void intl_bar();
    ```
* Ensure that opening curly brackets are always on the same line.
* All functions should try to follow this syntactical structure:
    ```
    <verb><subject><complement>();
    ```
  More specifically, every syntactic element implies:
    ```
    <action><object><attribute/state>();
    ```
* Try to follow the common pattern as the rest of the codebase to be consistant
* Prefix pointer functions with `PFN_`.