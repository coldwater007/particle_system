#include "TrapzIntegrator.h"

void TrapzIntegrator::Update(Particle *particle, ForceField *forcefield, float t, float dt)
{

	//��ȡ�ʵ������
	float particleMass = particle->getMass();
	//��ȡ�ʵ�λ�ã��ٶȣ����ٶ�
	Vec3f currentPosition = particle->getPosition();
	Vec3f currentVelocity = particle->getVelocity();
	Vec3f currentAccelera = forcefield->getAcceleration(currentPosition, particleMass, t);

	//���㾭��ʱ��dt���λ�ã����ٶȣ��ٶȵ�
	Vec3f newPosition = currentPosition + currentVelocity*dt;
	Vec3f newAccelera = forcefield->getAcceleration(newPosition, particleMass, t + dt);

	//ƽ�����ٶ�ȡ ��ֵ
	Vec3f resultAccelera = (currentAccelera + newAccelera) *(1.0 / 2);

	//����ƽ�����ٶȼ�����
	Vec3f resultPosition = currentPosition + resultAccelera*dt;
	Vec3f resultVelocity = currentVelocity + resultAccelera*dt;

	particle->setPosition(resultPosition);
	particle->setVelocity(resultVelocity);

	//�ʵ������ڼ��� dt
	particle->increaseAge(dt);
}

//ÿ������������һ������,��������ɫ���Ա�Ƚϲ�ͬ���ֲ��ԡ�
Vec3f TrapzIntegrator::getColor()
{
	return Vec3f(0.5, 0.5, 0.5);
}
