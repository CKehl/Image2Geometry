# Directory containing class headers.
SET(VTK_GENERIC_FILTERING_HEADER_DIR "${VTK_INSTALL_PREFIX}/include/vtk-5.8")

# Classes in vtkGenericFiltering.
SET(VTK_GENERIC_FILTERING_CLASSES
  "vtkGenericContourFilter"
  "vtkGenericGeometryFilter"
  "vtkGenericClip"
  "vtkGenericProbeFilter"
  "vtkGenericDataSetTessellator"
  "vtkGenericCutter"
  "vtkGenericGlyph3DFilter"
  "vtkGenericStreamTracer"
  "vtkGenericOutlineFilter")

# Abstract classes in vtkGenericFiltering.
SET(VTK_GENERIC_FILTERING_CLASSES_ABSTRACT)

# Wrap-exclude classes in vtkGenericFiltering.
SET(VTK_GENERIC_FILTERING_CLASSES_WRAP_EXCLUDE)

# Wrap-special classes in vtkGenericFiltering.
SET(VTK_GENERIC_FILTERING_CLASSES_WRAP_SPECIAL)

# Wrappable non-class headers for vtkGenericFiltering.
SET(VTK_GENERIC_FILTERING_WRAP_HEADERS)

# Set convenient variables to test each class.
FOREACH(class ${VTK_GENERIC_FILTERING_CLASSES})
  SET(VTK_CLASS_EXISTS_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_GENERIC_FILTERING_CLASSES_ABSTRACT})
  SET(VTK_CLASS_ABSTRACT_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_GENERIC_FILTERING_CLASSES_WRAP_EXCLUDE})
  SET(VTK_CLASS_WRAP_EXCLUDE_${class} 1)
ENDFOREACH(class)
FOREACH(class ${VTK_GENERIC_FILTERING_CLASSES_WRAP_SPECIAL})
  SET(VTK_CLASS_WRAP_SPECIAL_${class} 1)
ENDFOREACH(class)
