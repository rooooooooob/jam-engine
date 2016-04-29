# Jam Engine

This is a C++/SFML game engine designed for and largely programmed during 48 hour game jams.

## Features

### Overall Game Structure

* A game is composed of an active je::Level which contains je::Entity instances, which correspond
  to physical game objects.

### Gamepad Support

* In addition to SFML's raw gamepad support, many features such as control-maps with re-assignable
  controls as well as support for easy integration of key-binding (via Controller::Bind) allows
  users to easily let the player re-bind controls for a variety of devices without much effort.
* je::Controller class allows users to map many keys across a variety of devices (mouse, keyboard, gamepad)
  to actions as well as providing functionality for axes/analog stick emulation.
  
### Pathfinding

* Pathfinding is supported and includes grid-based movement, but more movement options will be supported later.


### Collision Detection

* Collision detection between AABBs (axis aligned bounding boxes)(je::CollisionMask), circles (je::CircleMask)
  and arbitrary convex polygons (je::PolygonMask) are supported.
  
### Graphics

* Convenient wrappers around SFML are provided that allow for sprite-based animations (je::Animation)
  and grids of tiles (je::TileGrid). Texture storing is also done via je::TexManager.
* Cameras are supported over top of SFML's sf::View and allow to easily allow views to follow entities
  with support for acceleration and other juicy features.
  
  
## Usage Information

To use this engine with your game simply include the /jam-engine/ folder into your library folder
and link against SFML (tested with SFML2.1, 2.2 and 2.3).