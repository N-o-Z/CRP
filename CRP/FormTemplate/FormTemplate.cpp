// FormTemplate.cpp : A test application for the modules
//

#include "stdafx.h"
#include <CRP\ImageParser\ImageParser.h>

int main()
{
    int result = -1;
	ImageParser parser;

	parser = ImageParser();
	result = parser.Init("heb");
	result = parser.ReadImage("../test.tif");
	result = parser.CreateHOCR();
	parser.TextToFile("../outputFile.xml");
	


    return 0;
}

