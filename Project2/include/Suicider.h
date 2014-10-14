#include "EventCollision.h"
#include "Object.h"

class Suicider : public Object {

private:

	//void kbd(EventKeyboard *keyboard_event);

	void step();
	void activate(EventCollision* _eventCollision);
	//void fire();
	int fire_slowdown;
	int fire_countdown;
public:
	Suicider();
	Suicider(int x, int y);
	~Suicider();
	void fire();
	int eventHandler(Event *p_e);
	void draw();
};
