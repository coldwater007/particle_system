#pragma once
//
//.. �Ľ������������
// y(i + 1) = y(i) + h*(K1 + 2 * K2 + 2 * K3 + K4) / 6
// K1 = f(x(i), y(i))
// K2 = f(x(i) + h / 2, y(i) + h*K1 / 2)
// K3 = f(x(i) + h / 2, y(i) + h*K2 / 2)
// K4 = f(x(i) + h, y(i) + h*K3)
//


#include "Integrator.h"
class RungeKuttaIntegrator :
	public Integrator
{
public:
	RungeKuttaIntegrator(void) {}
	~RungeKuttaIntegrator(void) {}

	//�÷���ģ���ʵ��������������¸ı�λ�ú��ٶ� (��ʱ�䲽dt��)��
	//���������ʱ��仯������, t (��ǰʱ��) �������ԡ�
	//����Integrator::Update Ҳ�������ʵ������(����Particle::increaseAge()).
	void Update(Particle *particle, ForceField *forcefield, float t, float dt);

	//ÿ������������һ������,��������ɫ���Ա�Ƚϲ�ͬ���ֲ��ԡ�
	Vec3f getColor();
};
