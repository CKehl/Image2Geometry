# This installs two files, app.exe and logo.ico, creates a start menu shortcut, builds an uninstaller, and
# adds uninstall information to the registry for Add/Remove Programs
 
# To get started, put this script into a folder with the two files (app.exe, logo.ico, and license.rtf -
# You'll have to create these yourself) and run makensis on it
 
# If you change the names "app.exe", "logo.ico", or "license.rtf" you should do a search and replace - they
# show up in a few places.
# All the other settings can be tweaked by editing the !defines at the top of this script
!define APPNAME "Image2Geometry"
!define DESCRIPTION "Scripted program for registring natural photographs to triangular textured surface ; ONLY FOR ACADEMIC USE"
# These three must be integers
!define VERSIONMAJOR 1
!define VERSIONMINOR 0
!define VERSIONBUILD 0
# These will be displayed by the "Click here for support information" link in "Add/Remove Programs"
# It is possible to use "mailto:" links in here to open the email client
!define HELPURL "https://github.com/CKehl/Image2Geometry/wiki" # "Support Information" link
!define UPDATEURL "https://github.com/CKehl/Image2Geometry" # "Product Updates" link
!define ABOUTURL "http://christian.kehl-foto.de/blog" # "Publisher" link
# This is the size (in kB) of all the files copied into "Program Files"
!define INSTALLSIZE 242581
 
RequestExecutionLevel admin ;Require admin rights on NT6+ (When UAC is turned on)
 
InstallDir "$PROGRAMFILES\${APPNAME}"
 
# rtf or txt file - remember if it is txt, it must be in the DOS text format (\r\n)
LicenseData "LICENSE.rtf"
# This will be in the installer/uninstaller's title bar
Name "${APPNAME}"
#Icon "logo.ico"
outfile "Image2Geometry-64bit-setup.exe"
 
!include LogicLib.nsh
 
# Just three pages - license agreement, install location, and installation
page license
page directory
Page instfiles
 
!macro VerifyUserIsAdmin
UserInfo::GetAccountType
pop $0
${If} $0 != "admin" ;Require admin rights on NT4+
        messageBox mb_iconstop "Administrator rights required!"
        setErrorLevel 740 ;ERROR_ELEVATION_REQUIRED
        quit
${EndIf}
!macroend
 
function .onInit
	setShellVarContext all
	!insertmacro VerifyUserIsAdmin
functionEnd
 
section "install"
	# Files for the install directory - to build the installer, these should be in the same directory as the install script (this file)
	setOutPath $INSTDIR
	# Files added here should be removed by the uninstaller (see section "uninstall")
	file /a "Image2Geometry.exe"
	file /a "libarmadillo.dll"
	file /a "libboost_atomic-gcc74-mt-x64-1_66.dll"
	file /a "libboost_chrono-gcc74-mt-x64-1_66.dll"
	file /a "libboost_date_time-gcc74-mt-x64-1_66.dll"
	file /a "libboost_filesystem-gcc74-mt-x64-1_66.dll"
	file /a "libboost_program_options-gcc74-mt-x64-1_66.dll"
	file /a "libboost_regex-gcc74-mt-x64-1_66.dll"
	file /a "libboost_system-gcc74-mt-x64-1_66.dll"
	file /a "libboost_thread-gcc74-mt-x64-1_66.dll"
	file /a "libcurl-x64.dll"
	file /a "libflann.dll"
	file /a "libflann_cpp.dll"
	file /a "libflann_cpp-gd.dll"
	file /a "libfreetype-6.dll"
	file /a "libgif-7.dll"
	file /a "libgio-2.0-0.dll"
	file /a "libglib-2.0-0.dll"
	file /a "libgmodule-2.0-0.dll"
	file /a "libgobject-2.0-0.dll"
	file /a "libgthread-2.0-0.dll"
	file /a "libHalf.dll"
	file /a "libIex-2_2.dll"
	file /a "libIexMath-2_2.dll"
	file /a "libIlmImf-2_2.dll"
	file /a "libIlmImfUtil-2_2.dll"
	file /a "libIlmThread-2_2.dll"
	file /a "libImath-2_2.dll"
	file /a "libjasper-4.dll"
	file /a "libjpeg-62.dll"
	file /a "liblzma-5.dll"
	file /a "libopencv_calib3d2413.dll"
	file /a "libopencv_contrib2413.dll"
	file /a "libopencv_core2413.dll"
	file /a "libopencv_features2d2413.dll"
	file /a "libopencv_flann2413.dll"
	file /a "libopencv_gpu2413.dll"
	file /a "libopencv_highgui2413.dll"
	file /a "libopencv_imgproc2413.dll"
	file /a "libopencv_legacy2413.dll"
	file /a "libopencv_ml2413.dll"
	file /a "libopencv_nonfree2413.dll"
	file /a "libopencv_objdetect2413.dll"
	file /a "libopencv_ocl2413.dll"
	file /a "libopencv_photo2413.dll"
	file /a "libopencv_stitching2413.dll"
	file /a "libopencv_superres2413.dll"
	file /a "libopencv_video2413.dll"
	file /a "libopencv_videostab2413.dll"
	file /a "libOpenThreads.dll"
	file /a "libosg.dll"
	file /a "libosgAnimation.dll"
	file /a "libosgDB.dll"
	file /a "libosgFX.dll"
	file /a "libosgGA.dll"
	file /a "libosgManipulator.dll"
	file /a "libosgParticle.dll"
	file /a "libosgPresentation.dll"
	file /a "libosgQt.dll"
	file /a "libosgShadow.dll"
	file /a "libosgSim.dll"
	file /a "libosgTerrain.dll"
	file /a "libosgText.dll"
	file /a "libosgUI.dll"
	file /a "libosgUtil.dll"
	file /a "libosgViewer.dll"
	file /a "libosgVolume.dll"
	file /a "libosgWidget.dll"
	file /a "libpng16-16.dll"
	file /a "libtiff.dll"
	file /a "libtiffxx.dll"
	file /a "libturbojpeg-0.dll"
	file /a "libxml2.dll"
	file /a "libxml2-2.dll"
	file /a "libzlib.dll"
	file /a "opencv_ffmpeg2413_64.dll"
	file /a "shaderGamma.frag"
	file /a "shaderGamma.vert"
	file /r "osgPlugins-3.3.8"
	file /r "w2c"
	file /a "LICENSE.rtf"
	# Add any other files for the install directory (license files, app data, etc) here
 
	# Uninstaller - See function un.onInit and section "uninstall" for configuration
	writeUninstaller "$INSTDIR\uninstall.exe"
 
	# Start Menu
	createDirectory "$SMPROGRAMS\${APPNAME}"
	#createShortCut "$SMPROGRAMS\${COMPANYNAME_SHORT}\${APPNAME}.lnk" "$INSTDIR\app.exe" "" "$INSTDIR\logo.ico"
	createShortCut "$SMPROGRAMS\${APPNAME}\Uninstall Scripts.lnk" "$INSTDIR\uninstall.exe" "" ""
 
	# Registry information for add/remove programs
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "DisplayName" "${APPNAME} - ${DESCRIPTION}"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "UninstallString" "$\"$INSTDIR\uninstall.exe$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "QuietUninstallString" "$\"$INSTDIR\uninstall.exe$\" /S"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "InstallLocation" "$\"$INSTDIR$\""
	#WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${COMPANYNAME} ${APPNAME}" "DisplayIcon" "$\"$INSTDIR\logo.ico$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "Publisher" "Dr. Christian Kehl"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "HelpLink" "$\"${HELPURL}$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "URLUpdateInfo" "$\"${UPDATEURL}$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "URLInfoAbout" "$\"${ABOUTURL}$\""
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "DisplayVersion" "$\"${VERSIONMAJOR}.${VERSIONMINOR}.${VERSIONBUILD}$\""
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "VersionMajor" ${VERSIONMAJOR}
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "VersionMinor" ${VERSIONMINOR}
	# There is no option for modifying or repairing the install
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "NoModify" 1
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "NoRepair" 1
	# Set the INSTALLSIZE constant (!defined at the top of this script) so Add/Remove Programs can accurately report the size
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}" "EstimatedSize" ${INSTALLSIZE}
sectionEnd
 
# Uninstaller
 
function un.onInit
	SetShellVarContext all
 
	#Verify the uninstaller - last chance to back out
	MessageBox MB_OKCANCEL "Permanantly remove ${APPNAME}?" IDOK next
		Abort
	next:
	!insertmacro VerifyUserIsAdmin
functionEnd
 
section "uninstall"
 
	# Remove Start Menu launcher
	delete "$SMPROGRAMS\${APPNAME}\Uninstall Scripts.lnk"
	# Try to remove the Start Menu folder - this will only happen if it is empty
	rmDir "$SMPROGRAMS\${APPNAME}"
 
	# Remove files
	delete $INSTDIR\osgPlugins-3.3.8\*.*
	rmDir $INSTDIR\osgPlugins-3.3.8
	delete $INSTDIR\w2c\*.*
	rmDir $INSTDIR\w2c
	delete $INSTDIR\*.dll
	delete $INSTDIR\shaderGamma.vert
	delete $INSTDIR\shaderGamma.frag
	delete $INSTDIR\LICENSE.rtf
	delete $INSTDIR\Image2Geometry.exe
	#delete $INSTDIR\logo.ico
 
	# Always delete uninstaller as the last action
	delete $INSTDIR\uninstall.exe
 
	# Try to remove the install directory - this will only happen if it is empty
	rmDir $INSTDIR
 
	# Remove uninstaller information from the registry
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APPNAME}"
sectionEnd