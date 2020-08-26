all-windows:
	conan install . --build=missing && make build-windows
build-windows:
	mkdir build && cd build && cmake .. -G "Visual Studio 14 2015" -A x64 && "C:\Program Files (x86)\MSBuild\14.0\Bin\MSBuild.exe" /p:Configuration=Release life_game.sln && dir && move .\bin\life_game.exe ..\ && cd ..
install-windows:
	make all-windows && make clean-windows
clean-windows:
	rmdir /Q/S build && del conan*info* graph_info.json conan.lock
all-linux:
	conan install . --build=missing && make build-linux
build-linux:
	mkdir build && cd build && cmake .. && make && make install && cd ..
install-linux:
	make all-linux && make clean-linux
clean-linux:
	rm build rm conan*info* graph_info.json conan.lock -rf
