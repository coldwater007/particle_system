#include "TrapzIntegrator.h"

void TrapzIntegrator::Update(Particle *particle, ForceField *forcefield, float t, float dt)
{

	//获取质点的质量
	float particleMass = particle->getMass();
	//获取质点位置，速度，加速度
	Vec3f currentPosition = particle->getPosition();
	Vec3f currentVelocity = particle->getVelocity();
	Vec3f currentAccelera = forcefield->getAcceleration(currentPosition, particleMass, t);

	//计算经过时间dt后的位置，加速度，速度等
	Vec3f newPosition = currentPosition + currentVelocity*dt;
	Vec3f newAccelera = forcefield->getAcceleration(newPosition, particleMass, t + dt);

	//平均加速度取 均值
	Vec3f resultAccelera = (currentAccelera + newAccelera) *(1.0 / 2);

	//利用平均加速度计算结果
	Vec3f resultPosition = currentPosition + resultAccelera*dt;
	Vec3f resultVelocity = currentVelocity + resultAccelera*dt;

	particle->setPosition(resultPosition);
	particle->setVelocity(resultVelocity);

	//质点生命期减少 dt
	particle->increaseAge(dt);
}

//每个积分器都有一个方法,来返回颜色，以便比较不同积分策略。
Vec3f TrapzIntegrator::getColor()
{
	return Vec3f(0.5, 0.5, 0.5);
}
