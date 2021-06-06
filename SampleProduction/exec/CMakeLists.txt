MESSAGE(STATUS "--")
MESSAGE(STATUS "---- ${BoldBlue}================================================${Reset}")
MESSAGE(STATUS "---- ${BoldYellow}ANALYSIS${Reset} [stand-alone/analysis]: [${BoldCyan}SampleProduction/exec/CMakeLists.txt${Reset}. ${BoldRed}Begin...${Reset}")
MESSAGE(STATUS "--")

include_directories(${PROJET_SOURCE_DIR}/include)
include_directories(${PROJET_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(LIBS ${LIBS} SampleProduction_src SampleProduction_utils)

if(${ROOT_FOUND})
  include_directories(${ROOT_INCLUDE_DIRS})
  set(LIBS ${LIBS} ${ROOT_LIBRARIES})
endif(${ROOT_FOUND})

if(${CLHEP_FOUND})
  include_directories(${CLHEP_INCLUDE_DIRS})
  set(LIBS ${LIBS} ${CLHEP_LIBRARIES})
endif(${CLHEP_FOUND})

file(GLOB BINARIES RELATIVE ${PROJECT_SOURCE_DIR}/exec *.cc)

MESSAGE("-------- ${BoldCyan}#### Building the following executables : ####${Reset}")
foreach(sourcefile ${BINARIES} )
    string(REPLACE ".cc" "" name ${sourcefile})
    MESSAGE(STATUS "-------- ${name}")
    add_executable(${name} ${sourcefile})
    target_link_libraries(${name} ${LIBS})
endforeach(sourcefile ${BINARIES})
MESSAGE("-------- ${BoldCyan}#### End ####${Reset}")


MESSAGE(STATUS "--")
MESSAGE(STATUS "---- ${BoldBlue}================================================${Reset}")
MESSAGE(STATUS "---- ${BoldYellow}ANALYSIS${Reset} [stand-alone/analysis]: [${BoldCyan}SampleProduction/exec/CMakeLists.txt${Reset}. ${BoldGreen}DONE!${Reset}")
MESSAGE(STATUS "--")