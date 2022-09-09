#pragma once

class Door {

private:
	bool locked = false;
	bool isLocked();

public:
	Door() {};
	Door(bool l);
	void travel(Door door);

};
