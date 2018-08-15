#include "RingGenerator.h"



//���ʵ������� �̳��ƻ��� Generator

RingGenerator::RingGenerator(float position_randomness,
	Vec3f velocity, float velocity_randomness) :Generator(position_randomness, velocity_randomness)
{
	SetVelocity(velocity);
}


RingGenerator::~RingGenerator()
{
}


//���ڻ��ʵ�������  ÿ�������ɵ��ʵ���Ŀ ��ʱ��仯
int RingGenerator::numNewParticles(float current_time, float dt) const
{
	return (dt*GetDesiredNumParticles() / GetLifespan())*(1 + current_time);
}

//����Paint����
void RingGenerator::Paint()const
{
	// ������
	float x = 100,
		y = -4,      //���ܸ���
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
	Restart();              //������������
	Random rend(GetSeed());
	double x = ((double)GetSeed() / RAND_MAX)*PI * 2;   //����
	double R = 3 * (1 + current_time);	        //���滷�İ뾶,��ʱ�䲻������

	Vec3f tmp(R*cosf(x), 0, R*sinf(x));
	SetPosition(tmp);

	//���ɻ� λ�� ,�ٶ� ,����, ������
	Vec3f ring_position = GetPosition() + rend.randomVector() * GetPositionRand();
	Vec3f ring_velocity = GetVelocity() + rend.randomVector() * GetVelocityRand();
	float mass = GetMass() + rend.next() * GetMassRand();
	float lifespan = GetLifespan() + rend.next() * GetLifespanRand();

	SetParticle(new Particle(ring_position, ring_velocity, GetColor(), GetDeadColor(), mass, lifespan));
	return GetParticle();
}
