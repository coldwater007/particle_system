#include <gl\glut.h>
#include <gl\GL.h>

#include "particle.h"



//增加生存期中时间
void Particle::increaseAge(float a) {

	float t = 1;
	if (timeToDeath > 0)
		t = a / timeToDeath;
	if (t > 1) t = 1;
	color += t*(dead_color - color);

	// adjust the clock
	timeToDeath -= a;
}


void Particle::Paint(float dt, int integrator_color, int draw_vectors, int motion_blur) const
{

	// 设定颜色
	if (integrator_color == 0)
	{
		glColor3f(color.x(), color.y(), color.z());
	}

	// 绘制质点
	if (motion_blur == 0) {
		glPointSize(3);
		glBegin(GL_POINTS);
		glVertex3f(position.x(), position.y(), position.z());
		glEnd();
	}

	//.绘制速度向量
	if (draw_vectors == 1)
	{
		glLineWidth(1);
		glBegin(GL_LINES);
		Vec3f a = position;
		Vec3f b = position + dt*velocity;
		glVertex3f(a.x(), a.y(), a.z());
		glVertex3f(b.x(), b.y(), b.z());
		glEnd();
	}

	//绘制运动模糊线（在前一个点与当前点之间）
	if (motion_blur == 1) {
		glLineWidth(1);
		glBegin(GL_LINES);
		Vec3f a = position;
		Vec3f b = last_position;
		glVertex3f(a.x(), a.y(), a.z());
		glVertex3f(b.x(), b.y(), b.z());
		glEnd();
	}
}

