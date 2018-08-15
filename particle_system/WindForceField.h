#pragma once
//
// �����������ٶȵķ�����ʱ�䲻�ϸı�(��Y�᷽���ϸı䣬���ٶȾ���ֵ����)
//
#pragma once
#include "ForceField.h"
class WindForceField :
	public ForceField
{
public:
	WindForceField(void) {}
	WindForceField(float magnitude) :windForceMagnitude(magnitude) {}
	~WindForceField() {}


	//���ɼ��ٶȷ���   
	Vec3f getAcceleration(const Vec3f &position, float mass, float t) const
	{
		float tmp = windForceMagnitude / mass;
		int a = t * 100;
		if (a % 5 == 0)
		{
			tmp *= (-1);
		}
		return Vec3f(tmp, 0, 0);
	}
private:
	float windForceMagnitude;
};

