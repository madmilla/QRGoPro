@Author: L. Veenendaal

Test code for using a GoPro Hero 3 to read QR codes.
You will need to have opencv 2.x and zBar installed to use this code.

#note to self

To compile the goPro cpp file run the following command:
g++ main.cpp $(pkg-config --cflags --libs opencv zbar) -lopencv_gpu
./a.out