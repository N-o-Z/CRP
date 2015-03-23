

#include <iostream>
#include <fstream>
#include "ImageParser.h"

/**
* Image Parser Constructor
*
*/
ImageParser::ImageParser() {
	api = NULL;
	image = NULL;
	oText = NULL;
}

/**
* Init Image Parser
* Init tesseract::TessBaseAPI object and what else?
*
*/
int ImageParser::Init(char* lang) {
	
	if(NULL != api) {
		//TODO:: Create a logging mechanism
		fprintf(stderr, "Tesseract already init.\n");
		return E_INIT_TWICE;
	}

	api = new tesseract::TessBaseAPI();
	// Initialize tesseract-ocr with English, without specifying tessdata path
	if (  api->Init("../../tesseract/tessdata/", lang)) {
		//TODO:: Create a logging mechanism
		fprintf(stderr, "Could not initialize tesseract.\n");
		return E_INIT_FAILED;
	}
	//TODO:: What else to do?
	return SUCCESS;
}
/**
* Init Image Parser
* Init tesseract::TessBaseAPI object and what else?
*
*/
int ImageParser::ReadImage(char* imagePath) {
	if(NULL != image) {
		pixDestroy(&image);
	}
	image = pixRead(imagePath);
	if(NULL == image) {
		//TODO:: Create a logging mechanism
		fprintf(stderr, "Invalid image path.\n");
		return E_INVALID_PATH;
	}
	api->SetImage(image);
	return SUCCESS;
}

/**
* Create HOCR
* Gets the HOCR processing of the image
*
*/
int ImageParser::CreateHOCR() {
	oText = api->GetHOCRText(0);
	if(NULL == oText) {
		//TODO:: Create a logging mechanism
		fprintf(stderr, "Could not create output text.\n");
		return E_PROCESSING;
	}
	return SUCCESS;
}

/**
* Get the string created by the image processing to file
*
*/
int ImageParser::TextToFile(char* filename) {

	std::ofstream oFile;

	if(NULL == oText) {
		//TODO:: Create a logging mechanism
		fprintf(stderr, "No text was created.\n");
		return E_NOTEXT;
	}
	oFile.open(filename);
	oFile<<oText;
	oFile.close();
	
	return SUCCESS;
}

/**
* Image Parser Destructor
*
*/
ImageParser::~ImageParser() {
	if(NULL != image) {
		pixDestroy(&image);
	}
	if(NULL != api) {
		api->End();
	}
}