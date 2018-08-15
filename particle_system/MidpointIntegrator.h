#pragma once
//
//..�е㷨����ŷ�����߰벽��Ȼ��ʹ�ô�ʱ���ٶ��������ʵ�:
//        pm = pn + vn * dt / 2
//		  vm = vn + a(pn, t) * dt / 2
//		  pn + 1 = pn + vm * dt
//		  vn + 1 = vn + a(pm, t + dt / 2) * dt
//		  a(p, t) ����ʱ��t, �ڵ�p�ļ��ٶȡ�
//
#pragma once

#include "Integrator.h"

class MidpointIntegrator :
	public Integrator
{
public:
	MidpointIntegrator() {}
	~MidpointIntegrator() {}


	//�÷���ģ���ʵ��������������¸ı�λ�ú��ٶ� (��ʱ�䲽dt��)��
	//���������ʱ��仯������, t (��ǰʱ��) �������ԡ�
	//����Integrator::Update Ҳ�������ʵ������(����Particle::increaseAge()).
	void Update(Particle *particle, ForceField *forcefield, float t, float dt);

	//ÿ������������һ������,��������ɫ���Ա�Ƚϲ�ͬ���ֲ��ԡ�
	Vec3f getColor();
};


