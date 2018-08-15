#include "RungeKuttaIntegrator.h"


//龙格库塔积分方式，（直接套用对应公式）
void RungeKuttaIntegrator::Update(Particle *particle, ForceField *forcefield, float t, float dt)
{
	/*  y(i + 1) = y(i) + h*(K1 + 2 * K2 + 2 * K3 + K4) / 6
	K1 = f(x(i), y(i))
	K2 = f(x(i) + h / 2, y(i) + h*K1 / 2)
	K3 = f(x(i) + h / 2, y(i) + h*K2 / 2)
	K4 = f(x(i) + h, y(i) + h*K3)
	*/

	//获取质量
	float mass = particle->getMass();

	//获取位置，速度，加速度
	Vec3f Xn1 = particle->getPosition();
	Vec3f Vn1 = particle->getVelocity();
	Vec3f An1 = forcefield->getAcceleration(Xn1, mass, t);

	Vec3f Xn2 = Xn1 + Vn1*0.5*dt;
	Vec3f Vn2 = Vn1 + An1*0.5*dt;
	Vec3f An2 = forcefield->getAcceleration(Xn2, mass, t);

	Vec3f Xn3 = Xn1 + Vn2*0.5*dt;
	Vec3f Vn3 = Vn1 + An2*0.5*dt;
	Vec3f An3 = forcefield->getAcceleration(Xn3, mass, t);

	Vec3f Xn4 = Xn1 + Vn3*dt;
	Vec3f Vn4 = Vn1 + An3*dt;
	Vec3f An4 = forcefield->getAcceleration(Xn4, mass, t);

	Vec3f rung_position = Xn1 + 1.0 / 6 * (Vn1 + 2 * Vn2 + 2 * Vn3 + Vn4)*dt;
	Vec3f rung_velocity = Vn1 + 1.0 / 6 * (An1 + 2 * An2 + 2 * An3 + An4)*dt;

	particle->setPosition(rung_position);
	particle->setVelocity(rung_velocity);
	particle->increaseAge(dt);
}

Vec3f RungeKuttaIntegrator::getColor()
{
	return Vec3f(0, 0, 1);
}
