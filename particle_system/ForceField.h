#pragma once
//
// 力场基类
//

#pragma once
#include "vectors.h"

class ForceField
{
public:
	ForceField(void) {}
	~ForceField(void) {}



	//纯虚函数,获得力场加速度
	virtual Vec3f getAcceleration(const Vec3f &position, float mass, float t) const = 0;
};


