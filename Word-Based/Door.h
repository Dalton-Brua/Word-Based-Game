#pragma once

class Door {

private:
	bool locked;
	bool isLocked();

public:
	Door();
	void travel(Door, Door);

};
