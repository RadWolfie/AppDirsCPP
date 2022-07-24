[![GitHub CI](https://github.com/RadWolfie/AppDirsCPP/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/RadWolfie/AppDirsCPP/actions/workflows/ci.yml)

# Description
AppDirsCPP, written in C++, is a port of [AppDirs (python)](https://github.com/ActiveState/appdirs).
This project allow to compile as native C++ library without python requirement.

# Features
- Everything AppDirs has except for appauthor parameter's 3rd optional value, `False`, is excluded.
  - See AppDirs's [readme file](https://github.com/ActiveState/appdirs/blob/master/README.rst) for details.
- Cross-platform support.
- [CMake](https://cmake.org/cmake/help/latest/) support for ability to use [different compilers](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html).
- Unit tests for each function to ensure they are passing the expectation results.

# Contribution Guidelines
## Any contributions you make will be under the MIT Software License
In short, when you submit code changes, your submissions are understood to be under the same [MIT License](http://choosealicense.com/licenses/mit/) that covers the project. Feel free to contact the maintainers if that's a concern.

## License
By contributing, you agree that your contributions will be licensed under its MIT License.

## Contributing
### Main Prerequisites
1. [Git](https://git-scm.com)
2. [CMake](https://cmake.org)
    * Some IDEs already have CMake support, this is optional.

### Fetching the code
Run the following command in the command line:
<br>`git clone https://github.com/RadWolfie/AppDirsCPP.git`


### Compiling
1. Open terminal whichever has CMake support.
<br>i.e. If you don't have CMake installed, open `___ Native Tools Command Prompt for VS 20##`.
2. `cd` to the AppDirsCPP directory.
3. Run these commands to generate compiler projects.
   1. `mkdir build & cd build`
   2. `cmake .. -G ???`; replace ??? to your perferred compiler/IDE from [CMake Generator](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) documentation.
4. Open your solution/project(s) from preferred compiler/IDE.
5. Start building project(s).
6. Run tests to ensure your new code has not break the expected results. (RECOMMENDED)

# Research References
- [AppDirs project](https://github.com/ActiveState/appdirs)
- [$XDG_ prefix usages](https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html)
- [Online ECMAScript regex inspection](https://regex101.com/)

# Credits
- 2010 ActiveState Software Inc.
  - and AppDirs contributors.
- AppDirsCPP contributors