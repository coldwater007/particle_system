#pragma once
//
// ��������
//

#pragma once
#include "vectors.h"

class ForceField
{
public:
	ForceField(void) {}
	~ForceField(void) {}



	//���麯��,����������ٶ�
	virtual Vec3f getAcceleration(const Vec3f &position, float mass, float t) const = 0;
};


