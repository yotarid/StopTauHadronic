file(GLOB_RECURSE CLHEP_SOURCE_DIR ${CLHEP_INCLUDE}/*ClhepVersion.h)
if(CLHEP_SOURCE_DIR)
         set(CLHEP_FOUND TRUE)
         #strip to the blank path
         get_filename_component(CLHEP_SOURCE_DIR "${CLHEP_SOURCE_DIR}" PATH)

         find_library(CLHEP_LIBRARY_DIRS
         NAMES
         lib/libCLHEP.so
         PATHS
         ${CLHEP_LIB}
         )

         #strip away the path
         get_filename_component(CLHEP_LIBRARY_DIRS "${CLHEP_LIBRARY_DIRS}" PATH)

         set(CLHEP_INCLUDE_DIRS
             ${CLHEP_SOURCE_DIR})

         file(GLOB_RECURSE CLHEP_LIBRARIES ${CLHEP_LIBRARY_DIRS}/*.so)
else(CLHEP_SOURCE_DIR)
         set(CLHEP_FOUND FALSE)
endif(CLHEP_SOURCE_DIR)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CLHEP DEFAULT_MSG CLHEP_SOURCE_DIR)

# show the PH2_USBINSTLIB_INCLUDE_DIRS and PH2_USBINSTLIB_LIBRARIES variables only in the advanced view
mark_as_advanced(CLHEP_INCLUDE_DIRS CLHEP_LIBRARY_DIRS)
