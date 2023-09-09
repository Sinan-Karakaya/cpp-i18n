# cpp-i18n

## Introduction

cpp-i18n is a C++ library for internationalization (i18n) of C++ applications, which was made to be as simple as 
possible to use, with easy integration into existing projects.

- [Installation](#installation)
    - [CMake](#cmake)
- [Usage](#usage)
    - [Basic usage](#basic-usage)
    - [Multiple languages](#multiple-languages)
    - [Multiple files](#multiple-files)
    - [Custom locales directory path](#custom-locales-directory-path)
- [Planned features](#planned-features)

## Installation

### CMake

cpp-i18n can be installed using CMake's `FetchContent` module.

```cmake
include(FetchContent)

FetchContent_Declare(
    cpp-i18n
    GIT_REPOSITORY   https://github.com/Sinan-Karakaya/cpp-i18n.git
    GIT_TAG          v0.1.0
)

FetchContent_MakeAvailable(cpp-i18n)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE 
    cpp-i18n
)
```

## Usage

### Basic usage

assets/locales/en/basic.json
```json
{
    "hello": "Hello, world!"
}
```

```cpp
#include <Translator.hpp>

int main()
{
    i18n::Translator t;
    
    std::cout << t.translate("hello", "basic") << std::endl;    // "Hello, world!"
    return 0;
}
```

### Multiple languages

assets/locales/en/basic.json
```json
{
    "hello": "Hello, world!"
}
```

assets/locales/fr/basic.json
```json
{
    "hello": "Bonjour, monde!"
}
```

```cpp
#include <Translator.hpp>

int main()
{
    i18n::LocaleConfig config;
    config.supportedLocales = {"en", "fr"};
    i18n::Translator t(config);
    
    std::cout << t.translate("hello", "basic") << std::endl;    // "Hello, world!"
    t.setLocale("fr");
    std::cout << t.translate("hello", "basic") << std::endl;    // "Bonjour, monde!"
    return 0;
}
```

### Multiple files

assets/locales/en/basic.json
```json
{
    "hello": "Hello, world!"
}
```

assets/locales/en/other.json
```json
{
    "goodbye": "Goodbye, world!"
}
```

```cpp
#include <Translator.hpp>

int main()
{
    i18n::Translator t;
    
    std::cout << t.translate("hello", "basic") << std::endl;    // "Hello, world!"
    std::cout << t.translate("goodbye", "other") << std::endl;  // "Goodbye, world!"
    return 0;
}
```

### Custom locales directory path

path/to/locales/en/basic.json
```json
{
    "hello": "Hello, world!"
}
```

```cpp
#include <Translator.hpp>

int main()
{
    i18n::LocaleConfig config;
    config.localesDir = "path/to/locales";
    i18n::Translator t(config);
    
    std::cout << t.translate("hello", "basic") << std::endl;    // "Hello, world!"
    return 0;
}
```

## Planned features

- [ ] Support for objects inside of JSON files [(#1)](https://github.com/Sinan-Karakaya/cpp-i18n/issues/1)
- [ ] Support for pluralization [(#2)](https://github.com/Sinan-Karakaya/cpp-i18n/issues/2)
- [ ] Support for localization of numbers, dates, currencies, etc... [(#4)](https://github.com/Sinan-Karakaya/cpp-i18n/issues/4)
- [ ] Support for automatically detecting multiple locales [(#3)](https://github.com/Sinan-Karakaya/cpp-i18n/issues/3)
