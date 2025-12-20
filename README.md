# CMake Project Templates

A collection of ready-to-use CMake project templates for C++ development, featuring modern CMake practices, cross-platform support, and integrated code formatting.

## Templates

### LibraryTemplate

A complete C++ library template implementing the Pimpl (Pointer to Implementation) idiom for clean API design.

**Features:**
- Pimpl idiom implementation with proper destructor handling
- Separation of public API and private implementation
- Example application demonstrating library usage
- Install support for library distribution
- clang-format integration for consistent code style
- Cross-platform build configuration

**Structure:**
```
LibraryTemplate/
├── CMakeLists.txt          # Root CMake configuration
├── .clang-format           # Code formatting rules
├── 3rdparty/               # Third-party dependencies
├── src/                    # Library source code
│   ├── CMakeLists.txt      # Library build configuration
│   ├── MyLib.h             # Public API header
│   ├── MyLib.cpp           # Library implementation
│   └── impl/               # Private implementation (not installed)
│       ├── MyLibImpl.h
│       └── MyLibImpl.cpp
└── example/                # Example application
    ├── CMakeLists.txt
    └── main.cpp
```

### ApplicationTemplate

A standalone C++ application template.

**Structure:**
```
ApplicationTemplate/
├── CMakeLists.txt          # Root CMake configuration
├── .clang-format           # Code formatting rules
├── 3rdparty/               # Third-party dependencies
└── src/                    # Application source code
    ├── CMakeLists.txt
    └── main.cpp
```

## Quick Start

### Building a Project

```bash
# Navigate to the template you want to use
cd LibraryTemplate

# Create build directory
mkdir build && cd build

# Configure the project
cmake ..

# Build
make
# Or use the cross-platform command:
cmake --build .

# Run the example (for LibraryTemplate)
./bin/MyLibExample
```

### Build Types

```bash
# Debug build (with debug symbols)
cmake .. -DCMAKE_BUILD_TYPE=Debug

# Release build (optimized, default)
cmake .. -DCMAKE_BUILD_TYPE=Release

# Release with debug info
cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo
```

## Library Template Usage

### Building and Installing

```bash
cd LibraryTemplate/build

# Configure with custom install prefix (optional)
cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/local

# Build the library
make

# Install library and headers
make install
# Or with sudo for system-wide installation:
sudo make install
```

**Default install locations:**
- **Linux/macOS:** `/usr/local/lib/` (library), `/usr/local/include/MyLib/` (headers)
- **Windows:** `C:/Program Files/${PROJECT_NAME}/`

**Installed structure:**
```
/prefix/
├── lib/
│   └── libMyLib.a (or libMyLib.so)
└── include/MyLib/
    └── MyLib.h
```

Note: Implementation files in `src/impl/` are excluded from installation.

### Using as a Submodule

The library can be included as a submodule in another CMake project:

```cmake
# In parent CMakeLists.txt
add_subdirectory(path/to/LibraryTemplate)
target_link_libraries(YourTarget PRIVATE MyLib)
```

## Static Analysis (clang-tidy)

Both templates include clang-tidy integration for static analysis and code quality checks.

### Prerequisites

Install clang-tidy:
```bash
# Ubuntu/Debian
sudo apt install clang-tidy
```

### Usage

clang-tidy runs automatically during compilation when enabled (default):

```bash
cd build

# Configure with clang-tidy enabled (default)
cmake ..

# Build - clang-tidy will analyze files as they compile
cmake --build .

# Disable clang-tidy during build
cmake .. -DENABLE_CLANG_TIDY=OFF
```

### Configuration

Edit `.clang-tidy` in the project root to customize which checks are enabled. The default configuration enables:
- `bugprone-*` - Common bug patterns
- `clang-analyzer-*` - Clang static analyzer checks
- `cppcoreguidelines-*` - C++ Core Guidelines checks
- `modernize-*` - Modernization suggestions (C++11/14/17)
- `performance-*` - Performance improvements
- `portability-*` - Portability issues
- `readability-*` - Code readability improvements

Some overly strict checks are disabled by default (e.g., `modernize-use-trailing-return-type`).

### Customizing Checks

To modify enabled checks, edit the `Checks` field in `.clang-tidy`:
```yaml
Checks: >
  -*,
  bugprone-*,
  modernize-*,
  -modernize-use-trailing-return-type
```

To treat warnings as errors:
```yaml
WarningsAsErrors: '*'
```

## Code Formatting

Both templates include clang-format integration for consistent code style.

### Prerequisites

Install clang-format:
```bash
# Ubuntu/Debian
sudo apt install clang-format
```

### Usage

```bash
cd build

# Format all source files
make format
# Or cross-platform:
cmake --build . --target format

# Check formatting without modifying files
make format-check
# Or cross-platform:
cmake --build . --target format-check
```

### Customizing Format Style

Edit `.clang-format` in the project root to customize formatting rules. The current configuration uses:
- Attach-style braces (on same line)
- 4-space indentation
- No indentation for access modifiers (public/private)
- 120 character column limit

To generate a new format configuration:
```bash
# Generate with specific style
clang-format -style=microsoft -dump-config > .clang-format
clang-format -style=llvm -dump-config > .clang-format
clang-format -style=google -dump-config > .clang-format

# Or create minimal reference
echo "---
BasedOnStyle: Microsoft" > .clang-format
```

## Cross-Platform Support

These templates are designed to work on:
- Linux
- macOS
- Windows (with Visual Studio, MinGW, or MSYS2)

Use `cmake --build .` instead of `make` for maximum portability.

## Best Practices

### Pimpl Idiom (LibraryTemplate)

The library template demonstrates proper Pimpl implementation:

1. **Forward declaration** of implementation class in header
2. **Explicit destructor** defined in .cpp file (required for unique_ptr with incomplete type)
3. **Implementation details** hidden in `impl/` directory (excluded from installation)

This provides:
- Binary compatibility across releases
- Faster compilation (changes to impl don't require recompiling users)
- Clean public API

### Build Directory

Always use out-of-source builds:
```bash
mkdir build && cd build
cmake ..
```

Never run `cmake .` in the source directory.

### Installation Testing

Test installations in a local directory before system-wide install:
```bash
cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/test-install
make install
# Verify files in ~/test-install
```

## Troubleshooting

### clang-tidy Not Found

If clang-tidy is not available:
```bash
# Check if clang-tidy is installed
which clang-tidy

# Install if missing (see Static Analysis section)
```

The build will succeed even without clang-tidy; it's optional. You can also explicitly disable it:
```bash
cmake .. -DENABLE_CLANG_TIDY=OFF
```

### clang-format Not Found

If formatting targets are not available:
```bash
# Check if clang-format is installed
which clang-format

# Install if missing (see Code Formatting section)
```

The build will succeed even without clang-format; it's optional.

### Permission Denied During Install

If installing to system directories:
```bash
sudo make install
```

Or use a user-writable prefix:
```bash
cmake .. -DCMAKE_INSTALL_PREFIX=$HOME/local
```