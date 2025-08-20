# libpico

A dynamic link library for parsing PicoScenes data frame.

## Build

### Toolchains

* Clang
* MSVC / g++
* CMake
* Ninja

> **Note:**  
> *Currently only tested on Windows using MSVC (Microsoft Visual Studio C++).*

### Step by Step

1. Clone the libpico repository from GitHub, including submodule ([RXS-Parsing-Core](https://github.com/wifisensing/RXS-Parsing-Core)) the project depends on:

```
git clone --recurse-submodules https://github.com/kiki-i/libpico.git
```

2. Change the current directory to `libpico` and creates a new `build` folder for builds:

```
cd libpico && mkdir build
```

3. Go into the `build` directory and generate Ninja build files using CMake:

```
cd build && cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ..
```

4. Build the project using Ninja:

```
ninja
```

## Usage

Refer to [src/api.hxx](src/api.hxx) for externed methods definition.

Refer to [src/libpicoFrame.hxx](src/libpicoFrame.hxx) for data structs definition.

## Part of

* [PicoScenesParser.py](https://github.com/kiki-i/PicoScenesParser.py)

## License

[![LGPLv3](https://www.gnu.org/graphics/lgplv3-with-text-154x68.png)](https://www.gnu.org/licenses/agpl-3.0.html)

Licensed under the [LGPLv3](https://www.gnu.org/licenses/agpl-3.0.html).
