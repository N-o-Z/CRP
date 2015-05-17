#include <TemplateMatcher\TemplateMatcher.h>
#include <iostream>
#include <dirent.h>
#include <fstream>

using namespace CRP;

//Private Functions
int TemplateMatcher::LoadXmlFromPath(const char* path) {

	// TODO: Do error check
	std::ifstream fs(path);
	long size = fs.tellg();
	
	_xml.resize(size+1) ;
	fs.read(&_xml[0],size);

	fs.close();
	return 0;
}


//Public Functions
TemplateMatcher::TemplateMatcher() {

}

TemplateMatcher::TemplateMatcher(char* templates_path) {
	_tmpPath = templates_path;
}

int TemplateMatcher::FindMatch(TemplateParser* report, __out TemplateParser* tmplt) {
	
	DIR* dir;
	dirent* ent;
	dir = opendir(_tmpPath);
	
	while(NULL != (ent = readdir(dir))) {

		std::cout<<ent->d_name<<endl;

		// TODO: in linux check if entry is a file or folder
		// TODO: error check
		// NOTE: we work with file system , but the plan is to get xmls from DB. 
		//		 create interface for load xmls from file system or DB
		LoadXmlFromPath(ent->d_name);

		_temp->SetTemplate(&_xml[0]);
		//logic

		_temp->ComapreToTemplate();

	}
	return 0;
}

TemplateMatcher::~TemplateMatcher() {
	free(_xml);
	//TODO:: Free more?
}