#include "followMouseNode.h"

FollowMouseNode::FollowMouseNode(){}

//Bind all your methods used in this class
void FollowMouseNode::_bind_methods(){
  ClassDB::bind_method(D_METHOD("add", "a", "b"), &FollowMouseNode::add);
  ClassDB::bind_method(D_METHOD("loadImage", "fileName"), &FollowMouseNode::loadImage);
}


//Custom Functions
int FollowMouseNode::add(int a, int b) {
	set_position(Point2(a, b));
  return a+b;
}


int FollowMouseNode::loadImage(String fileName) {
	Ref<ImageTexture> tex;
	ImageTexture *imgTex = new ImageTexture();
	Error error = imgTex->load("res://" + fileName);

	set_texture(imgTex);
	return error;
}
