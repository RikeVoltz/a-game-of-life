# A Game of Life
This is a simple educational project that represents the implementation of the Conway's “Game of Life” in C++ using SFML as a graphics library. In memory of John Horton Conway.

## Installation
Перед выполнением тех или иных шагов установки рекомендуется убедиться в их необходимости - так в Windows Chocolate нужен для установки VS Build Tools, Python3 и CMake. Если перечисленные компоненты уже установлены - то необходимости в их установке (как и в установке Chocolate) нет.
1. (Windows only) Install [choco](https://chocolatey.org/docs/installation)
2. (Windows) `choco install -y python3 make && choco install -y vcbuildtools -ia "/Full"` (long step, check for necessity)` && choco install -y cmake --installargs 'ADD_CMAKE_TO_PATH=System'` | (Linux) `sudo apt install -y gcc g++ python3 cmake`  
3. `pip install conan`
4. `conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan`
5. (Windows) `make install-windows` | (Linux) `make install-linux`
6. (Windows) `life_game.exe` | (Linux) `./life_game`

## Usage  
- `LMouse` - to put alive cell
- `RMouse` - to kill alive cell
- `Num+` - to increase speed
- `Num-` - to decrease speed
- `Enter` - to start/stop emulation
