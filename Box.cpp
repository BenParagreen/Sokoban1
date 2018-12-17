//project inlcude
#include "Box.h"
#include "Framework/AssetManager.h"
#include "Level.h"
#include "StorageObject.h"

Box::Box()
	: GridObject()
	, m_stored(false)
{
	m_Sprite.setTexture(AssetManager::GetTexture("graphics/box.png"));
	m_BlocksMovement = true;
}

bool Box::AttemptPush(sf::Vector2i _direction)
{
	//attempt to move the box in the given direction
		//get the current position
		//calculate the target position
	sf::Vector2i TargetPos = m_GridPosition + _direction;
	// check if the space is empty
	// get list of  objects in our target position
	std::vector<GridObject*> TargetCellContents = m_Level->GetObjectAt(TargetPos);
	// check if any of those objects block movement
	bool blocked = false;
	for (int i = 0; i < TargetCellContents.size(); ++i)
	{
		if (TargetCellContents[i]->GetBlockedMovement() == true)
		{
			blocked = true;
		}
	}
	//if empty, move there
	if (blocked == false)
	{
		bool moveSucceded =  m_Level->MoveObjectTo(this, TargetPos);

		// If box successfully moved
		if (moveSucceded == true)
		{
			//Check if box is stored

			//Assume box is not stored
			m_stored - false;

			// Loop through the contents and see if a storage object is found
			for (int i = 0; i < TargetCellContents.size(); ++i)
			{
				//Check if this element in the vector is a storage object by using dynamic cast
				StorageObject* storageObject = dynamic_cast<StorageObject*>(TargetCellContents[i]);

				//If dynamic cast succeeds, it will NOT be a nullptr
				if (storageObject != nullptr)
				{
					//Box is Stored
					m_stored = true;

					//Check if the Level is complete 
					m_Level -> CheckComplete();
				}
			}
			//Change sprite if stored
			if (m_stored)
			{
				m_Sprite.setTexture(AssetManager::GetTexture("graphics/boxStored.png"));
			}
			else
			{
				m_Sprite.setTexture(AssetManager::GetTexture("graphics/box.png"));
			}
		}

		return moveSucceded;
	}
	//if movement is blocked, do nothing, return false
	return false;
}

bool Box::GetStored()
{
	return m_stored;
}