# SFML Project

## Overview
This project is a simple game built using the SFML (Simple and Fast Multimedia Library) framework. It demonstrates the basic structure of a multi-file C++ application, including the use of classes to manage game state and input.

## Project Structure
```
sfml-project
├── src
│   ├── main.cpp        # Entry point of the application
│   ├── Game.cpp        # Implementation of the Game class
│   └── Game.h          # Declaration of the Game class
├── img
│   └── pesawat1.png    # Image asset for the game
├── CMakeLists.txt      # Build configuration file for CMake
└── README.md           # Project documentation
```

## Building the Project
To build the project, you need to have CMake and SFML installed on your system. Follow these steps:

1. Clone the repository or download the project files.
2. Open a terminal and navigate to the project directory.
3. Create a build directory:
   ```
   mkdir build
   cd build
   ```
4. Run CMake to configure the project:
   ```
   cmake ..
   ```
5. Build the project:
   ```
   cmake --build .
   ```

## Running the Application
After building the project, you can run the application from the build directory:
```
./sfml-project
```

## Controls
- **W**: Move up
- **A**: Move left
- **S**: Move down
- **D**: Move right

## Dependencies
- SFML (version X.X.X or later)

## License
This project is licensed under the MIT License. See the LICENSE file for more details.