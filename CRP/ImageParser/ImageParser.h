#include "OCRheaders.h"

namespace CRP
{
	#define SUCCESS				0
	#define E_INIT_FAILED		1
	#define E_INIT_TWICE		2
	#define E_INVALID_PATH		3
	#define E_PROCESSING		4
	#define E_NOTEXT			5
	
	/**
	*/
	class ImageParser {
		
		private:
		// Tesseract object pointer
		tesseract::TessBaseAPI *api;
		// Pix object for the tesseract image processing
		Pix* image;
	
		public:
		// Contains the image processing output
		char* oText;
	
		/**
		* Image Parser Constructor
		*
		*/
		ImageParser();
	
		/**
		* Init Image Parser
		* Init tesseract::TessBaseAPI object and what else?
		*
		*/
		int Init(char* lang);
	
		/**
		* Init Image Parser
		* Init tesseract::TessBaseAPI object and what else?
		*
		*/
		int ReadImage(char* imagePath);
	
		/**
		* Create HOCR
		* Gets the HOCR processing of the image
		*
		*/
		int CreateHOCR();
		/**
		* Get the string created by the image processing to file
		*
		*/
	
		int TextToFile(char* filename);
	
		/**
		* Image Parser Destructor
		*
		*/
		~ImageParser();
	
	};

}