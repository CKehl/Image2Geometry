REM run this batch to build all samples
REM output files are saved in ..\bin
REM --Issam Ali (http://issamsoft.com)
@echo make bin directory
mkdir ..\bin
copy ..\windows\Release\giflib5.dll ..\bin\
@echo ====================
@echo complile giftext
cl /D_WIN32 /D_MS_VISUAL_STUDIO giftext.c getarg.c qprintf.c utilhlpr.c /Fe..\bin\giftext.exe /I ..\lib /link ..\windows\Release\giflib5.lib 
@echo ====================
@echo compile gifbuild
cl /D_WIN32 /D_MS_VISUAL_STUDIO gifbuild.c getarg.c qprintf.c utilhlpr.c /Fe..\bin\gifbuild.exe /I ..\lib /link ..\windows\Release\giflib5.lib 
@echo ====================
@echo compile gif2rgb
cl /D_WIN32 /D_MS_VISUAL_STUDIO gif2rgb.c getarg.c qprintf.c utilhlpr.c /Fe..\bin\gif2rgb.exe /I ..\lib /link ..\windows\Release\giflib5.lib 
@echo ====================
@echo compile giftool
cl /D_WIN32 /D_MS_VISUAL_STUDIO /DWIN32 giftool.c getarg.c qprintf.c utilhlpr.c getopt.c /Fe..\bin\giftool.exe /I ..\lib /link ..\windows\Release\giflib5.lib 
@echo ====================
@echo compile gifclrmp
cl /D_WIN32 /D_MS_VISUAL_STUDIO gifclrmp.c getarg.c qprintf.c utilhlpr.c /Fe..\bin\gifclrmp.exe /I ..\lib /link ..\windows\Release\giflib5.lib 
@echo ====================
@echo compile gifbg
cl /D_WIN32 /D_MS_VISUAL_STUDIO gifbg.c getarg.c qprintf.c utilhlpr.c /Fe..\bin\gifbg.exe /I ..\lib /link ..\windows\Release\giflib5.lib 
@echo ====================
@echo compile giffix
cl /D_WIN32 /D_MS_VISUAL_STUDIO giffix.c getarg.c qprintf.c utilhlpr.c /Fe..\bin\giffix.exe /I ..\lib /link ..\windows\Release\giflib5.lib 
@echo ====================
@echo compile gifecho
cl /D_WIN32 /D_MS_VISUAL_STUDIO gifecho.c getarg.c qprintf.c utilhlpr.c /Fe..\bin\gifecho.exe /I ..\lib /link ..\windows\Release\giflib5.lib 
@echo ====================
@echo compile giffilter
cl /D_WIN32 /D_MS_VISUAL_STUDIO giffilter.c getarg.c qprintf.c utilhlpr.c /Fe..\bin\giffilter.exe /I ..\lib /link ..\windows\Release\giflib5.lib 
@echo ====================
@echo compile gifcolor
cl /D_WIN32 /D_MS_VISUAL_STUDIO gifcolor.c getarg.c qprintf.c utilhlpr.c /Fe..\bin\gifcolor.exe /I ..\lib /link ..\windows\Release\giflib5.lib 
@echo ====================
@echo compile gifinto
cl /D_WIN32 /D_MS_VISUAL_STUDIO gifinto.c getarg.c qprintf.c utilhlpr.c /Fe..\bin\gifinto.exe /I ..\lib /link ..\windows\Release\giflib5.lib 
@echo ====================
@echo compile gifwedge
cl /D_WIN32 /D_MS_VISUAL_STUDIO gifwedge.c getarg.c qprintf.c utilhlpr.c /Fe..\bin\gifwedge.exe /I ..\lib /link ..\windows\Release\giflib5.lib 
@echo ====================
@echo compile gifsponge
cl /D_WIN32 /D_MS_VISUAL_STUDIO gifsponge.c getarg.c qprintf.c utilhlpr.c /Fe..\bin\gifsponge.exe /I ..\lib /link ..\windows\Release\giflib5.lib 
