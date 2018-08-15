#include "RingGenerator.h"



//环质点生成器 继承制基类 Generator

RingGenerator::RingGenerator(float position_randomness,
	Vec3f velocity, float velocity_randomness) :Generator(position_randomness, velocity_randomness)
{
	SetVelocity(velocity);
}


RingGenerator::~RingGenerator()
{
}


//对于环质点生成器  每次新生成的质点数目 随时间变化
int RingGenerator::numNewParticles(float current_time, float dt) const
{
	return (dt*GetDesiredNumParticles() / GetLifespan())*(1 + current_time);
}

//给定Paint方法
void RingGenerator::Paint()const
{
	// 画地面
	float x = 100,
		y = -4,      //不能更改
		z = 100;
	glBegin(GL_POLYGON);
	glVertex3f(x, y, -z);
	glVertex3f(x, y, z);
	glVertex3f(-x, y, z);
	glVertex3f(-x, y, -z);
	glEnd();
}

void RingGenerator::Restart()
{
	SetSeed(rand());
}

Particle *RingGenerator::Generate(float current_time, int i)
{
	Restart();              //获得随机性种子
	Random rend(GetSeed());
	double x = ((double)GetSeed() / RAND_MAX)*PI * 2;   //弧度
	double R = 3 * (1 + current_time);	        //火焰环的半径,随时间不断增大

	Vec3f tmp(R*cosf(x), 0, R*sinf(x));
	SetPosition(tmp);

	//生成环 位置 ,速度 ,质量, 生命期
	Vec3f ring_position = GetPosition() + rend.randomVector() * GetPositionRand();
	Vec3f ring_velocity = GetVelocity() + rend.randomVector() * GetVelocityRand();
	float mass = GetMass() + rend.next() * GetMassRand();
	float lifespan = GetLifespan() + rend.next() * GetLifespanRand();

	SetParticle(new Particle(ring_position, ring_velocity, GetColor(), GetDeadColor(), mass, lifespan));
	return GetParticle();
}
