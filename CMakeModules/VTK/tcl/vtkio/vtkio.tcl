package require -exact vtkfiltering 5.8

if {[info commands ::vtk::init::require_package] != ""} {
  if {[::vtk::init::require_package vtkIOTCL 5.8]} {
    package provide vtkio 5.8
  }
} else {
  if {[info commands vtkBMPReader] != "" ||
    [::vtk::load_component vtkIOTCL] == ""} {
    package provide vtkio 5.8
  }
}
