all-linux:
	conan install . --build=missing && make build-linux
all-windows:
	conan install . --build=missing && make build-windows
build-windows:
	mkdir build && cd build && cmake .. -G "Visual Studio 15 2017" && make && make install && cd ..
build-linux:
	mkdir build && cd build && cmake .. && make && make install && cd ..
install-windows:
	make all-windows && make clean
install-linux:
	make all-linux && make clean
clean:
	rm build rm conan*info* graph_info.json conan.lock -rf
