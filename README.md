@Author: L. Veenendaal

Test code for using a GoPro Hero 3 to read QR codes.
You will need to have opencv 2.x and zBar installed to use this code.

You need to connect with the GoPro over Wifi. Then you need to check what the router/gateways ip is.
route -n -> linux
ipconfig -> windows
rm -rf 	-> mac

#note to self

To compile the goPro cpp file run the following command:

g++ main.cpp $(pkg-config --cflags --libs opencv zbar) -lopencv_gpu

Then you can run the following file:

./a.out