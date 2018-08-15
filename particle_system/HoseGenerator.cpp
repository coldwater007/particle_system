#include "HoseGenerator.h"

//水管质点生成器  （质点类似于水管喷出）




HoseGenerator::HoseGenerator(Vec3f position, float position_randomness,
	Vec3f velocity, float velocity_randomness) :Generator(position_randomness, velocity_randomness)
{
	//设定参数
	SetPosition(position);
	SetVelocity(velocity);
}


//每次获取新的质点数目
int HoseGenerator::numNewParticles(float current_time, float dt) const
{
	//return ((current_time / dt)*GetDesiredNumParticles() / GetLifespan());
	return 10;
	//return (dt*GetDesiredNumParticles() / GetLifespan())*1000;
}


//生成器核心方法：Generate   基于当前时间  生成一个质点(速度，位置......)
Particle* HoseGenerator::Generate(float current_time, int i)
{
	Restart();              //获得随机性种子
	Random rend(GetSeed());


	//随机生成质点的 位置 速度 质量 生命期(由初始值 + 随机值)
	Vec3f hose_position = GetPosition() + rend.randomVector() * GetPositionRand();
	Vec3f hose_velocity = GetVelocity() + rend.randomVector() * GetVelocityRand();
	float mass = GetMass() + rend.next() * GetMassRand();
	float lifespan = GetLifespan() + rend.next() * GetLifespanRand();

	SetParticle(new Particle(hose_position, hose_velocity, GetColor(), GetDeadColor(), mass, lifespan));   //调用基类 Generator的Set方法（每个生成器对应一个代表质点）
	return GetParticle();
}

// for the gui
// 绘制与生成子相关的任意几何
void HoseGenerator::Paint() const
{

}

// 将为随机数生成类产生种子，以便质点仿真能完全一样地重现。
void HoseGenerator::Restart()
{
	SetSeed(rand());
}
