# - Try to find Assimp
# Once done, this will define
#
#  ASSIMP_FOUND
#  ASSIMP_INCLUDE_DIR
#  ASSIMP_LIBRARIES

FIND_PATH( ASSIMP_INCLUDE_DIR assimp/mesh.h
  /usr/include
  /usr/local/include
  /sw/include
  /opt/local/include
  ${CMAKE_SOURCE_DIR}/assimp/include
  DOC "The directory where assimp/mesh.h resides"
)

FIND_LIBRARY( ASSIMP_LIBRARIES
  NAMES ASSIMP assimp
  PATHS
  /usr/lib64
  /usr/lib
  /usr/local/lib64
  /usr/local/lib
  /sw/lib
  /opt/local/lib
  ${CMAKE_SOURCE_DIR}/assimp/lib
  DOC "The ASSIMP library"
)

IF (ASSIMP_INCLUDE_DIR)
  SET( ASSIMP_FOUND 1 CACHE STRING "Set to 1 if ASSIMP is found, 0 otherwise")
  MESSAGE(STATUS "Found ASSIMP: ${ASSIMP_LIBRARIES}")
  MESSAGE(STATUS "Found ASSIMP_INCLUDE_DIR: ${ASSIMP_INCLUDE_DIR}")
ELSE (ASSIMP_INCLUDE_DIR)
  SET( ASSIMP_FOUND 0 CACHE STRING "Set to 1 if ASSIMP is found, 0 otherwise")
ENDIF (ASSIMP_INCLUDE_DIR)

MARK_AS_ADVANCED( ASSIMP_FOUND )
