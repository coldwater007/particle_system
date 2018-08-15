#pragma once
//
//..���������
//
#pragma once
#include "particle.h"
#include "ForceField.h"

class Integrator
{
public:
	Integrator() {}
	~Integrator() {}
	//�÷���ģ���ʵ��������������¸ı�λ�ú��ٶ� (��ʱ�䲽dt��)��
	//���������ʱ��仯������, t (��ǰʱ��) �������ԡ�
	//����Integrator::Update Ҳ�������ʵ������(����Particle::increaseAge()).
	virtual void Update(Particle *particle, ForceField *forcefield, float t, float dt) = 0;

	virtual Vec3f getColor() = 0;          //ÿ������������һ������,��������ɫ���Ա�Ƚϲ�ͬ���ֲ��ԡ�
};


