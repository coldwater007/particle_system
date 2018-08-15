#pragma once
#include <stdlib.h>
#include "vectors.h"

class Parser;

// ====================================================================
// A simplied version of the code from the OpenGL assignment

class GLCanvas {

public:
	// �������������
	GLCanvas(void) { }
	~GLCanvas(void) { }

	
	static void initialize(Parser *parser, float refresh, float dt,
		int integrator_color, int draw_vectors,
		float acceleration_scale, int motion_blur);

private:

	// the system
	static Parser *parser;

	// viewport & mouse
	static Vec3f camera_pos;
	static int width;
	static int height;
	static int mouse_button;
	static int mouse_x;
	static int mouse_y;

	// actions & rendering

	//����Ƿ���ͣ��ʾ
	static int   paused;

	//ˢ�¼��
	static float refresh;

	//System::Update����ÿ�λ���ʱ��������ǰ�ߵ�ʱ��  
	static float dt;

	//����_��ɫ, ���ڶԲ�ͬ�Ļ��ֲ�����ɫ  
	static int   integrator_color;

	//���Ժ��ʵ�ͬ������ɫ�����ٶ�����  
	static int   draw_vectors;

	//�԰�ɫ�����������ļ��ٶ�����
	static float acceleration_scale;


	static int   motion_blur;          //��2��λ��֮�����ֱ��

									   // GUI�ⲿ�¼�����
	static void display(void);
	static void reshape(int w, int h);
	static void mouse(int button, int state, int x, int y);
	static void motion(int x, int y);
	static void keyboard(unsigned char key, int x, int y);
	static void idle(int value);

	// helper functions
	static void step();
	static void restart();
};
