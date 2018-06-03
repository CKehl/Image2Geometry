package require -exact vtkfiltering 5.8

if {[info commands ::vtk::init::require_package] != ""} {
  if {[::vtk::init::require_package vtkGraphicsTCL 5.8]} {
    package provide vtkgraphics 5.8
  }
} else {
  if {[info commands vtkAxes]  != "" ||
    [::vtk::load_component vtkGraphicsTCL] == ""} {
    package provide vtkgraphics 5.8
  }
}
