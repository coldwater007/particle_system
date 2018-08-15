#pragma once
//
//ŷ���������ʵ�ķ������£�
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

	//�÷���ģ���ʵ��������������¸ı�λ�ú��ٶ� (��ʱ�䲽dt��)��
	//���������ʱ��仯������, t (��ǰʱ��) �������ԡ�
	//����Integrator::Update Ҳ�������ʵ������(����Particle::increaseAge()).
	void Update(Particle *particle, ForceField *forcefield, float t, float dt);


	Vec3f getColor();
};

