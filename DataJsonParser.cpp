#include "DataJsonParser.h"
#include <fstream>
#include <json/writer.h>
#include <json/reader.h>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp> 
#include <glog/logging.h>
#include "BlockData.h"
namespace fs = boost::filesystem; 


DataJsonParser::DataJsonParser(void)
{
}


DataJsonParser::~DataJsonParser(void)
{
}

std::map<std::string, BlockData>* DataJsonParser::Parse(std::string s)
{
	std::ifstream configFile(s);
	//name = configFileName;

	if (!configFile.is_open())
	{
		LOG(WARNING) << s << " file open error";
		return false;
	}


	Json::Value root;
	Json::Reader reader;

	LOG(INFO) << s << " parsing.";

	bool parsingSuccessful = reader.parse(configFile, root );
	if ( !parsingSuccessful )
	{
		configFile.close();
		LOG(INFO) << s << " data json file corrupted.";
		LOG(INFO) << "     " << reader.getFormatedErrorMessages();
		return nullptr;
	} else {
		for(int i =0; i< root.size(); i++){
			auto t = root[i];

		}
	}
}

std::map<std::string, BlockData> DataJsonParser::ParseDirectory(std::string s)
{
	fs::path targetDir(s); 

	fs::directory_iterator it(targetDir), eod;
	BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod))  
	{ 
		if(is_regular_file(p) && p.extension() == ".json")
		{
			Parse(p.relative_path().string());
		} 
	}
}
