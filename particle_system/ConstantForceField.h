#pragma once

//恒力场
#pragma once
#include "ForceField.h"
class ConstantForceField :
	public ForceField
{
public:
	ConstantForceField(void) {}
	ConstantForceField(Vec3f force) :constantForce(force) {}
	~ConstantForceField() {}

	//获得力场加速度
	Vec3f getAcceleration(const Vec3f &position, float mass, float t) const
	{
		return Vec3f(constantForce *(1.0 / mass));   //常力除以质量
	}
private:
	Vec3f constantForce;         //常力
};


