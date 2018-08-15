#include "MidpointIntegrator.h"



//中点积分法

void MidpointIntegrator::Update(Particle *particle, ForceField *forcefield, float t, float dt)
{
	//中点法先用欧拉法走半步，然后使用此时的速度来更新质点:
	//        pm = pn + vn * dt / 2
	//		  vm = vn + a(pn, t) * dt / 2
	//		  pn + 1 = pn + vm * dt
	//		  vn + 1 = vn + a(pm, t + dt / 2) * dt
	//		  a(p, t) 是在时间t, 在点p的加速度。

	//获取位置，速度，质量，加速度
	Vec3f currentPosition = particle->getPosition();
	Vec3f currentVelocity = particle->getVelocity();
	float particleMass = particle->getMass();
	Vec3f particleAccelera = forcefield->getAcceleration(currentPosition, particleMass, t);

	//参考中点(MidPoint)的位置，速度
	Vec3f tmpPosition = currentPosition + currentVelocity*(dt / 2);
	Vec3f tmpVelocity = currentVelocity + particleAccelera*(dt / 2);

	//最终位置为当前位置+中间速度*dt
	Vec3f newPosition = currentPosition + tmpVelocity*dt;
	//最终速度为当前速度+中间位置加速度*dt
	Vec3f newVelocity = currentVelocity + forcefield->getAcceleration(tmpPosition, particleMass, t + (dt / 2))*dt;

	particle->setPosition(newPosition);
	particle->setVelocity(newVelocity);
	particle->increaseAge(dt);
}


Vec3f MidpointIntegrator::getColor()
{
	return Vec3f(0, 1, 0);          //GREEN
}