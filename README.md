# ACN-KEMY

The major part of this project will deal with understanding the Kemy generator and also
ns-3 queue discipline parent/template class. After which, the project will look into the
modification of Kemy source code to automatically generate queue disciplines in ns-3.

## Project Members  
Sharath Savasere 15CO244  
Harsh Shah       15CO243  
Satish Mhetre    15CO242  


### Steps to Reproduce
1. Replace the 'traffic-control' folder in ns-3.27/src with the one in this repository.
2. Protobuf Installation.
	1. ```sudo apt-get install autoconf automake libtool curl make g++ unzip```
	2. ```git clone https://github.com/google/protobuf.git```
	3. ```cd protobuf```
	4. ```git submodule update --init --recursive```
	5. ```./autogen.sh```
3. To build and install the C++ Protocol Buffer runtime and the Protocol Buffer compiler (protoc) execute the following:
	1. ```./configure```
	2. ```make```
	3. ```make check```
	4. ```sudo make install```
	5. ```sudo ldconfig```
4. In the ns-3.27/src/traffic-control/model/kemy/ directory run the following command:
	1. ```protoc --cpp_out=. dna.proto```
5. In a terminal run the following commands 
	1. ```pkg-config --cflags protobuf``` 
	2. ```pkg-config --libs protobuf```
6. Run ```./waf configure CXXFLAGS='Output of First Command' LINKFLAGS='Output of Second Command'```
7. Run ```./waf```
