#pragma once

//������
#pragma once
#include "ForceField.h"
class ConstantForceField :
	public ForceField
{
public:
	ConstantForceField(void) {}
	ConstantForceField(Vec3f force) :constantForce(force) {}
	~ConstantForceField() {}

	//����������ٶ�
	Vec3f getAcceleration(const Vec3f &position, float mass, float t) const
	{
		return Vec3f(constantForce *(1.0 / mass));   //������������
	}
private:
	Vec3f constantForce;         //����
};


