#include <TemplateParser\TemplateParser.h>
#include <vector>

namespace CRP
{
	class TemplateMatcher {
	
	private:
		char* _tmpPath;
		vector <char> _xml;
		TemplateParser* _temp;
		int LoadXmlFromPath(const char* path);

	public:
	
		TemplateMatcher();
		TemplateMatcher::TemplateMatcher(char* templates_path);
		int FindMatch(TemplateParser* report, __out TemplateParser* tmplt);
		~TemplateMatcher();

	};
}