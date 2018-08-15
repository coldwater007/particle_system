#pragma once
#include "vectors.h"

// ================================================================
//    �ʵ���
// stores the information for a particle
// ..����һ�����Ӷ������Ϣ

class Particle {

public:

	// CONSTRUCTOR & DESTRUCTOR
	Particle(Vec3f p, Vec3f v, Vec3f _color, Vec3f _dead_color, float m, float lifespan) {
		position = p;              //���ڵ�λ��
		last_position = p;         //��һ�ε�λ��
		velocity = v;              //�ٶ�
		color = _color;			   // ���Ӳ���ʱ����ɫ
		dead_color = _dead_color;  // ������ʧʱ����ɫ
		mass = m;                  //��������
		timeToDeath = lifespan;    //��������ʱ�䣬���ϼ���
	}
	~Particle() {}

	// ACCESSORS

	//��ȡ�������ڵ�λ��
	Vec3f getPosition() const { return position; }
	//��ȡ�����ٶ�
	Vec3f getVelocity() const { return velocity; }
	//��ȡ������ɫ
	Vec3f getColor() const { return color; }
	//��ȡ��������
	float getMass() const { return mass; }
	//�ж������Ƿ�Ӧ����ʧ
	int isDead() const { if (timeToDeath <= 0) return 1; else return 0; }


	//��������λ��
	void setPosition(Vec3f p) { last_position = position; position = p; }
	//���������ٶ�
	void setVelocity(Vec3f v) { velocity = v; }
	//�������Ӳ���ʱ����ɫ
	void setColor(Vec3f c) { color = c; }
	//������������
	void setMass(float m) { mass = m; }
	//ʹ���ӵ���ɫ������������ɫ�仯��ʹ���ӵ���������a
	void increaseAge(float a);

	// Paint
	// ��������
	void Paint(float dt, int integrator_color, int draw_vectors, int motion_blur) const;

private:

	Particle() { assert(0); } // don't use this constructor


	Vec3f position;         //���ڵ�λ��
	Vec3f last_position;    //��һ�ε�λ��
	Vec3f velocity;		  //�ٶ�
	Vec3f color;            //TODO ���Ӳ���ʱ����ɫ
	Vec3f dead_color;       // ������ʧʱ����ɫ
	float mass;             //��������
	float timeToDeath;      //��������ʱ�䣬���ϼ���

};