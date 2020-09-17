#include "followMouseNode.h"

FollowMouseNode::FollowMouseNode(){}

//Bind all your methods used in this class
void FollowMouseNode::_bind_methods(){
  ClassDB::bind_method(D_METHOD("loadImage", "fileName"), &FollowMouseNode::loadImage);
  ClassDB::bind_method(D_METHOD("setLocation", "x", "y"), &FollowMouseNode::setLocation);
}

int FollowMouseNode::loadImage(String fileName) {
	Ref<ImageTexture> tex;
	ImageTexture *imgTex = new ImageTexture();
	Error error = imgTex->load("res://" + fileName);

	set_texture(imgTex);
	return error;
}

void FollowMouseNode::setLocation(int x, int y) {
	set_position(Point2(x, y));
}
