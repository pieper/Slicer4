project(EMSegmentCommandLineExecutable)

#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.8.2)
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# See http://cmake.org/cmake/help/cmake-2-8-docs.html#section_Policies for details
#-----------------------------------------------------------------------------

SET(project_policies
  CMP0001 # NEW: CMAKE_BACKWARDS_COMPATIBILITY should no longer be used.
  CMP0002 # NEW: Logical target names must be globally unique.
  CMP0003 # NEW: Libraries linked via full path no longer produce linker search paths.
  CMP0004 # NEW: Libraries linked may NOT have leading or trailing whitespace.
  CMP0005 # NEW: Preprocessor definition values are now escaped automatically.
  CMP0006 # NEW: Installing MACOSX_BUNDLE targets requires a BUNDLE DESTINATION.
  CMP0007 # NEW: List command no longer ignores empty elements.
  CMP0008 # NEW: Libraries linked by full-path must have a valid library file name.
  CMP0009 # NEW: FILE GLOB_RECURSE calls should not follow symlinks by default.
  CMP0010 # NEW: Bad variable reference syntax is an error.
  CMP0011 # NEW: Included scripts do automatic cmake_policy PUSH and POP.
  CMP0012 # NEW: if() recognizes numbers and boolean constants.
  CMP0013 # NEW: Duplicate binary directories are not allowed.
  CMP0014 # NEW: Input directories must have CMakeLists.txt
  )
FOREACH(policy ${project_policies})
  IF(POLICY ${policy})
    CMAKE_POLICY(SET ${policy} NEW)
  ENDIF()
ENDFOREACH()

# --------------------------------------------------------------------------
# Find Slicer3

if(NOT Slicer_SOURCE_DIR)
  find_package(Slicer3 REQUIRED)
  include(${Slicer_USE_FILE})
  slicer3_set_default_install_prefix_for_external_projects()
endif(NOT Slicer_SOURCE_DIR)

# --------------------------------------------------------------------------
# Include dirs

include_directories(
  ${EMSegment_SOURCE_DIR}
  ${EMSegment_SOURCE_DIR}/MRML
  ${EMSegment_SOURCE_DIR}/Algorithm
  ${EMSegment_SOURCE_DIR}/CommandLineApplication
  ${Slicer_Libs_INCLUDE_DIRS}
  ${Slicer_Base_INCLUDE_DIRS}
  )

# --------------------------------------------------------------------------
# Sources

set(CLP_MODULE EMSegmentCommandLine)
set(${CLP_MODULE}_SOURCE
  ${CLP_MODULE}.cxx
  )
generateclp(
  ${CLP_MODULE}_SOURCE 
  ${CLP_MODULE}.xml)

# --------------------------------------------------------------------------
# Build and install the exe

add_executable(${CLP_MODULE} ${${CLP_MODULE}_SOURCE})
slicer3_set_plugins_output_path(${CLP_MODULE})
target_link_libraries(
  ${CLP_MODULE}
  EMSegment
  vtkCommon
  )

slicer3_install_plugins(${CLP_MODULE})

