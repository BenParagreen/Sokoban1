#pragma once

//project includes
#include "GridObject.h"

class Box : public GridObject
{

public:
	Box();

	bool AttemptPush(sf::Vector2i _direction);

	bool GetStored();

private:
	bool m_stored;
};
