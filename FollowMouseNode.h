//insert the Headername here
#ifndef FOLLOWMOUSENODE_H
#define FOLLOWMOUSENODE_H

#include "scene/main/node.h"
#include "scene/2d/node_2d.h"
#include "scene/2d/sprite.h"
#include <string>

class FollowMouseNode : public Sprite {
	GDCLASS(FollowMouseNode, Sprite);

protected:
  static void _bind_methods();

public:
  FollowMouseNode();

  
  int loadImage(String fileName);
  void setLocation(int x, int y);

};

#endif
