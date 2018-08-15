#pragma once

//
// ..产生质点
//
//水管（hose）在空间某固定点(position)按某个特定的速度(velocity)来产生质点。位置和速度都可以混以随机性
//
#pragma once

#include "Generator.h"
#include "vectors.h"


class HoseGenerator :
	public Generator
{
public:
	HoseGenerator(void) {}
	HoseGenerator(Vec3f position, float position_randomness, Vec3f velocity, float velocity_randomness);
	~HoseGenerator() {}

	int numNewParticles(float current_time, float dt) const;
	Particle* Generate(float current_time, int i);

	void Paint() const;
	void Restart();
};


