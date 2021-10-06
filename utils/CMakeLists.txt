MESSAGE(STATUS "--")
MESSAGE(STATUS "---- ${BoldBlue}================================================${Reset}")
MESSAGE(STATUS "---- ${BoldYellow}ANALYSIS${Reset} [stand-alone/analysis]: [${BoldCyan}SampleProduction/utils/CMakeLists.txt${Reset}. ${BoldRed}Begin...${Reset}")
MESSAGE(STATUS "--")

include_directories(${PROJET_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/utils/*/*.h ${PROJECT_SOURCE_DIR}/utils/*/*.hpp)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/utils/*/*.cc ${PROJECT_SOURCE_DIR}/utils/*/*.cpp)

add_library(SampleProduction_utils STATIC ${SOURCES} ${HEADERS})
target_link_libraries(SampleProduction_utils ${LIBS})

file(GLOB BINARIES RELATIVE ${PROJECT_SOURCE_DIR}/utils/* *.cc *.cpp)

MESSAGE("-------- ${BoldCyan}#### Compiling the following files : ####${Reset}")
foreach( sourcefile ${BINARIES} )
    MESSAGE(STATUS "-------- ${sourcefile}")
endforeach(sourcefile ${BINARIES})
MESSAGE("-------- ${BoldCyan}#### End ####${Reset}")

MESSAGE(STATUS "--")
MESSAGE(STATUS "---- ${BoldBlue}================================================${Reset}")
MESSAGE(STATUS "---- ${BoldYellow}ANALYSIS${Reset} [stand-alone/analysis]: [${BoldCyan}SampleProduction/utils/CMakeLists.txt${Reset}. ${BoldGreen}DONE!${Reset}")
MESSAGE(STATUS "--")