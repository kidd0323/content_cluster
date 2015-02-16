/***************************************************************
 * Name:      Feature.cpp
 * Purpose:   Extract low-level MPEG-7 descriptors
 * Author:    Muhammet Bastan (bastan@cs.bilkent.edu.tr)
 * Created:   2008
 * Copyright: Muhammet Bastan (http://www.cs.bilkent.edu.tr/~bastan)
 * License:
 * Update: 2009-11-08
 **************************************************************/
#include <iostream>
#include "Feature.h"
#include "Convert.h"

//color
//#include "Extraction/ColorStructureExtraction.h"
#include "ColorLayoutExtraction.h"
//#include "Extraction/ScalableColorExtraction.h"
//#include "Extraction/GoFGoPColorExtraction.h"

//texture
//#include "Extraction/EdgeHistExtraction.h"
//#include "Extraction/HomoTextureExtraction.h"

//shape
//#include "Extraction/ContourShapeExtraction.h"
//#include "Extraction/RegionShapeExtraction.h"


//============================================================================
///				Color Layout Descriptor
//============================================================================
// numberOfYCoeff, numberOfCCoeff: case 3: case 6: case 10: case 15: case 21: case 28: case 64:
XM::ColorLayoutDescriptor* Feature::getColorLayoutD( Frame* f, int numberOfYCoeff, int numberOfCCoeff )
{
	//std::cout << "\nColor Layout Descriptor (CLD):" << std::endl;

	XM::ColorLayoutExtractionTool* cldt = new  XM::ColorLayoutExtractionTool(numberOfYCoeff, numberOfCCoeff);
	XM::ColorLayoutDescriptor* cld = cldt->GetDescriptor();
	cldt->extract( f->image, numberOfYCoeff, numberOfCCoeff);

	//cldi->Print();
	//std::cout << std::endl;

	delete cldt;

	return cld;
}

