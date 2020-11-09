#include "SubdivisionNode.h"
#include <fstream>
#include <iostream>
#include <map>

Vector3 getAvgVec3(map<int, Vector3> points) {
	Vector3 avg;
	avg.zero();
	map<int, Vector3>::iterator it;

	for (it = points.begin(); it != points.end(); it++) {
		avg += it->second;
	}

	return avg / points.size();
}


SubdivisionNode::SubdivisionNode() {
	numSubdivisions = 0;
	redraw = true;
	he_mesh = new meshparse::mesh();
	std::ifstream infile;
	infile.open("roosterTri.obj");
	meshparse::load_obj(infile, *he_mesh);
}
//Bind all your methods used in this class
//Custom Functions
void SubdivisionNode::_ready() {
	numTriangles = he_mesh->faces.size();
	set_process(true);
	set_process_input(true);

	catmull_clark(1); //TODO: This does something bad enough to the mesh that calling more then once causes the whole thing to crash

	//Copy the half edge mesh to the vertex structure to render it
	for (std::vector<face *>::iterator it = he_mesh->faces.begin(); it != he_mesh->faces.end(); ++it) {
		Vector3 v0, v1, v2;
		v0 = (*it)->e->vert->loc;
		vertices.push_back(Vector2(v0.x, v0.y));
		v1 = (*it)->e->next->vert->loc;
		vertices.push_back(Vector2(v1.x, v1.y));
		v2 = (*it)->e->next->next->vert->loc;
		vertices.push_back(Vector2(v2.x, v2.y));
		colors.append(Color(1, 0, 0));
		colors.append(Color(1, 1, 0));
		colors.append(Color(0, 0, 1));
	}
	_vertices = vertices;
	_colors = colors;

	////6 vertices for the two triangles
	//vertices.push_back(Vector2(0, 100));
	//vertices.push_back(Vector2(100, 0));
	//vertices.push_back(Vector2(0, 0));
	//vertices.push_back(Vector2(0, 100));
	//vertices.push_back(Vector2(100, 100));
	//vertices.push_back(Vector2(100, 0));
	//colors.append(Color(1, 1, 1));
	//colors.append(Color(0, 1, 0));
	//colors.append(Color(0, 0, 1));
	//colors.append(Color(1, 0, 0));
	//colors.append(Color(0, 0, 0));
	//colors.append(Color(0, 1, 0));
	////Copying the data into another set
	//_vertices.push_back(Vector2(0, 100));
	//_vertices.push_back(Vector2(100, 0));
	//_vertices.push_back(Vector2(0, 0));
	//_vertices.push_back(Vector2(0, 100));
	//_vertices.push_back(Vector2(100, 100));
	//_vertices.push_back(Vector2(100, 0));
	//_colors.append(Color(1, 1, 1));
	//_colors.append(Color(0, 1, 0));
	//_colors.append(Color(0, 0, 1));
	//_colors.append(Color(1, 0, 0));
	//_colors.append(Color(0, 0, 0));
	//_colors.append(Color(0, 1, 0));
}

void SubdivisionNode::catmull_clark(int numDivisions) {
	if (numDivisions == 0) {
		return;
	}
	map<int, VertexData> verticeData;

	//Loop through faces, calulate new face points, and edge points. Record data for vertices
	meshparse::mesh *newMesh = new meshparse::mesh();
	int vertexID = 0;
	int faceID = 0;
	int edgeID = 0;
	for (std::vector<face *>::iterator it = he_mesh->faces.begin(); it != he_mesh->faces.end(); ++it) {
		Vector3 facePoint = (*it)->centroid();

		edge *e0 = (*it)->e;
		int n = 0;
		do {
			Vector3 edgePoint = (e0->vert->loc + e0->next->vert->loc + facePoint + e0->pair->f->centroid()) / 4;
			Vector3 prevEdgePoint = (e0->previous()->vert->loc + e0->vert->loc + facePoint + e0->pair->f->centroid()) / 4;

			//Create new vertices to add to mesh
			vertex *a = new vertex(++vertexID, e0->vert->loc);
			vertex *b = new vertex(++vertexID, edgePoint);
			vertex *c = new vertex(++vertexID, facePoint);
			vertex *d = new vertex(++vertexID, prevEdgePoint);

			//Add the new vertices to the mesh
			newMesh->verteces.push_back(a);
			newMesh->verteces.push_back(b);
			newMesh->verteces.push_back(c);
			newMesh->verteces.push_back(d);

			//Create edges to add to mesh. Innitalize them with correct data
			edge *e1 = new edge(++edgeID, a);
			edge *e2 = new edge(++edgeID, b);
			edge *e3 = new edge(++edgeID, c);
			edge *e4 = new edge(++edgeID, d);

			e1->next = e2;
			e2->next = e3;
			e3->next = e4;
			e4->next = e1;

			edge *re1 = new edge(++edgeID, b, e1);
			edge *re2 = new edge(++edgeID, c, e2);
			edge *re3 = new edge(++edgeID, d, e3);
			edge *re4 = new edge(++edgeID, a, e4);

			re1->next = re2;
			re2->next = re3;
			re3->next = re4;
			re4->next = re1;

			//Give vertices their edges
			a->e = e1;
			b->e = e2;
			c->e = e3;
			c->e = e4;

			//Add new edges to the mesh
			newMesh->edges.push_back(e1);
			newMesh->edges.push_back(e2);
			newMesh->edges.push_back(e3);
			newMesh->edges.push_back(e4);

			newMesh->edges.push_back(re1);
			newMesh->edges.push_back(re2);
			newMesh->edges.push_back(re3);
			newMesh->edges.push_back(re4);

			//Create new face and add to mesh
			face *f0 = new face(++faceID, e1);
			newMesh->faces.push_back(f0);

			//Add the edge and face points to the record for this vertex
			if (verticeData[(e0->vert->id)].vertex == NULL) {
				verticeData[(e0->vert->id)].vertex = a;
			}
			if (!verticeData[(e0->vert->id)].edgePoints.count(e0->id)) {
				verticeData[(e0->vert->id)].edgePoints[e0->id] = edgePoint;
			}
			if (!verticeData[(e0->vert->id)].facePoints.count((*it)->id)) {
				verticeData[(e0->vert->id)].facePoints[(*it)->id] = facePoint;
			}

			n++;
			e0 = e0->next;
		} while (e0 != (*it)->e);

	}

	
	//Modify existing vertices based on calculated edge points
	map<int, VertexData>::iterator it;
	for (it = verticeData.begin(); it != verticeData.end(); it++) {

		//https://rosettacode.org/wiki/Catmull%E2%80%93Clark_subdivision_surface
		//Eh, maybe that is all the face points?
		float edgeCount = (float)it->second.edgePoints.size();
		float m1 = (edgeCount - 3.0) / edgeCount;
		float m2 = 1.0 / edgeCount;
		float m3 = 2.0 / edgeCount;

		Vector3 avgFacePoint = getAvgVec3(it->second.facePoints);
		Vector3 avgEdgePoint = getAvgVec3(it->second.edgePoints);

		Vector3 weightedAvg = it->second.vertex->loc * m1 + m2 * avgFacePoint + m3 * avgEdgePoint;

		it->second.vertex->loc = weightedAvg;
	}

	he_mesh = newMesh;

	catmull_clark(numDivisions - 1);
}


void SubdivisionNode::_update() {
}
void SubdivisionNode::_draw() {
	if (redraw) {
		Ref<ArrayMesh> a = memnew(ArrayMesh);
		Array arrays;
		arrays.resize(ArrayMesh::ARRAY_MAX);
		arrays[ArrayMesh::ARRAY_VERTEX] = _vertices; // required
		arrays[ArrayMesh::ARRAY_COLOR] = _colors;
		//optionally u can add texture coordinates and attach a texture from the editor to this arraymesh in the scene
		a->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, arrays);
		if (this != NULL)
			this->set_mesh(a);
		redraw = false;
	}
}
void SubdivisionNode::_input(InputEvent *e) {
	if (e->is_action_pressed("ui_up")) {
		numSubdivisions += 1;
		if (numSubdivisions > 5)
			numSubdivisions = 1;
		redraw = true;
	}
}
void SubdivisionNode::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_PROCESS: {
			if (Input::get_singleton()->is_action_pressed("ui_up")) {
				numSubdivisions += 1;
				if (numSubdivisions > 5)
					numSubdivisions = 1;
				redraw = true;
				SceneTree::get_singleton()->set_input_as_handled();
			}
			_update();

			update();
		} break;
		case NOTIFICATION_READY: {
			_ready();
		} break;
		case NOTIFICATION_DRAW: {
			_draw();
		} break;
	}
}
