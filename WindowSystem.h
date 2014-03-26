#ifndef WindowSystem_h__
#define WindowSystem_h__
#include "Window.h"
#include <vector>
#include "TextureManager.h"
#include "DrawableComponent.h"
#include "SpriteBatch.h"

class WindowSystem : public DrawableComponent {
public:
	std::vector<Window> windows;
	WindowSystem(SpriteBatch sb);

	virtual void Draw()
	{
		if(windows.size() > 0)
		{
			for (int i =0; i < windows.size(); i++)
			{
				windows.at(i).Draw();
			}
		}
	}

	virtual void Update()
	{
	
	}

	static Texture bp;
	static SpriteBatch sb;
	
};

WindowSystem::WindowSystem(SpriteBatch sb_)
{
	Texture t;
	t.Load("bp.png");
	bp = t;
	sb = sb_;
}

#endif // WindowSystem_h__
