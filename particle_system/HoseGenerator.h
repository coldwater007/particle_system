#pragma once

//
// ..�����ʵ�
//
//ˮ�ܣ�hose���ڿռ�ĳ�̶���(position)��ĳ���ض����ٶ�(velocity)�������ʵ㡣λ�ú��ٶȶ����Ի��������
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


