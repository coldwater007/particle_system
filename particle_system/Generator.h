#pragma once
//
//质点类
//
// 一个可动态变大小的数组
//
#pragma once
#include "vectors.h"
#include "particle.h"
#include "Random.h"

#include <cmath>
#include <stdlib.h>
#include <gl\glut.h>
#include <gl\GL.h>

const double PI = 3.1415926;  //圆周率

class Generator
{
public:
	Generator(void) {}
	Generator(float m_position_randomness, float m_velocity_randomness);
	~Generator();

	// 初始化
	// 前三个方法设置一些公共质点参数。每个都有一个随机性的选项。
	void SetColors(Vec3f m_color, Vec3f m_dead_color, float m_color_randomness);
	void SetLifespan(float m_lifespan, float m_lifespan_randomness, int m_desired_num_particles);
	void SetMass(float m_mass, float m_mass_randomness);

	// 每个时间步，产生一些质点
	// System::Update 函数的助手函数
	// 每个时间步，都要问质点生成子需要产生多少个新的质点。
	// 为了在整个仿真过程中，都保持粗略上一致的质点数 (desired_num_particles），
	// 每步应产生 dt * desired_num_particles / lifespan 个质点。
	// 如果质点在整个仿真过程中需要变化(如在火环的例子中),你需要用别的办法。
	// Generate方法有两个参数 (当前时间和在0到n-1之间的一个整数，这里n是在此时间步中的新质点数).
	virtual int numNewParticles(float current_time, float dt) const = 0;

	virtual Particle* Generate(float current_time, int i) = 0;

	// for the gui
	// 绘制与生成子相关的任意几何
	virtual void Paint() const = 0;
	// 将为随机数生成类产生种子，以便质点仿真能完全一样地重现。
	virtual void Restart() = 0;
private:
	Vec3f position;
	float position_randomness;

	Vec3f velocity;
	float velocity_randomness;

	Vec3f color;
	Vec3f dead_color;
	float color_randomness;

	float lifespan;
	float lifespan_randomness;
	int   desired_num_particles;
	float mass;
	float mass_randomness;
	float current_time;
	float dt;
	Particle *particle;
	int seed;       //随机数种子
public:


	//   Set  与  get方法

	void  SetPosition(Vec3f m_position);
	void  SetVelocity(Vec3f m_velocity);
	void  SetPositionRand(float m_position_rand);
	void  SetVelocityRand(float m_velocity_rand);
	void  SetCurrentTime(float m_current_time);
	void  SetDt(float m_dt);
	void  SetParticle(Particle* m_particle);
	void  SetSeed(int m_seed);
	int   GetSeed(void)const;

	Vec3f GetPosition()const;
	Vec3f GetVelocity()const;
	float GetPositionRand()const;
	float GetVelocityRand()const;
	Vec3f GetColor()const;
	Vec3f GetDeadColor()const;
	float GetColorRand()const;
	float GetLifespan()const;
	float GetLifespanRand()const;
	int   GetDesiredNumParticles()const;
	float GetMass()const;
	float GetMassRand()const;
	float GetCurrentTime()const;
	float GetDt()const;
	Particle *GetParticle()const;
};

