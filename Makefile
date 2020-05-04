all:
	conan install . --build=missing && mkdir build && cd build && cmake .. && make && make install && cd ..
install:
	make all && make clean
clean:
	rm build rm conan*info* graph_info.json conan.lock -rf
