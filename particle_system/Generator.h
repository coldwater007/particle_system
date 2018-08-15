#pragma once
//
//�ʵ���
//
// һ���ɶ�̬���С������
//
#pragma once
#include "vectors.h"
#include "particle.h"
#include "Random.h"

#include <cmath>
#include <stdlib.h>
#include <gl\glut.h>
#include <gl\GL.h>

const double PI = 3.1415926;  //Բ����

class Generator
{
public:
	Generator(void) {}
	Generator(float m_position_randomness, float m_velocity_randomness);
	~Generator();

	// ��ʼ��
	// ǰ������������һЩ�����ʵ������ÿ������һ������Ե�ѡ�
	void SetColors(Vec3f m_color, Vec3f m_dead_color, float m_color_randomness);
	void SetLifespan(float m_lifespan, float m_lifespan_randomness, int m_desired_num_particles);
	void SetMass(float m_mass, float m_mass_randomness);

	// ÿ��ʱ�䲽������һЩ�ʵ�
	// System::Update ���������ֺ���
	// ÿ��ʱ�䲽����Ҫ���ʵ���������Ҫ�������ٸ��µ��ʵ㡣
	// Ϊ����������������У������ִ�����һ�µ��ʵ��� (desired_num_particles����
	// ÿ��Ӧ���� dt * desired_num_particles / lifespan ���ʵ㡣
	// ����ʵ������������������Ҫ�仯(���ڻ𻷵�������),����Ҫ�ñ�İ취��
	// Generate�������������� (��ǰʱ�����0��n-1֮���һ������������n���ڴ�ʱ�䲽�е����ʵ���).
	virtual int numNewParticles(float current_time, float dt) const = 0;

	virtual Particle* Generate(float current_time, int i) = 0;

	// for the gui
	// ��������������ص����⼸��
	virtual void Paint() const = 0;
	// ��Ϊ�����������������ӣ��Ա��ʵ��������ȫһ�������֡�
	virtual void Restart() = 0;
private:
	Vec3f position;
	float position_randomness;

	Vec3f velocity;
	float velocity_randomness;

	Vec3f color;
	Vec3f dead_color;
	float color_randomness;

	float lifespan;
	float lifespan_randomness;
	int   desired_num_particles;
	float mass;
	float mass_randomness;
	float current_time;
	float dt;
	Particle *particle;
	int seed;       //���������
public:


	//   Set  ��  get����

	void  SetPosition(Vec3f m_position);
	void  SetVelocity(Vec3f m_velocity);
	void  SetPositionRand(float m_position_rand);
	void  SetVelocityRand(float m_velocity_rand);
	void  SetCurrentTime(float m_current_time);
	void  SetDt(float m_dt);
	void  SetParticle(Particle* m_particle);
	void  SetSeed(int m_seed);
	int   GetSeed(void)const;

	Vec3f GetPosition()const;
	Vec3f GetVelocity()const;
	float GetPositionRand()const;
	float GetVelocityRand()const;
	Vec3f GetColor()const;
	Vec3f GetDeadColor()const;
	float GetColorRand()const;
	float GetLifespan()const;
	float GetLifespanRand()const;
	int   GetDesiredNumParticles()const;
	float GetMass()const;
	float GetMassRand()const;
	float GetCurrentTime()const;
	float GetDt()const;
	Particle *GetParticle()const;
};

