#pragma once

//
// ���η������
//
#pragma once

#include "Integrator.h"

class TrapzIntegrator :
	public Integrator
{
public:
	TrapzIntegrator(void) {}
	~TrapzIntegrator(void) {}

	//..�÷���ģ���ʵ��������������¸ı�λ�ú��ٶ� (��ʱ�䲽dt��)��
	//���������ʱ��仯������, t (��ǰʱ��) �������ԡ�
	//����Integrator::Update Ҳ�������ʵ������(����Particle::increaseAge()).
	void Update(Particle *particle, ForceField *forcefield, float t, float dt);

	//ÿ������������һ������,��������ɫ���Ա�Ƚϲ�ͬ���ֲ��ԡ�
	Vec3f getColor();
};


