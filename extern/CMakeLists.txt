MESSAGE(STATUS "--")
MESSAGE(STATUS "---- ${BoldBlue}================================================${Reset}")
MESSAGE(STATUS "---- ${BoldYellow}ANALYSIS${Reset} [stand-alone/analysis]: [${BoldCyan}SampleProduction/extern/CMakeLists.txt${Reset}. ${BoldRed}Begin...${Reset}")
MESSAGE(STATUS "--")

include_directories(${PROJET_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/extern/pugixml/*.h* ${PROJECT_SOURCE_DIR}/extern/argvparser/*.h* ${PROJECT_SOURCE_DIR}/extern/easylogging/*.h*)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/extern/pugixml/*.c* ${PROJECT_SOURCE_DIR}/extern/argvparser/*.c* ${PROJECT_SOURCE_DIR}/extern/easylogging/*.c*)

add_library(SampleProduction_extern STATIC ${SOURCES} ${HEADERS})
target_link_libraries(SampleProduction_extern ${LIBS})

MESSAGE("-------- ${BoldCyan}#### Compiling the following files : ####${Reset}")
    MESSAGE(STATUS "-------- pugixml")
    MESSAGE(STATUS "-------- argvparser")
    MESSAGE(STATUS "-------- easylogging")
MESSAGE("-------- ${BoldCyan}#### End ####${Reset}")

MESSAGE(STATUS "--")
MESSAGE(STATUS "---- ${BoldBlue}================================================${Reset}")
MESSAGE(STATUS "---- ${BoldYellow}ANALYSIS${Reset} [stand-alone/analysis]: [${BoldCyan}SampleProduction/extern/CMakeLists.txt${Reset}. ${BoldGreen}DONE!${Reset}")
MESSAGE(STATUS "--")