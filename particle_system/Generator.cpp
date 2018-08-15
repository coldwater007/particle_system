#include "Generator.h"

//�ʵ�������

//���캯���� λ������� & �ٶ������
Generator::Generator(float m_position_randomness, float m_velocity_randomness)
{
	position_randomness = m_position_randomness;
	velocity_randomness = m_velocity_randomness;
}


Generator::~Generator()
{
}

// �趨��ɫ��������ɫ����ɫ�����
void  Generator::SetColors(Vec3f m_color, Vec3f m_dead_color, float m_color_randomness)
{
	color = m_color;
	dead_color = m_dead_color;
	color_randomness = m_color_randomness;
}

//�趨��������
void  Generator::SetLifespan(float m_lifespan, float m_lifespan_randomness, int m_desired_num_particles)
{
	lifespan = m_lifespan;
	lifespan_randomness = m_lifespan_randomness;
	desired_num_particles = m_desired_num_particles;
}
//�趨����
void  Generator::SetMass(float m_mass, float m_mass_randomness)
{
	mass = m_mass;
	mass_randomness = m_mass_randomness;
}
//�趨λ��
void  Generator::SetPosition(Vec3f m_position)
{
	position = m_position;
}
//�趨�ٶ�
void  Generator::SetVelocity(Vec3f m_velocity)
{
	velocity = m_velocity;
}
//�趨λ�����
void  Generator::SetPositionRand(float m_position_rand)
{
	position_randomness = m_position_rand;
}
//�趨�ٶ����
void  Generator::SetVelocityRand(float m_velocity_rand)
{
	velocity_randomness = m_velocity_rand;
}
//�趨��ǰʱ��
void  Generator::SetCurrentTime(float m_current_time)
{
	current_time = m_current_time;
}
//�趨ʱ�䲽��
void  Generator::SetDt(float m_dt)
{
	dt = m_dt;
}
//�趨�ʵ�
void  Generator::SetParticle(Particle* m_particle)
{
	particle = m_particle;
}
//�趨�����
void  Generator::SetSeed(int m_seed)
{
	seed = m_seed;
}
int   Generator::GetSeed(void)const
{
	return seed;
}
Vec3f Generator::GetPosition()const
{
	return position;
}
Vec3f Generator::GetVelocity()const
{
	return velocity;
}
float Generator::GetPositionRand()const
{
	return position_randomness;
}
float Generator::GetVelocityRand()const
{
	return velocity_randomness;
}
Vec3f Generator::GetColor()const
{
	return color;
}
Vec3f Generator::GetDeadColor()const
{
	return dead_color;
}
float Generator::GetColorRand()const
{
	return color_randomness;
}
float Generator::GetLifespan()const
{
	return lifespan;
}
float Generator::GetLifespanRand()const
{
	return lifespan_randomness;
}
int   Generator::GetDesiredNumParticles()const
{
	return desired_num_particles;
}
float Generator::GetMass()const
{
	return mass;
}
float Generator::GetMassRand()const
{
	return mass_randomness;
}
float Generator::GetCurrentTime()const
{
	return current_time;
}
float Generator::GetDt()const
{
	return dt;
}
Particle *Generator::GetParticle()const
{
	return particle;
}
