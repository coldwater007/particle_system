#pragma once

//对应于平面的力场
#pragma once

#include "ForceField.h"

class VerticalForceField :
	public ForceField
{
public:
	VerticalForceField(void) {}
	VerticalForceField(float magnitude) :verticalMagnitude(magnitude) {}
	~VerticalForceField() {}

	//获得加速度
	Vec3f getAcceleration(const Vec3f &position, float mass, float t) const
	{
		return Vec3f(0, -verticalMagnitude * position.y() * 1 / mass, 0);
	}
private:
	float verticalMagnitude;          //到y平面的距离
};
