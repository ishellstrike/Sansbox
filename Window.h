#ifndef Window_h__
#define Window_h__
#include "DrawableComponent.h"
#include "Vector.h"

class Window : public DrawableComponent {
public:
	Window();
	Window(Vector2 pos_, Vector2 size_);
	~Window();

	Vector2 pos;
	Vector2 size;
	virtual void Draw();

	virtual void Update();

};
#endif // Window_h__
