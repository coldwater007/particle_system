#pragma once
//
// 重力场
//
#pragma once

#include "ForceField.h"
#include "vectors.h"

#define GRAVITY_ACCELERATION -9.8f         //重力加速度

class GravityForceField :
	public ForceField
{
public:
	GravityForceField(void)
	{
		gravityForcePower.Set(0.0f, GRAVITY_ACCELERATION, 0.0f);
	}
	GravityForceField(Vec3f gravity) :gravityForcePower(gravity) {}
	~GravityForceField() {}

	//获得力场加速度
	Vec3f getAcceleration(const Vec3f &position, float mass, float t) const
	{
		return gravityForcePower;
	}
private:

	Vec3f gravityForcePower;
};
