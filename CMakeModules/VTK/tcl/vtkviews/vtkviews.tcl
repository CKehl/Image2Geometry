package require -exact vtkwidgets 5.8

if {[info commands ::vtk::init::require_package] != ""} {
  if {[::vtk::init::require_package vtkViewsTCL 5.8]} {
    package provide vtkviews 5.8
  }
} else {
  if {[info commands vtkGraphLayout] != "" ||
    [::vtk::load_component vtkViewsTCL] == ""} {
    package provide vtkviews 5.8
  }
}
