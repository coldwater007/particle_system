#pragma once

//��Ӧ��ƽ�������
#pragma once

#include "ForceField.h"

class VerticalForceField :
	public ForceField
{
public:
	VerticalForceField(void) {}
	VerticalForceField(float magnitude) :verticalMagnitude(magnitude) {}
	~VerticalForceField() {}

	//��ü��ٶ�
	Vec3f getAcceleration(const Vec3f &position, float mass, float t) const
	{
		return Vec3f(0, -verticalMagnitude * position.y() * 1 / mass, 0);
	}
private:
	float verticalMagnitude;          //��yƽ��ľ���
};
