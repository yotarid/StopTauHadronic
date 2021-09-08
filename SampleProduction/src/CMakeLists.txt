MESSAGE(STATUS "--")
MESSAGE(STATUS "---- ${BoldBlue}================================================${Reset}")
MESSAGE(STATUS "---- ${BoldYellow}ANALYSIS${Reset} [stand-alone/analysis]: [${BoldCyan}SampleProduction/src/CMakeLists.txt${Reset}. ${BoldRed}Begin...${Reset}")
MESSAGE(STATUS "--")

include_directories(${PROJET_SOURCE_DIR}/include)
include_directories(${PROJET_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(${ROOT_FOUND})
  include_directories(${ROOT_INCLUDE_DIRS})
  set(LIBS ${LIBS} ${ROOT_LIBRARIES})
endif(${ROOT_FOUND})

if(${CLHEP_FOUND})
  include_directories(${CLHEP_INCLUDE_DIRS})
  set(LIBS ${LIBS} ${CLHEP_LIBRARIES})
endif(${CLHEP_FOUND})

file(GLOB HEADERS *.h)
file(GLOB SOURCES *.cc)

add_library(SampleProduction_src STATIC ${SOURCES} ${HEADERS})
target_link_libraries(SampleProduction_src ${LIBS})

file(GLOB BINARIES RELATIVE ${PROJECT_SOURCE_DIR}/src *.cc)

MESSAGE("-------- ${BoldCyan}#### Compiling the following files : ####${Reset}")
foreach( sourcefile ${BINARIES} )
    MESSAGE(STATUS "-------- ${sourcefile}")
endforeach(sourcefile ${BINARIES})
MESSAGE("-------- ${BoldCyan}#### End ####${Reset}")

MESSAGE(STATUS "--")
MESSAGE(STATUS "---- ${BoldBlue}================================================${Reset}")
MESSAGE(STATUS "---- ${BoldYellow}ANALYSIS${Reset} [stand-alone/analysis]: [${BoldCyan}SampleProduction/src/CMakeLists.txt${Reset}. ${BoldGreen}DONE!${Reset}")
MESSAGE(STATUS "--")
