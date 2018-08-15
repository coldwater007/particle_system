#pragma once
#include <stdlib.h>
#include "vectors.h"

class Parser;

// ====================================================================
// A simplied version of the code from the OpenGL assignment

class GLCanvas {

public:
	// 构造和析构函数
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

	//标记是否暂停演示
	static int   paused;

	//刷新间隔
	static float refresh;

	//System::Update函数每次会让时间仿真地向前走的时间  
	static float dt;

	//积分_颜色, 用于对不同的积分策略着色  
	static int   integrator_color;

	//将以和质点同样的颜色画出速度向量  
	static int   draw_vectors;

	//以白色画出伸缩过的加速度向量
	static float acceleration_scale;


	static int   motion_blur;          //在2次位置之间绘制直线

									   // GUI外部事件处理
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
