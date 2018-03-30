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
2. Install google protobuf from- https://github.com/google/protobuf
3. In a terminal run the following commands 
	1. ```pkg-config --cflags protobuf``` 
	2. ```pkg-config --libs protobuf```
4. Run ```./waf configure CXXFLAGS=[Output of First Command] LINKFLAGS=[Output of Second Command]```
5. Run ```./waf```
