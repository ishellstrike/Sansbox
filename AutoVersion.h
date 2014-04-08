#ifndef AutoVersion_h__ 
#define AutoVersion_h__ 
#include <string>
#define Ver "v0.0.1-3-g42df87d";
#define Time "1396486121";
class AutoVersion { 
public: 
	static std::string GetTitle();
private:
	static std::string title_;
static bool ready_;
};
#endif // AutoVersion_h__   
