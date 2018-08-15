#pragma once

#include <assert.h>

#include "particle.h"


//该类实现对整体质点数组的管理
//一个可动态调整大小的粒子数组.
//包含了一个特殊RemoveDead方法剔除已经过期的质点。

class ParticleSet {

public:
	//构造函数，析构函数
	ParticleSet(int n)
	{
		size = n;             //容量
		num_particles = 0;    //当前粒子数量
		particles = new Particle*[size];
		for (int i = 0; i < size; i++)
		{
			particles[i] = NULL;
		}
	}

	~ParticleSet()
	{
		for (int i = 0; i < num_particles; i++)
		{
			delete particles[i];
		}
		delete[] particles;
	}

	//获取当前粒子数量
	int getNumParticles() const { return num_particles; }

	//获取指定下标的粒子
	Particle* Get(int i) const {
		assert(i >= 0 && i < num_particles);
		assert(particles[i] != NULL);
		return particles[i];
	}

	//添加粒子对象
	void Add(Particle *p)
	{
		assert(p != NULL);
		if (num_particles == size)
		{
			// 如果超出缓冲区，则重新申请缓冲区（默认原先大小的2倍）
			Particle **new_particles = new Particle*[size * 2];
			for (int i = 0; i < size; i++)
			{
				new_particles[i] = particles[i];
				new_particles[i + size] = NULL;
			}
			delete[] particles;
			particles = new_particles;
			size *= 2;
		}
		assert(num_particles < size);
		particles[num_particles] = p;
		num_particles++;
	}

	//删除已经死亡的粒子
	void RemoveDead()
	{
		int i = 0;
		while (1)
		{
			if (i == num_particles) break;
			assert(particles[i] != NULL);
			if (particles[i]->isDead())
			{

				delete particles[i];
				num_particles--;
				particles[i] = particles[num_particles];
				particles[num_particles] = NULL;
			}
			else
			{
				i++;
			}
		}
		// verify cleanup
		for (i = 0; i < size; i++)
		{
			if (i < num_particles)
			{
				assert(particles[i] != NULL);
				assert(!particles[i]->isDead());
			}
			else
			{
				assert(particles[i] == NULL);
			}
		}
	}


private:

	// don't use this constructor
	ParticleSet() { assert(0); }

	// REPRESENTATION
	int num_particles;      //当前粒子的数量
	int size;               //最大的粒子数量(自动，可变)
	Particle **particles;   //储存粒子对象的一维数组
};

