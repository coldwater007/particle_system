#pragma once

#include <assert.h>
#include "vectors.h"

#include "particle.h"
#include "particleSet.h"
#include "Generator.h"
#include "Integrator.h"
#include "ForceField.h"

// ====================================================================
//�������һ��particleϵͳ    �����ʵ������������ַ������Լ��������
// ====================================================================




class System
{

public:

	// CONSTRUCTOR & DESTRUCTOR
	System(Generator *g, Integrator *i, ForceField *f);
	~System();

	// FUNCTIONALITY
	void Restart();

	//System::Update ����ÿ��һ��ʱ�䱻����һ��(ͨ��������ѡ�� -refresh <seconds>ָ��),
	//Update ��������ʱ���÷�����ǰ�� (ÿ���ߵ�ʱ����������ѡ��-dt <seconds>ָ����
	void Update(float dt);

	// RENDERING
	void Paint(float dt, int integrator_color, int draw_vectors,
		float acceleration_scale, int motion_blur) const;
	void PaintGeometry() const;


private:
	// don't use this constructor
	System() { assert(0); }

	// REPRESENTATION
	ParticleSet *particles;   //�ʵ�ϵͳ���ʵ㼯��
	Generator   *generator;  //�ʵ�ϵͳ��������
	Integrator  *integrator;   //�ʵ�ϵͳ�Ļ��ַ���
	ForceField  *forcefield;  //��������
	float current_time;  //��ǰʱ��
};
