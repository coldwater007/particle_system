#pragma once

#include <assert.h>

#include "particle.h"


//����ʵ�ֶ������ʵ�����Ĺ���
//һ���ɶ�̬������С����������.
//������һ������RemoveDead�����޳��Ѿ����ڵ��ʵ㡣

class ParticleSet {

public:
	//���캯������������
	ParticleSet(int n)
	{
		size = n;             //����
		num_particles = 0;    //��ǰ��������
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

	//��ȡ��ǰ��������
	int getNumParticles() const { return num_particles; }

	//��ȡָ���±������
	Particle* Get(int i) const {
		assert(i >= 0 && i < num_particles);
		assert(particles[i] != NULL);
		return particles[i];
	}

	//������Ӷ���
	void Add(Particle *p)
	{
		assert(p != NULL);
		if (num_particles == size)
		{
			// ������������������������뻺������Ĭ��ԭ�ȴ�С��2����
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

	//ɾ���Ѿ�����������
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
	int num_particles;      //��ǰ���ӵ�����
	int size;               //������������(�Զ����ɱ�)
	Particle **particles;   //�������Ӷ����һά����
};

