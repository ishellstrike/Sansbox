#ifndef LineBatch_h__
#define LineBatch_h__
#include "BufferArray.h"

class LineBatch {
private:
	BufferArray buffer;
	double zorder;
public:
	LineBatch();
	~LineBatch();
	void AddLine(vec2 a, vec2 b, int size);
	void Draw();
	void Clear();
};

#endif // LineBatch_h__
