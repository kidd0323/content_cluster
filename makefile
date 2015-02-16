CLD: main1.o imgutil.o ColorLayout.o ColorQuant.o ColorSpace.o Convert.o vopio.o Frame.o  ColorSpaceExtraction.o  ColorLayoutExtraction.o Feature.o
	g++ main1.o imgutil.o ColorLayout.o ColorQuant.o ColorSpace.o Convert.o vopio.o Frame.o ColorSpaceExtraction.o ColorLayoutExtraction.o Feature.o -L /usr/local/lib -lopencv_core -lcv -lm -lhighgui -lcvaux -lml -o CLD

main1.o: main1.cpp Feature.h 
	g++ -I /usr/local/include/opencv -c main1.cpp

ColorLayout.o: ColorLayout.cpp ColorLayout.h
	g++ -c ColorLayout.cpp

ColorQuant.o: ColorQuant.cpp ColorQuant.h 
	g++ -c ColorQuant.cpp

ColorSpace.o: ColorSpace.cpp ColorSpace.h
	g++ -c ColorSpace.cpp 

Convert.o: Convert.cpp Convert.h vopio.h
	g++ -I /usr/local/include/  -c Convert.cpp
vopio.o: vopio.cpp vopio.h
	g++ -c vopio.cpp 
Frame.o: Frame.cpp Frame.h
	g++ -c Frame.cpp
Feature.o: Feature.cpp Feature.h Convert.h ColorLayout.h 
	g++ -c Feature.cpp
colorSpaceExtraction.o: ColorSpaceExtraction.cpp ColorSpaceExtraction.h
	g++ -c ColorSpaceExtraction.cpp ColorSpaceExtraction.h
ColorLayoutExtraction.o: ColorLayoutExtraction.cpp ColorLayoutExtraction.h
	g++ -c ColorLayoutExtraction.cpp 

imgutil.o:imgutil.c imgutil.h
	g++ -c imgutil.c
clean:
	rm -f haha *.o


