# Kryos

A small cross platform game engine aiming to provided a streamlined development
experience while staying lightweight, fast and open source. The Project is very
early within development and currently working on the early core components.

## Table of Contents

- [Installation](#installation)
- [Planned Features](#features)
- [Contributing](#contributing)
- [License](#license)

## Installation

Kryos uses CMake for the build process, making it straightforward. Follow
these three commands to clone the repository, navigate to the project directory,
and generate build/project files for your operating system

```bash
git clone https://github.com/Oniup/Kryos.git
cd Kryos
cmake --build .
```

To specify a particular build system generator, add the following option along
with the desired generator name. In this example, we'll generate Ninja build
files:

```bash
cmake -DCMAKE_GENERATOR=Ninja --build .
```

## Planned Features (1st Year)

25.11.2023 is the day of starting this project therefore:

### Features coming within the next 6 months

- Render pipeline using [Vulkan]() as the backend
- Customizable User Interface for the editor
- Support for both a 2D and a basic but still usable 3D renderer
- Fully integrated ECS

### Features coming within 12 months

- Faster, more performant renderer
- Have a MVP version of the editor which would include:
    - Asset handling
    - Projects and scenes
- And more (The list can go on and on...)

## Contributing

If your interested in contributing, your welcome to by following these
guidelines:

    Fork the repository.
    Create a new branch.
    Make your changes, follow the code style guidelines.
    Commit them.
    Submit a pull request.

## License

This project is licensed under the ZIB License - see the [LICENSE](./LICENSE.md)
file for details.
