
#include "TemplateParser.h"
#include <string>
#include <sstream>
#include <algorithm>
#include <TinyXml2\Inc\tinyxml2.h>

namespace CRP
{

	ParagraphBox::ParagraphBox(int x_1, int y_1, int x_2, int y_2)
	{
		coordinates.x_1 = x_1 ;
		coordinates.y_1 = y_1 ;
		coordinates.x_2 = x_2 ;
		coordinates.y_2 = y_2 ;
	}

	const BBOX_COORDINATES& ParagraphBox::GetCoordinates()
	{
		return (coordinates); 
	}

	void ParagraphBox::addLine(LineBox* line)
	{
		_lines.push_back(line);
	}

	bool ParagraphBox::GetLine(int lineNumber, const LineBox* line)
	{
		auto line_it = find_if(_lines.begin(),  _lines.end(), [&] (LineBox* tempLine) -> bool
			{
				return (lineNumber == tempLine->GetLineNumber()) ;
			}
		);

		if (line_it != _lines.end())
		{
			line = &(**line_it) ;
			
			return (true);
		}

		return (false);
	}

	string ParagraphBox::GetParagraphAsStr()
	{
		string paraStr;
		
		paraStr.clear();

		if (_lines.size() == 0)
		{
			return (paraStr);
		}

		auto line_it = _lines.begin() ;
		paraStr.append((&(**line_it))->GetLineAsStr());

		for_each(line_it,  _lines.end(), [&paraStr] (LineBox* line) -> void
			{
				paraStr.append("\n");
				paraStr.append(line->GetLineAsStr());
			}
		);

		return (paraStr);
	}

	LineBox::LineBox(int LineNumber, int x_1, int y_1, int x_2, int y_2)
	{
		coordinates.x_1 = x_1 ;
		coordinates.y_1 = y_1 ;
		coordinates.x_2 = x_2 ;
		coordinates.y_2 = y_2 ;

		_lineNumber = LineNumber ;
	}

	const BBOX_COORDINATES& LineBox::GetCoordinates()
	{
		return (coordinates); 
	}

	void LineBox::addWord(WordBox* word)
	{
		_words.push_back(word);
	}

	string LineBox::GetLineAsStr()
	{
		string lineStr;
		
		lineStr.clear();

		if (_words.size() == 0)
		{
			return (lineStr);
		}

		auto word_it = _words.begin() ;
		lineStr.append((&(**word_it))->GetWordAsString());

		for_each(word_it,  _words.end(), [&lineStr] (WordBox* word) -> void
			{
				lineStr.append(" ");
				lineStr.append(word->GetWordAsString());
			}
		);

		return (lineStr);
	}

	int LineBox::GetLineNumber()
	{
		return (_lineNumber);
	}

	const string& LineBox::GetWordByIndex(unsigned int index)
	{
		if (index > _words.size())
		{
			// need to throw exception
		}

		return (_words[index]->GetWordAsString()); 
	}


	WordBox::WordBox(string word, int x_1, int y_1, int x_2, int y_2)
	{
		coordinates.x_1 = x_1 ;
		coordinates.y_1 = y_1 ;
		coordinates.x_2 = x_2 ;
		coordinates.y_2 = y_2 ;
	}

	const BBOX_COORDINATES& WordBox::GetCoordinates()
	{
		return (coordinates); 
	}

	const string& WordBox::GetWordAsString()
	{
		return (_data) ;
	}

	const char*	WordBox::GetWordAsCstr()
	{
		return (_data.c_str());
	}

	// constructor
	TemplateParser::TemplateParser()
	{
		_threshold = 0 ; 
	}
	
	int TemplateParser::SetThreshold(int level)
	{
		int oldTrashHold = _threshold ;
		_threshold = level ; 

		return (oldTrashHold);
	}

	bool TemplateParser::SetTemplate(char* temple)
	{
		tinyxml2::XMLDocument doc;

		if (temple == nullptr)
		{
			return (false);
		}

		if (!(doc.LoadFile(temple)))
		{
			return (false);
		}


		tinyxml2::XMLElement* paragraph =  doc.FirstChildElement("p") ;
		tinyxml2::XMLElement* line = paragraph->FirstChildElement("span") ; 

		for (; line; line=line->NextSiblingElement())
		{
			const char* class_att = line->Attribute("class");

			if (!class_att)
			{
				continue;
			}
			else if(strcmp("ocr_line", class_att))
			{
				continue;
			}

			// TODO: verfy the attributes.
			const char* lineId = line->Attribute("id");
			const char* lineDesc = line->Attribute("Description");
			const char* bbox = line->Attribute("title");

			BBOX_TEMP_LINE_INFO* tempSt = new BBOX_TEMP_LINE_INFO(); 
			tempSt->lineNum = atoi(&lineId[5/*MAGIC NUM*/]) ; 
			memcpy(tempSt->description, lineDesc, sizeof(lineDesc)+1) ;

			string bboxString(bbox) ;
			string buf; // Have a buffer string
			stringstream ss(bboxString); // Insert the string into a stream
			vector<string> tokens; // Create vector to hold our words
			while (ss >> buf)
				tokens.push_back(buf);

			// TODO: verfy that the 4 coordinates are in the vector.
			tempSt->coordinates.x_1 = atoi (tokens[1].c_str());
			tempSt->coordinates.y_1 = atoi (tokens[2].c_str());
			tempSt->coordinates.x_2 = atoi (tokens[3].c_str());
			tempSt->coordinates.y_2 = atoi (tokens[4].c_str());

			_linesBboxInfo.push_back(tempSt);
		}

		return (true);
	}
	
	bool TemplateParser::ComapreToTemplate(char* hOcrXml)
	{
		tinyxml2::XMLDocument doc;

		if (hOcrXml == nullptr)
		{
			return (false);
		}

		if (!(doc.LoadFile(hOcrXml)))
		{
			return (false);
		}

		// 1. load xml file into vectore (BBOX_INFO)
		// 2. go over the the template vector
		//	2.1 for each entry in the vector 
		//		2.1.1 compare the look for the coordinates in the xml usint the threshold (substract with ABS)
		//		2.1.2 usinf the description look for expected data on the bbox and give a score for each match
		// 3. cala the overall matches and return if the xml similare to the tamplate

		return (true); 
	}
}