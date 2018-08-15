#pragma once
//
//..积分类基类
//
#pragma once
#include "particle.h"
#include "ForceField.h"

class Integrator
{
public:
	Integrator() {}
	~Integrator() {}
	//该方法模拟质点在力场的作用下改变位置和速度 (在时间步dt内)。
	//如果不是随时间变化的力场, t (当前时间) 将被忽略。
	//方法Integrator::Update 也将调整质点的年龄(调用Particle::increaseAge()).
	virtual void Update(Particle *particle, ForceField *forcefield, float t, float dt) = 0;

	virtual Vec3f getColor() = 0;          //每个积分器都有一个方法,来返回颜色，以便比较不同积分策略。
};


