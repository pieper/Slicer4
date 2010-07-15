project(vtkSlicerEMSegmentModuleLogic)

#
# See CMake/Slicer3ModuleLogicMacros.cmake for details
#

SET(module_logic_name "${PROJECT_NAME}")

# The header '${PROJECT_NAME}Export.h' will be automatically configured.
SET(module_logic_export_directive "VTK_SLICER_EMSEGMENT_MODULE_LOGIC_EXPORT")

# Additional directories to include
SET(module_logic_include_directories
  )

# Source files
SET(module_logic_SRCS
  vtkSlicerEMSegmentLogic.cxx
  )

# Additional Target libraries
SET(module_logic_target_libraries
  ${ITK_LIBRARIES}
  )


Slicer3_build_module_logic(
  NAME ${module_logic_name}
  EXPORT_DIRECTIVE ${module_logic_export_directive}
  INCLUDE_DIRECTORIES ${module_logic_include_directories}
  SRCS ${module_logic_SRCS}
  TARGET_LIBRARIES ${module_logic_target_libraries}
  )