#pragma once
//
// �����ʵ�
//
// ...���������������ƵĲ�������֮ͬ�������ʵ�λ��һ����չ�Ļ���(�ӽ��������)��
// ���İ뾶������ʱ�䡣Ϊ���û����ܶȱ��ֳ�����ÿ��ʱ�䲽�������ʵ���������ӵ�
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