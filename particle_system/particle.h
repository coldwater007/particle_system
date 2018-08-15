#pragma once
#include "vectors.h"

// ================================================================
//    质点类
// stores the information for a particle
// ..储存一个粒子对象的信息

class Particle {

public:

	// CONSTRUCTOR & DESTRUCTOR
	Particle(Vec3f p, Vec3f v, Vec3f _color, Vec3f _dead_color, float m, float lifespan) {
		position = p;              //现在的位置
		last_position = p;         //上一次的位置
		velocity = v;              //速度
		color = _color;			   // 粒子产生时的颜色
		dead_color = _dead_color;  // 粒子消失时的颜色
		mass = m;                  //粒子质量
		timeToDeath = lifespan;    //粒子生存时间，不断减少
	}
	~Particle() {}

	// ACCESSORS

	//获取粒子现在的位置
	Vec3f getPosition() const { return position; }
	//获取粒子速度
	Vec3f getVelocity() const { return velocity; }
	//获取粒子颜色
	Vec3f getColor() const { return color; }
	//获取粒子质量
	float getMass() const { return mass; }
	//判断粒子是否应该消失
	int isDead() const { if (timeToDeath <= 0) return 1; else return 0; }


	//更新粒子位置
	void setPosition(Vec3f p) { last_position = position; position = p; }
	//设置粒子速度
	void setVelocity(Vec3f v) { velocity = v; }
	//设置粒子产生时的颜色
	void setColor(Vec3f c) { color = c; }
	//设置粒子质量
	void setMass(float m) { mass = m; }
	//使粒子的颜色朝着死亡的颜色变化并使粒子的寿命减少a
	void increaseAge(float a);

	// Paint
	// 画出粒子
	void Paint(float dt, int integrator_color, int draw_vectors, int motion_blur) const;

private:

	Particle() { assert(0); } // don't use this constructor


	Vec3f position;         //现在的位置
	Vec3f last_position;    //上一次的位置
	Vec3f velocity;		  //速度
	Vec3f color;            //TODO 粒子产生时的颜色
	Vec3f dead_color;       // 粒子消失时的颜色
	float mass;             //粒子质量
	float timeToDeath;      //粒子生存时间，不断减少

};