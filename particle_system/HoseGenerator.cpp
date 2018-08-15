#include "HoseGenerator.h"

//ˮ���ʵ�������  ���ʵ�������ˮ�������




HoseGenerator::HoseGenerator(Vec3f position, float position_randomness,
	Vec3f velocity, float velocity_randomness) :Generator(position_randomness, velocity_randomness)
{
	//�趨����
	SetPosition(position);
	SetVelocity(velocity);
}


//ÿ�λ�ȡ�µ��ʵ���Ŀ
int HoseGenerator::numNewParticles(float current_time, float dt) const
{
	//return ((current_time / dt)*GetDesiredNumParticles() / GetLifespan());
	return 10;
	//return (dt*GetDesiredNumParticles() / GetLifespan())*1000;
}


//���������ķ�����Generate   ���ڵ�ǰʱ��  ����һ���ʵ�(�ٶȣ�λ��......)
Particle* HoseGenerator::Generate(float current_time, int i)
{
	Restart();              //������������
	Random rend(GetSeed());


	//��������ʵ�� λ�� �ٶ� ���� ������(�ɳ�ʼֵ + ���ֵ)
	Vec3f hose_position = GetPosition() + rend.randomVector() * GetPositionRand();
	Vec3f hose_velocity = GetVelocity() + rend.randomVector() * GetVelocityRand();
	float mass = GetMass() + rend.next() * GetMassRand();
	float lifespan = GetLifespan() + rend.next() * GetLifespanRand();

	SetParticle(new Particle(hose_position, hose_velocity, GetColor(), GetDeadColor(), mass, lifespan));   //���û��� Generator��Set������ÿ����������Ӧһ�������ʵ㣩
	return GetParticle();
}

// for the gui
// ��������������ص����⼸��
void HoseGenerator::Paint() const
{

}

// ��Ϊ�����������������ӣ��Ա��ʵ��������ȫһ�������֡�
void HoseGenerator::Restart()
{
	SetSeed(rand());
}
