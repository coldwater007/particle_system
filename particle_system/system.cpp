#include <gl\glut.h>


#include "system.h"
#include "generator.h"
#include "integrator.h"
#include "forcefield.h"
#include "particleSet.h"
#include "particle.h"

// ====================================================================


//构造函数  一个质点系统由 质点生成器，积分方法，所处力场 构造而成
System::System(Generator *g, Integrator *i, ForceField *f)
{
	assert(g != NULL);
	assert(i != NULL);
	assert(f != NULL);
	generator = g;
	integrator = i;
	forcefield = f;
	particles = NULL;
	//调用restart方法
	Restart();
}
//析构函数
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


//质点系统的刷新方法
void System::Update(float dt)
{
	// 更新每个质点
	int num_particles = particles->getNumParticles();
	for (int i = 0; i < num_particles; i++)
	{
		//具体调用 积分方法来 调整质点的属性
		integrator->Update(particles->Get(i), forcefield, current_time, dt);
	}

	// 同时由生成新的质点
	int num_new = generator->numNewParticles(current_time, dt);
	for (int i = 0; i < num_new; i++)
	{
		//具体调用生成器方法 生成全新的质点
		Particle *p = generator->Generate(current_time, i);
		assert(p != NULL);
		particles->Add(p);
	}

	// 及时移除过期的质点（否则内存...）
	particles->RemoveDead();

	// 当前时间点往后推移
	current_time += dt;
}


// ====================================================================

void System::PaintGeometry() const
{
	//部分生成器需要绘制
	generator->Paint();
}


void System::Paint(float dt, int integrator_color, int draw_vectors,
	float acceleration_scale, int motion_blur) const
{

	
	if (integrator_color) {
		Vec3f c = integrator->getColor();
		glColor3f(c.r(), c.g(), c.b());
	}

	// 绘制质点

	int num_particles = particles->getNumParticles();
	for (int i = 0; i < num_particles; i++)
	{

		//在质点集合（即质点系统中） 调用每个质点的绘制方法（）
		particles->Get(i)->Paint(dt, integrator_color, draw_vectors, motion_blur);
	}

	// 部分需要绘制直线
	/*

	由质点 指向加速度  相当于绘制  高中物理中的 力线（）

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