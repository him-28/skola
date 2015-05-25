#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Vector2f
{
	float x, y;
};

struct Vector3f
{
	float x, y, z;
};

struct Triangle
{
	unsigned int v0, t0, n0;
	unsigned int v1, t1, n1;
	unsigned int v2, t2, n2;
};

class ObjLoader
{
private:
	vector<Vector3f> vertices;
	vector<Vector3f> normals;
	vector<Vector3f> texcords;
	vector<Triangle> triangles;

private:
	void DecrementIndices(Triangle & triangle);

public:
	bool Load(const char * filename);

	vector<Vector3f> & GetVertices();

	vector<Vector3f> & GetNormals();

	vector<Vector3f> & GetTexcords();

	vector<Triangle> & GetTriangles();

	void PrintLog();
};

#endif
