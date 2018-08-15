#include <gl\glut.h>


#include "system.h"
#include "generator.h"
#include "integrator.h"
#include "forcefield.h"
#include "particleSet.h"
#include "particle.h"

// ====================================================================


//���캯��  һ���ʵ�ϵͳ�� �ʵ������������ַ������������� �������
System::System(Generator *g, Integrator *i, ForceField *f)
{
	assert(g != NULL);
	assert(i != NULL);
	assert(f != NULL);
	generator = g;
	integrator = i;
	forcefield = f;
	particles = NULL;
	//����restart����
	Restart();
}
//��������
System::~System()
{
	delete generator;
	delete integrator;
	delete forcefield;
	delete particles;
}

// ====================================================================

void System::Restart()
{
	// delete the current particles
	delete particles;
	particles = new ParticleSet(100);

	// restart the generator (it might have state)
	generator->Restart();

	// reset the main clock
	current_time = 0;
}


//�ʵ�ϵͳ��ˢ�·���
void System::Update(float dt)
{
	// ����ÿ���ʵ�
	int num_particles = particles->getNumParticles();
	for (int i = 0; i < num_particles; i++)
	{
		//������� ���ַ����� �����ʵ������
		integrator->Update(particles->Get(i), forcefield, current_time, dt);
	}

	// ͬʱ�������µ��ʵ�
	int num_new = generator->numNewParticles(current_time, dt);
	for (int i = 0; i < num_new; i++)
	{
		//����������������� ����ȫ�µ��ʵ�
		Particle *p = generator->Generate(current_time, i);
		assert(p != NULL);
		particles->Add(p);
	}

	// ��ʱ�Ƴ����ڵ��ʵ㣨�����ڴ�...��
	particles->RemoveDead();

	// ��ǰʱ�����������
	current_time += dt;
}


// ====================================================================

void System::PaintGeometry() const
{
	//������������Ҫ����
	generator->Paint();
}


void System::Paint(float dt, int integrator_color, int draw_vectors,
	float acceleration_scale, int motion_blur) const
{

	
	if (integrator_color) {
		Vec3f c = integrator->getColor();
		glColor3f(c.r(), c.g(), c.b());
	}

	// �����ʵ�

	int num_particles = particles->getNumParticles();
	for (int i = 0; i < num_particles; i++)
	{

		//���ʵ㼯�ϣ����ʵ�ϵͳ�У� ����ÿ���ʵ�Ļ��Ʒ�������
		particles->Get(i)->Paint(dt, integrator_color, draw_vectors, motion_blur);
	}

	// ������Ҫ����ֱ��
	/*

	���ʵ� ָ����ٶ�  �൱�ڻ���  ���������е� ���ߣ���

	*/
	if (draw_vectors)
	{
		glColor3f(1, 1, 1);
		glBegin(GL_LINES);
		for (int i = 0; i < num_particles; i++)
		{
			Particle *p = particles->Get(i);
			Vec3f a = p->getPosition();
			Vec3f b = forcefield->getAcceleration(a, p->getMass(), current_time);
			// scale the acceleration (it's often too large to visualize directly)
			b *= acceleration_scale;
			b += a;
			glVertex3f(a.x(), a.y(), a.z());
			glVertex3f(b.x(), b.y(), b.z());
		}
		glEnd();
	}
}