#pragma once
#include <gl/glew.h> //--- 필요한 헤더파일 include
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>
#include "shape.h"
#include "DefaultShape.h"
#include "cube.h"

// 세이더 함수
char* filetobuf(const char* file);
void free_model(shape::Model* model);
void read_obj_file(const char* filename, shape::Model* model);
void make_vertexShaders(GLuint& vertexShader);
void make_fragmentShaders(GLuint& fragmentShader);
void make_shaderProgram(GLuint& vertexShader, GLuint& fragmentShader, GLuint& shaderID);

// 버퍼 함수
void InitBuffer(GLuint& shaderID, GLuint& vao, GLuint* vbo, shape::DefaultShape defaultShape);
void InitBuffer(GLuint& shaderID, GLuint& vao, GLuint* vbo, GLuint* ebo, shape::Cube defaultShape);

// 카메라 설정 함수
void SetCamera(GLuint& shaderID, bool isOrtho);

// Draw 함수
void DrawShape(GLuint& shaderID, GLuint& vao, GLuint* vbo, shape::DefaultShape defaultShape, bool isOrtho);
void DrawShape(GLuint& shaderID, GLuint& vao, GLuint* vbo, GLuint* ebo, shape::Cube defaultShape, bool isOrtho);

// Draw 특수 함수
void DrawShape_Face(GLuint& shaderID, GLuint& vao, GLuint* vbo, GLuint* ebo, shape::Cube defaultShape, int faceNum, bool isOrtho);
void DrawShape_Line(GLuint& shaderID, GLuint& vao, GLuint* vbo, GLuint* ebo, shape::Cube defaultShape, bool isOrtho);
void DrawShape_Face_Line(GLuint& shaderID, GLuint& vao, GLuint* vbo, GLuint* ebo, shape::Cube defaultShape, int faceNum, bool isOrtho);