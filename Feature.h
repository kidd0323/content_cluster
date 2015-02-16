/***************************************************************
 * Name:      Feature.h
 * Purpose:   Extract low-level MPEG-7 descriptors
 * Author:    Muhammet Bastan (mubastan@gmail.com, bastan@cs.bilkent.edu.tr)
 * Created:   2008
 * Copyright: Muhammet Bastan (http://www.cs.bilkent.edu.tr/~bastan)
 * License:
 * Update: 2009-11-08
 * Update: 2009-11-18
 * Update: 2011-02-02 (upgrade to OpenCV 2.2 -- Mat)
 * TODO: modify the Feature class or provide a new class which
 *       does not use static functions, for efficiency in memory management
 **************************************************************/

/************************************************************************************
					How to use this class
					---------------------
1. include this header:		#include "Feature.h"
2. intantiate a Frame object: Frame* frame = new Frame( width, height, true, false, false );			// width-height of the input image/frame
   set the image			  frame->setImage( img );								// Mat& img // input image
					or use this: Frame* frame = new Frame( img );					// Mat& img // input image

3.a) Extract feature from the whole frame:
		XM::ColorStructureDescriptor* csd = Feature::getColorStructureD(frame);
		use the descriptor values in csd ( have a look at the descriptor classes under ./Descriptors/ directory)

NOTE: use the namespace XM to refer to the descriptors rather than declaring "using namespace XM",
      it may mess up with other namespaces!

3.b) Extract features from an arbitrary region - need to set the region mask
		set the mask for the region: frame->setMaskAll( Mat& mask, int regionID, 255, 0 );	// regionID: ID/value of the region in the mask image (1,2,3,..)
		compute the feature:
		XM::ColorStructureDescriptor* csd = Feature::getColorStructureD(frame);

4. when you are done with the computed descriptor, relase it: delete csd;		(avoid memory leakage)

IMPORTANT NOTES:

1. If you set a mask for the frame to extract features from arbitrary regions, and after that, if you want to extract features
   from the whole frame you need to reset the mask! Use: frame->resetMaskAll();
   Therefore, it is better (more efficient) to extract the global features from the whole frame first, and then set mask for arbitrary regions..

2. Homogeneous Texture Descriptor, Feature::getHomogeneousTextureD, uses grayscale image as input, therefore you need to convert your color image to gray first
   Suppose you have the RGB color image 'Mat img',
			// create a single channel image 'Mat gray' to store the grayscale image
			Mat gray = Mat( img.rows, img.cols, CV_8UC1 );
			// convert the input image from RGB to gray
			cvtColor(img, gray, CV_BGR2GRAY);
			// Create the frame (with only the gray image)
			Frame* frame = new Frame(width, height, false, true, false);
			// set the grayscale image of the frame
			frame->setGray( gray );
			// extract the descriptor
			XM::HomogeneousTextureDescriptor* htd = Feature::getHomogeneousTextureD( frame, true );	// true:full layer
            // do whatever you like with `htd`
            // ...
            // release the descriptor
            delete htd;

 ************************************************************************************/

#ifndef _FEATURE_H_
#define _FEATURE_H_

#include <vector>

#include "Frame.h"

#include "Descriptors.h"

typedef enum
{
    MP7_CSD, MP7_SCD, MP7_DCD, MP7_CLD,
    MP7_EHD, MP7_HTD, MP7_GOF, MP7_FRD, MP7_MAc
} MP7FeatureType;


class Feature
{
public:
	
	// Color Layout Descriptor (CLD)
	// numberOfYCoeff/numberOfCCoeff: (3, 6, 10, 15, 21, 28, 64)	( DC(1) + AC )
	static XM::ColorLayoutDescriptor* getColorLayoutD( Frame* f, int numberOfYCoeff = 64, int numberOfCCoeff = 28 );

	// Dominant Color Descriptor (CLD)
	// normalize: normalize values to MPEG-7 range (color:0-32, variance:0,1, weight:0-32)?
	//            if false, (color:RGB values[0-255], variance:as computed, weight:0-100 percent)
	// variance: compute the variance?
	// spatial: compute the spatial coherency
	// bin1, bin2, bin3: bin numbers to quantize the dominat color values
	static XM::DominantColorDescriptor* getDominantColorD( Frame* f, bool normalize = true, bool variance = true, bool spatial = true, int bin1 = 32, int bin2 = 32, int bin3 = 32 );
};


#endif
