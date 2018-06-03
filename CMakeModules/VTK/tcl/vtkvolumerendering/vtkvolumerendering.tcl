package require -exact vtkrendering 5.8

if {[info commands ::vtk::init::require_package] != ""} {
  if {[::vtk::init::require_package vtkVolumeRenderingTCL 5.8]} {
    package provide vtkvolumerendering 5.8
  }
} else {
  if {[info commands vtkEncodedGradientShader] != "" ||
    [::vtk::load_component vtkVolumeRenderingTCL] == ""} {
    package provide vtkvolumerendering 5.8
  }
}
