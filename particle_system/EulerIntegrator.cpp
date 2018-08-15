#include "EulerIntegrator.h"

//����ŷ���� �����ʵ�λ�ã��ٶȣ���


void EulerIntegrator::Update(Particle *particle, ForceField *forcefield, float t, float dt)
{
	//ŷ���������ʵ�ķ������£�
	//        pn + 1 = pn + vn * dt
	//		  vn + 1 = vn + a(pn, t) * dt


	//��ȡ��ǰ��λ�ã��ٶȣ����������ٶ�
	Vec3f currentPosition = particle->getPosition();
	Vec3f currentVelocity = particle->getVelocity();
	float particleMass = particle->getMass();
	Vec3f particleAccelera = forcefield->getAcceleration(currentPosition, particleMass, t);

	//����λ���ٶ�=��ǰλ��+���ٶ�*dt
	//����λ��=��ǰλ��+�ٶ�*dt
	Vec3f newVelocity = currentVelocity + particleAccelera*dt;
	Vec3f newPosition = currentPosition + currentVelocity*dt;

	particle->setPosition(newPosition);
	particle->setVelocity(newVelocity);
	particle->increaseAge(dt);
}


Vec3f EulerIntegrator::getColor()
{
	return Vec3f(1, 0, 0);      //rgb ��ɫ
}