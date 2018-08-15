#pragma once
//
//��������� ������ԭ�� ԽԶ ��Խ��
// ���ٶȾ��ǵ�ԭ��ľ����������
//
#pragma once

#include "ForceField.h"

class RadialForceField :
	public ForceField
{
public:
	RadialForceField(void) {}
	RadialForceField(float magnitude) :radiaMagnitude(magnitude) {}
	~RadialForceField() {}

	//��ü��ٶ�
	Vec3f getAcceleration(const Vec3f &position, float mass, float t) const
	{
		//TODO
		return Vec3f(position*(-1.0 / mass)*radiaMagnitude);     //���ٶȾ��ǵ�ԭ��ľ����������,������ԭ��
	}
private:
	float radiaMagnitude;           //��ԭ��ľ���
};


