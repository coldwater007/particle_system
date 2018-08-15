#pragma once
//
//特殊的力场 ：距离原点 越远 力越大
// 加速度就是到原点的距离除以质量
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

	//获得加速度
	Vec3f getAcceleration(const Vec3f &position, float mass, float t) const
	{
		//TODO
		return Vec3f(position*(-1.0 / mass)*radiaMagnitude);     //加速度就是到原点的距离除以质量,方向朝向原点
	}
private:
	float radiaMagnitude;           //与原点的距离
};


