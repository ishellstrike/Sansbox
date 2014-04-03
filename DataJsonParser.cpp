#include "DataJsonParser.h"
#include <fstream>
#include <json/writer.h>
#include <json/reader.h>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp> 
#include <glog/logging.h>
#include "BlockData.h"
#include <map>
namespace fs = boost::filesystem; 


DataJsonParser::DataJsonParser(void)
{
}


DataJsonParser::~DataJsonParser(void)
{
}

bool DataJsonParser::Parse(std::string s, std::map<std::string, BlockData*>* blocks)
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
		for(int i =0; i< root.size() - 2; i+= 2){
			auto key = root[i];
			auto value = root[i+1];
			BlockData* data = new BlockData();
			(*blocks)[key.asString()] = data;
			data->Name = value.get("Name", "error").asString();
			data->Id = key.asString();
			auto Spawn = value["ItemSpawn"];
			if(Spawn.size() > 0) {
				for (auto j = Spawn.begin(); j != Spawn.end(); ++j)
				{
					auto SpawnGroup = (*j);
					DropGroup dg;
					dg.Max = SpawnGroup.get("Max", 2).asInt();
					dg.Min = SpawnGroup.get("Min", 1).asInt();
					dg.Repeat = SpawnGroup.get("Repeat", 1).asInt();
					dg.Prob = SpawnGroup.get("Prob", 50).asInt();
					auto Ids = SpawnGroup["Ids"];
					for (auto k = Ids.begin(); k != Ids.end(); ++k)
					{
						dg.Ids.push_back((*k).asString());
					}
				}
			}
		}
	}
}

void DataJsonParser::ParseDirectory(std::string s, std::map<std::string, BlockData*>* blocks)
{
	fs::path targetDir(s); 

	fs::directory_iterator it(targetDir), eod;
	BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod))  
	{ 
		if(is_regular_file(p) && p.extension() == ".json")
		{
			Parse(p.relative_path().string(), blocks);
		} 
	}
}
