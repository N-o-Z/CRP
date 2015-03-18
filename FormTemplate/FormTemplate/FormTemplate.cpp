// FormTemplate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "OCRheaders.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    char *outText;

    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    //if (api->Init(NULL, "eng")) {
	if (api->Init(NULL, "heb")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open input image with leptonica library
    //Pix *image = pixRead("../test.pdf");
	Pix *image = pixRead("../test.tif");
    api->SetImage(image);
    // Get OCR result
    //outText = api->GetUTF8Text();
    //printf("OCR output:\n%s", outText);
	 outText = api->GetHOCRText(0);
	 printf("hOCR output:\n%s", outText);
    // Destroy used object and release memory
    api->End();
    pixDestroy(&image);
	ofstream myfile;
	myfile.open ("output.xml");
	myfile << outText;
	myfile.close();
    return 0;
}

