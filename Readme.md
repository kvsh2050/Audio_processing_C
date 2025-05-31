## Sound Generation and Audio Processing using C language 

### Tools

```
Compiler                 : gcc  
Build Tools              : Make   
Version Control          : Git  
Storage                  : GitHub  
Audio Library            : PortAudio, ALSA  
Platform                 : Simple Text Editor  
Debugger                 : gdb  
Signal Processing Library: FFTW, Libsndfile  
```

### Dependencies for Linux

- Install ALSA development libraries:
  ```bash
  sudo apt-get install libasound-dev
  ```

- After downloading PortAudio:
  ```bash
  ./configure && make
  ```
https://en.ittrip.xyz/c-language/c-audio-library-dev 

### Cmake Folder Structure 
```
MyProject/
├── CMakeLists.txt
├── build/             # for out-of-source builds
├── include/           # .h (header) files
│   └── mylib/
│       └── mylib.h
├── src/               # .c/.cpp source files
│   └── mylib.c
├── lib/               # optional: third-party libs like PortAudio
│   └── portaudio/
├── tests/             # unit test code
│   └── test_main.c

```
Then corresponding cmake file is :

```
cmake_minimum_required(VERSION 3.10)
project(MyProject C)

# Add include/ for headers
include_directories(include)

# Optionally set C standard
set(CMAKE_C_STANDARD 99)

# Add src as a library (e.g., mylib)
add_library(mylib src/mylib.c)

# Add PortAudio (assuming it's already built or add_subdirectory if needed)
# include_directories(lib/portaudio/include)
# link_directories(lib/portaudio/lib)

# Build the main executable
add_executable(MyProject src/main.c)
target_link_libraries(MyProject mylib)

# Add test executable
add_executable(test_runner tests/test_main.c)
target_link_libraries(test_runner mylib)
```
