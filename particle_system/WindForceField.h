#pragma once
//
// 风力场：加速度的方向随时间不断改变(在Y轴方向上改变，加速度绝对值不变)
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


	//生成加速度方法   
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

