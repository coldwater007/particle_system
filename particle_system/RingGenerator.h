#pragma once
//
// 产生质点
//
// ...环生成器具有类似的参数，不同之处在于质点位于一个扩展的环上(加进了随机性)。
// 环的半径依赖于时间。为了让环的密度保持常数，每个时间步产生的质点个数是增加的
//



#include "Generator.h"

class RingGenerator :
	public Generator
{
public:
	RingGenerator(void) {}
	RingGenerator(float position_randomness, Vec3f velocity, float velocity_randomness);
	~RingGenerator();

	int numNewParticles(float current_time, float dt) const;
	Particle* Generate(float current_time, int i);

	void Paint() const;
	void Restart();
};