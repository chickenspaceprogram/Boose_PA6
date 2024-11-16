# Battleship

To build this project, you must have CMake installed.
You can download it [here](https://cmake.org/download/), or use your preferred package manager.

### Configuring CMake

To configure the CMake project, navigate into the `build` directory using a terminal, and enter `cmake .` to configure CMake. Once you've configured CMake, you can then build the project.

### Building on *nix

To build the project on a Unix-based OS, enter `cmake --build .` when in the `build` directory, or `cmake --build build` when in the parent `Boose_PA6` directory. The executable will then compile and will be located in the `build` directory.

### Building on Windows

To build the project on Windows, you must use Microsoft Visual Studio. Open the `Boose_PA6.sln` file located in the `build` directory. Once Visual Studio has opened, right-click `Boose_PA6` in the Solution Explorer and select `Set as Startup Project`. Then, build the project.

### Running Battleship

To run this project, simply run the executable generated.

On Windows, use Visual Studio to run the project.

On Unix-based systems, the executable is located in `build/Boose_PA6`.
You can then run it either by selecting it in your file manager, or by running it on the command line with `build/Boose_PA6` (if you're in the `Boose_PA6` directory) or `./Boose_PA6` (if you're in the `build` directory).

If you decide to exit this program forcefully using Ctrl+C, your terminal settings may be altered.
To fix this on *nix systems, enter the command `reset` into the terminal.
Alternately, quit and reopen your terminal emulator.

## Potential runtime error codes:

### 0x00 - invalid ship type

This error occurs if `print_ship_string()` is given an invalid ship type. It should not occur under normal circumstances.

### 0x01 - log file could not be opened

This error occurs when the log file could not be opened for writing. 