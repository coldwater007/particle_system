#pragma once
//
//欧拉法更新质点的方法如下：
//        pn + 1 = pn + vn * dt
//		  vn + 1 = vn + a(pn, t) * dt
//
#pragma once
#include "Integrator.h"

class EulerIntegrator :
	public Integrator
{
public:
	EulerIntegrator() {}
	~EulerIntegrator() {}

	//该方法模拟质点在力场的作用下改变位置和速度 (在时间步dt内)。
	//如果不是随时间变化的力场, t (当前时间) 将被忽略。
	//方法Integrator::Update 也将调整质点的年龄(调用Particle::increaseAge()).
	void Update(Particle *particle, ForceField *forcefield, float t, float dt);


	Vec3f getColor();
};

