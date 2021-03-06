///
/// The game world manager
///

#pragma once

#include "Box.h"
#include "Circle.h"
#include "Line.h"
#include "Manager.h"
#include "ObjectList.h"
#include "Position.h"
#include "SceneGraph.h"

class WorldManager : public Manager
{

private:
	WorldManager();               // Private since a singleton.
	WorldManager(WorldManager const&);  // Don't allow copy.
	void operator=(WorldManager const&); // Don't allow assignment.
	ObjectList updates;           // List of all Objects in world to update.
	ObjectList deletions;         // List of all Objects to delete.
	Box boundary;                 ///< World boundary.
	Box view;
	Object* p_view_following;

public:
	/// Get the one and only instance of the WorldManager.
	static WorldManager &getInstance()
	{
		static WorldManager instance;
		return instance;
	}

	/// Accept all user-defined events (returns true).
	/// Return false for other engine events.
	bool isValid(string event_type) const;

	/// Startup game world (initialize everything to empty).
	/// Return 0.
	int startUp();

	/// Shutdown game world (delete all game world Objects).
	void shutDown();

	/// Add Object to world.
	/// Return 0 if ok, else -1.
	int insertObject(Object *p_o);

	/// Remove Object from world.
	/// Return 0 if ok, else -1.
	int removeObject(Object *p_o);

	/// Return list of all Objects in world.
	/// If inactive is true, include inactive Objects.
	ObjectList getAllObjects() const;

	/// Indicate Object is to be deleted at end of current game loop.
	/// Return 0 if ok, else -1.
	int markForDelete(Object *p_o);

	/// Update world.
	/// Update positions of Objects based on their velocities.
	/// Lastly, delete Objects marked for deletion.
	void update();

	/// Draw all Objects in view.
	/// Draw bottom up, from -MAX_ALTITUDE to MAX_ALTITUDE.
	void draw();

	/// Move Object. 
	/// If no collision with solid, move ok else don't move Object.
	/// If Object is Spectral, move ok.
	/// If move ok, adjust screen if following this Object.
	/// Return 0 if move ok, else -1 if collision with solid.
	int moveObject(Object *p_o, Position where);

	/// Return list of Objects collided with at Position 'where'.
	/// Collisions only with solid Objects.
	/// Does not consider if p_o is solid or not.
	ObjectList isCollision(Object *p_o, Position where) const;

	/// Return Object with indicated id.
	/// NULL if Object is not found.
	Object *objectWithId(int id) const;

	/// Return list of all Objects at Position 'where'.  
	/// Does include bounding boxes. Return empty list if none found.
	ObjectList objectsAtPosition(Position where) const;

	/// Return list of all Objects in Box.
	/// Does include bounding boxes. Return empty list if none found.
	ObjectList objectsInBox(Box box) const;

	/// Return a list of all Objects on line from point1 to point2.
	/// Does include bounding boxes. Return empty list if none found.
	ObjectList objectsOnLine(Line line) const;

	/// Return a list of all Objects in circle.
	/// Does include bounding boxes. Return empty list if none found.
	ObjectList objectsInCircle(Circle circle) const;

	/// Get game world boundary.
	Box getBoundary() const
	{
		return this->boundary;
	}

	/// Set game world boundary.
	void setBoundary(Box new_boundary)
	{
		this->boundary = new_boundary;
	}

	/// Get player view of game world.
	Box getView() const
	{
		return this->view;
	}

	/// Set player view of game world.
	void setView(Box new_view)
	{
		this->view = new_view;
	}

	/// Set view to center screen on Object.
	/// Set to NULL to stop following.
	/// If Object not legit, return -1 else return 0.
	int setViewFollowing(Object *p_new_view_following);

	/// Set view to center screen on Position view_pos.
	/// View edge will not go beyond world boundary.
	void setViewPosition(Position view_pos);
	// 
	//   /// Return reference to SceneGraph.
	// 	 SceneGraph &getSceneGraph() const
	// 	 {
	// 		 return (const SceneGraph)scene_graph;
	// 	 }
};
