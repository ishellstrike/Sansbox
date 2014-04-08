#ifndef AutoVersion_h__ 
#define AutoVersion_h__ 
#include <string>
#define Ver "v0.0.1-4-gddcf9e7";
#define Time "1396973903";
class AutoVersion { 
public: 
	static std::string GetTitle();
private:
	static std::string title_;
static bool ready_;
};
#endif // AutoVersion_h__   
