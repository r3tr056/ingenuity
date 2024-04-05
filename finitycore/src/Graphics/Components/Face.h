#pragma once

#include <vector>
#include <GL/GL.h>

class Face {
private:
	std::vector<GLuint> mVertexIndices;

public:
	void addVertexIndex(GLuint index) { mVertexIndices.push_back(index); }
};