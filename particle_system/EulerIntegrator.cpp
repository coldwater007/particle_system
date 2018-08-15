#include "EulerIntegrator.h"

//经典欧拉法 更新质点位置，速度，等


void EulerIntegrator::Update(Particle *particle, ForceField *forcefield, float t, float dt)
{
	//欧拉法更新质点的方法如下：
	//        pn + 1 = pn + vn * dt
	//		  vn + 1 = vn + a(pn, t) * dt


	//获取当前的位置，速度，质量，加速度
	Vec3f currentPosition = particle->getPosition();
	Vec3f currentVelocity = particle->getVelocity();
	float particleMass = particle->getMass();
	Vec3f particleAccelera = forcefield->getAcceleration(currentPosition, particleMass, t);

	//最终位置速度=当前位置+加速度*dt
	//最终位置=当前位置+速度*dt
	Vec3f newVelocity = currentVelocity + particleAccelera*dt;
	Vec3f newPosition = currentPosition + currentVelocity*dt;

	particle->setPosition(newPosition);
	particle->setVelocity(newVelocity);
	particle->increaseAge(dt);
}


Vec3f EulerIntegrator::getColor()
{
	return Vec3f(1, 0, 0);      //rgb 红色
}