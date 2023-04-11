cd build
cmake -G "MinGW Makefiles" ..
mingw32-make.exe all
move server.exe ../server.exe
move client.exe ../client.exe