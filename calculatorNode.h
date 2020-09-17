//insert the Headername here
#ifndef CALCULATORNODE_H
#define CALCULATORNODE_H

#include "scene/main/node.h"
#include "scene/2d/node_2d.h"
#include "scene/2d/sprite.h"
#include <string>

class CalculatorNode : public Sprite {
	GDCLASS(CalculatorNode, Sprite);

protected:
  static void _bind_methods();

public:
  CalculatorNode();

  int add(int a, int b);
  int sub(int a, int b);
  int mul(int a, int b);
  int div(int a, int b);
  int loadImage(String fileName);

};

#endif
