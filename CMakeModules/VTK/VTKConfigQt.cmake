#-----------------------------------------------------------------------------
#
# VTKConfigQt.cmake - VTK Qt CMake configuration file for external projects.
#
# This file is configured by VTK and used by the VTKConfig.cmake module
# to load VTK's Qt settings for an external project.

# exports for Qt4
SET(VTK_QT_RCC_EXECUTABLE "/usr/bin/rcc")

# exports for Qt3/Qt4
SET(VTK_QT_MOC_EXECUTABLE "/usr/bin/moc-qt4")
SET(VTK_QT_UIC_EXECUTABLE "/usr/bin/uic-qt4")
SET(VTK_QT_QMAKE_EXECUTABLE "/usr/bin/qmake")

