#pragma once
#include <iostream>
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

namespace shape
{
	class Shape;

	class Shape
	{
	public:
		int cnt{};
		GLfloat speed{};
		bool isActive{};
		glm::mat3 direcTionV3{};

		virtual void SetSpeed(GLfloat s_speed);

		virtual void SetDic(glm::mat3 dic);

		virtual void SetIsActive(bool is);

		virtual void MoveShape() {};
	};

	typedef struct {
		float x, y, z;
	} Vertex;

	typedef struct {
		unsigned int v1, v2, v3;  // Vertex indices
		//unsigned int n1, n2, n3;  // Normal indices
		//unsigned int t1, t2, t3;
	} Face;

	typedef struct {
		Vertex* vertices;
		Vertex* normals;
		size_t vertex_count;
		size_t normal_count;
		Face* faces;
		size_t face_count;
	} Model;
}