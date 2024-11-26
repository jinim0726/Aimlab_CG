#pragma once
#include "shape.h"

using namespace shape;

void Shape::SetIsActive(bool is)
{
	isActive = is;
}

void Shape::SetSpeed(GLfloat s_speed)
{
	speed = s_speed;
}

void Shape::SetDic(glm::mat3 dic)
{
	direcTionV3 = dic;
}