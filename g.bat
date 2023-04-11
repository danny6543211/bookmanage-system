rmdir /s/q build
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make.exe all
move server.exe ../server.exe
move demo.exe ../demo.exe