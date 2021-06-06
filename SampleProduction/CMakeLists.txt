string(ASCII 27 Esc)
set(Reset       "${Esc}[m"    )
set(Bold        "${Esc}[1m"   )
set(Red         "${Esc}[31m"  )
set(Green       "${Esc}[32m"  )
set(Yellow      "${Esc}[33m"  )
set(Blue        "${Esc}[34m"  )
set(Magenta     "${Esc}[35m"  )
set(Cyan        "${Esc}[36m"  )
set(White       "${Esc}[37m"  )
set(BoldRed     "${Esc}[1;31m")
set(BoldGreen   "${Esc}[1;32m")
set(BoldYellow  "${Esc}[1;33m")
set(BoldBlue    "${Esc}[1;34m")
set(BoldMagenta "${Esc}[1;35m")
set(BoldCyan    "${Esc}[1;36m")
set(BoldWhite   "${Esc}[1;37m")

MESSAGE(STATUS "")
MESSAGE(STATUS "${BoldBlue}============================================${Reset}")
MESSAGE(STATUS "${BoldYellow}ANALYSIS${Reset} [stand-alone]: compilation of the analysis package")
MESSAGE(STATUS "")

cmake_minimum_required(VERSION 2.8.9)
project(SampleProduction)

if ( ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR} )
  MESSAGE( STATUS "${BoldRed}" )
  MESSAGE( FATAL_ERROR "${Reset}In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt." )
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
${PROJECT_SOURCE_DIR}/bin
CACHE PATH
"Single Directory for all Executables."
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-g -std=c++17 -gdwarf-4 -O2 -Werror -pedantic -Wall -Wextra -Wcpp")

MESSAGE(STATUS "----")
MESSAGE(STATUS "---- ${BoldCyan}### Searching for ROOT ###${Reset}")
find_package(ROOT)
if(ROOT_FOUND)
  MESSAGE(STATUS "---- Using ROOT version ${ROOT_VERSION}")
endif(ROOT_FOUND)
MESSAGE(STATUS "----")

find_package(CLHEP)
if(CLHEP_FOUND)
  MESSAGE(STATUS "---- Found CLHEP")
endif(CLHEP_FOUND)
MESSAGE(STATUS "----")

set(CLHEP_INCLUDE_DIRS $ENV{CLHEP_INCLUDE})
set(CLHEP_LIBRARY_DIRS $ENV{CLHEP_LIB})

include_directories(include)
add_subdirectory(src)
add_subdirectory(exec)
add_subdirectory(utils)

MESSAGE(STATUS "")
MESSAGE(STATUS "${BoldYellow}ANALYSIS${Reset} [stand-alone]: [${BoldCyan}${SAMPLEPRODUCTION_BASE_DIR}/CMakeLists.txt${Reset}]")
MESSAGE(STATUS "${BoldYellow}ANALYSIS${Reset} [stand-alone]: compilation of the analysis package done.")
MESSAGE(STATUS "")
