
#include <vector>

namespace CRP
{
	using namespace std;

	#define MAX_DESC 20 

	typedef struct _BBOX_COORDINATES
	{
		int x_1 ;
		int y_1 ;
		int x_2 ; 
		int y_2 ;
	}BBOX_COORDINATES;

	class WordBox
	{
	private:
		string _data;
		BBOX_COORDINATES coordinates;

	public:
		WordBox(string data, int x_1, int y_1, int x_2, int y_2);
		const BBOX_COORDINATES& GetCoordinates();
		const string& GetWordAsString();
		const char*	GetWordAsCstr();
	};

	class LineBox
	{
	private:
		vector<WordBox*> _words;
		BBOX_COORDINATES coordinates;
		int _lineNumber;
	public:
		LineBox(int LineNumber, int x_1, int y_1, int x_2, int y_2);
		const BBOX_COORDINATES& GetCoordinates();
		void addWord(WordBox* word);
		string GetLineAsStr();
		int GetLineNumber();
		const string& GetWordByIndex(unsigned int index);
	};

	class ParagraphBox
	{
	private:
		vector<LineBox*> _lines;
		BBOX_COORDINATES coordinates;

	public:
		ParagraphBox(int x_1, int y_1, int x_2, int y_2);
		const BBOX_COORDINATES& GetCoordinates();
		void addLine(LineBox* line);
		bool GetLine(int lineNumber, const LineBox* line);
		string GetParagraphAsStr();
	};

	class TemplateParser
	{
	private:
		typedef struct _BBOX_TEMP_LINE_INFO
		{
			BBOX_COORDINATES coordinates ;
			int lineNum;
			char description[MAX_DESC] ;
		}BBOX_TEMP_LINE_INFO;

		int _threshold ; 

		vector<BBOX_TEMP_LINE_INFO*> _linesBboxInfo ;

	public:
		TemplateParser();
	
		bool SetTemplate(char* tmp) ; 

		int SetThreshold(int level) ;

		bool ComapreToTemplate(char* hOcrXml);

	};
}