@echo off

rem .\cp_cmake.bat 32 or .\cp_cmake.bat 64

rem test le nombre d'argument passe


if "%1" == "" (
	echo Il manque un argument 32 ou 64 decrivant l architecture
	) else (

	rem CMakeLists.txt
	copy ..\DIST_cmake\CMakeLists.txt ..\..\CMakeLists.txt
	copy Install.txt ..\..\Install.txt
	copy ..\DIST_cmake\SRC\CMakeLists.txt ..\..\SRC\CMakeLists.txt
	copy ..\DIST_cmake\SRC\MIXMOD\CMakeLists.txt ..\..\SRC\MIXMOD\CMakeLists.txt
	copy ..\DIST_cmake\SRC\MIXMOD_IOSTREAM\CMakeLists.txt ..\..\SRC\MIXMOD_IOSTREAM\CMakeLists.txt
	copy ..\DIST_cmake\SRC\NEWMAT\CMakeLists.txt ..\..\SRC\NEWMAT\CMakeLists.txt
	copy ..\DIST_cmake\SRC\GUI\CMakeLists.txt ..\..\SRC\GUI\CMakeLists.txt
	copy ..\DIST_cmake\SRC\GUI\MIXMOD_MVC\CMakeLists.txt ..\..\SRC\GUI\MIXMOD_MVC\CMakeLists.txt
	copy ..\DIST_cmake\SRC\GUI\MIXMOD_QT\CMakeLists.txt ..\..\SRC\GUI\MIXMOD_QT\CMakeLists.txt
	copy ..\DIST_cmake\LIB\CMakeLists.txt ..\..\LIB\thirdparty\CMakeLists.txt
	
	rem LIB (64 or 32 bits)
	copy ..\DIST_cmake\LIB\LIB%1\*.dll ..\..\LIB\thirdparty
)


