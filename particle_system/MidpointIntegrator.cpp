#include "MidpointIntegrator.h"



//�е���ַ�

void MidpointIntegrator::Update(Particle *particle, ForceField *forcefield, float t, float dt)
{
	//�е㷨����ŷ�����߰벽��Ȼ��ʹ�ô�ʱ���ٶ��������ʵ�:
	//        pm = pn + vn * dt / 2
	//		  vm = vn + a(pn, t) * dt / 2
	//		  pn + 1 = pn + vm * dt
	//		  vn + 1 = vn + a(pm, t + dt / 2) * dt
	//		  a(p, t) ����ʱ��t, �ڵ�p�ļ��ٶȡ�

	//��ȡλ�ã��ٶȣ����������ٶ�
	Vec3f currentPosition = particle->getPosition();
	Vec3f currentVelocity = particle->getVelocity();
	float particleMass = particle->getMass();
	Vec3f particleAccelera = forcefield->getAcceleration(currentPosition, particleMass, t);

	//�ο��е�(MidPoint)��λ�ã��ٶ�
	Vec3f tmpPosition = currentPosition + currentVelocity*(dt / 2);
	Vec3f tmpVelocity = currentVelocity + particleAccelera*(dt / 2);

	//����λ��Ϊ��ǰλ��+�м��ٶ�*dt
	Vec3f newPosition = currentPosition + tmpVelocity*dt;
	//�����ٶ�Ϊ��ǰ�ٶ�+�м�λ�ü��ٶ�*dt
	Vec3f newVelocity = currentVelocity + forcefield->getAcceleration(tmpPosition, particleMass, t + (dt / 2))*dt;

	particle->setPosition(newPosition);
	particle->setVelocity(newVelocity);
	particle->increaseAge(dt);
}


Vec3f MidpointIntegrator::getColor()
{
	return Vec3f(0, 1, 0);          //GREEN
}