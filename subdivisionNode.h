//insert the Headername here
#ifndef SUBDIVISIONNODE_H
#define SUBDIVISIONNODE_H
#include "core/math/triangle_mesh.h"
#include "core/os/input.h"
#include "he_mesh.h"
#include "objparse.h"
#include "scene/2d/mesh_instance_2d.h"
#include "scene/2d/node_2d.h"
#include "scene/resources/mesh.h"
#include <set>
#include <map>
using namespace meshparse;

Vector3 getAvgVec3(map<int, Vector3> points);

struct VertexData {
	vertex *vertex = NULL;
	map<int, Vector3> edgePoints;
	map<int, Vector3> facePoints;

	
};



class SubdivisionNode : public MeshInstance2D {
	GDCLASS(SubdivisionNode, MeshInstance2D);

protected:
	int numSubdivisions;
	int numTriangles;
	meshparse::mesh *he_mesh;
	//original
	PoolVector2Array vertices;
	PoolColorArray colors;
	//updated
	PoolVector2Array _vertices;
	PoolColorArray _colors;

	bool redraw;
	

public:
	SubdivisionNode();
	void _notification(int p_what);
	void _update();
	void _ready();
	void _draw();
	void _input(InputEvent *e);
	void catmull_clark(int numDivisions);
};
#endif
