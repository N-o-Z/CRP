// FormTemplate.cpp : A test application for the modules
//

#include "stdafx.h"
#include <ImageParser\ImageParser.h>

using namespace CRP;

int main()
{
    int result = -1;

	ImageParser parser;

	parser = ImageParser();
	result = parser.Init("heb");
	result = parser.ReadImage("../testData/elec1.tif");
	result = parser.CreateHOCR();
	parser.TextToFile("../testData/electric_temp.xml");
	result = parser.ReadImage("../testData/HM1.tif");
	result = parser.CreateHOCR();
	parser.TextToFile("../testData/hotmobile_temp.xml");
	result = parser.ReadImage("../testData/mun1.tif");
	result = parser.CreateHOCR();
	parser.TextToFile("../testData/municipality_temp.xml");


    return 0;
}

