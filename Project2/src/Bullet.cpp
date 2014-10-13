//
// Bullet.cpp
//

// Engine includes.
#include "GraphicsManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"

// Game includes.
#include "Bullet.h"
#include "Saucer.h"

Bullet::Bullet(Position hero_pos, int velocity) {

  // Set object properties.
  setType("Bullet");
  setXVelocity(velocity);		// move 1 space right every frame

  auto& resMgr = ResourceManager::getInstance();
  setSprite(resMgr.getSprite("bullet"));
  setSpriteSlowdown(4);
  // Set object type.
  setBox(Box(Position(0, 0), getSprite()->getWidth(), getSprite()->getHeight()));

  // Set starting location, based on hero's position passed in.
  Position pos(hero_pos.getX()+ 3 * velocity, hero_pos.getY());
  setPosition(pos);
}

// Handle event.
// Return 0 if ignored, else 1.
int Bullet::eventHandler(Event *p_e) {

  if (p_e->getType() == DF_OUT_EVENT) {
    out();
    return 1;
  }

  if (p_e->getType() == DF_COLLISION_EVENT) {
    EventCollision *p_collision_event = static_cast <EventCollision *> (p_e);
    hit(p_collision_event);
    return 1;
  }

  // If get here, have ignored this event.
  return 0;
}

// If bullet moves outside world, mark self for deletion.
void Bullet::out() {
  WorldManager &world_manager = WorldManager::getInstance();
  world_manager.markForDelete(this);
}

// If bullet hits Saucer, mark Saucer and bullet for deletion.
void Bullet::hit(EventCollision *p_c) {
  WorldManager &world_manager = WorldManager::getInstance();
  if ((p_c->getObject1()->getType() != "Platform"))
  {
	  world_manager.markForDelete(p_c->getObject1());
  }
  if ((p_c->getObject2()->getType() != "Platform"))
  {
	  world_manager.markForDelete(p_c->getObject2());
  }
}

void Bullet::draw() {
	Object::draw();
//   GraphicsManager &graphics_manager = GraphicsManager::getInstance();
//   graphics_manager.drawCh(getPosition(), BULLET_CHAR, COLOR_BLUE); 
}
