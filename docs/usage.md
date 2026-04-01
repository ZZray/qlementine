# Usage

## Installation

Qlementine supports Qt5 and Qt6 from the same codebase. When configuring CMake, point `CMAKE_PREFIX_PATH` to either your Qt5 or Qt6 installation.

1. Add the library as a dependency. Here is an example with CMake FetchContent. You may add it with another way such as vcpkg or from a regular installation.

   ```bash
   include(FetchContent)
   FetchContent_Declare(Qlementine GIT_REPOSITORY "https://github.com/oclero/qlementine.git")
   FetchContent_MakeAvailable(Qlementine)
   ```

2. Link with the library in CMake.

   ```cmake
   target_link_libraries(your_project qlementine)
   ```

If you are building the examples, `sandbox` works with Qt5 and Qt6, while `showcase` currently requires Qt6 because `qlementine-icons` is still Qt6-only.

## Usage in code

Define the `QStyle` on your `QApplication`.

```c++
#include <oclero/qlementine.hpp>

QApplication app(argc, argv);

auto* style = new oclero::qlementine::QlementineStyle(&app);
QApplication::setStyle(style);
```

## Themes

You may want to use your own JSON theme.

```c++
style->setThemeJsonPath(":/path/to/your/theme.json");
```

Additionnally, you can also use `ThemeManager` to handle that for you.

```c++
// Link a ThemeManager to a QlementineStyle.
auto* themeManager = new oclero::qlementine::ThemeManager(style);

// Load the directory where you store your own JSON themes.
themeManager->loadDirectory(":/themes");

// Define theme on QStyle.
themeManager->setCurrentTheme("Light");
```
