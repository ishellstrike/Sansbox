#pragma once
#pragma once
#ifndef JButton_h__
#define JButton_h__
#include "WComponent.h"
#include <string>

class JButton : public WComponent
{
public:
	JButton(void);
	JButton(Vector2 pos_, Vector2 size_);
	~JButton(void);

	void Draw();
	void Update();
	Vector2 GlobalPos();
	std::string Text;
	WContainer* parent;
private:
	Vector2 pos;
	Vector2 size;
	bool aimed;
};
#endif // JButton_h__

