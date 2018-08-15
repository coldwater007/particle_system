#pragma once

#include <assert.h>
#include "vectors.h"

#include "particle.h"
#include "particleSet.h"
#include "Generator.h"
#include "Integrator.h"
#include "ForceField.h"

// ====================================================================
//该类控制一个particle系统    包括质点生成器，积分方法，以及力场类别
// ====================================================================




class System
{

public:

	// CONSTRUCTOR & DESTRUCTOR
	System(Generator *g, Integrator *i, ForceField *f);
	~System();

	// FUNCTIONALITY
	void Restart();

	//System::Update 方法每隔一段时间被调用一次(通过命令行选项 -refresh <seconds>指定),
	//Update 函数会随时间让仿真向前走 (每次走的时间由命令行选项-dt <seconds>指定）
	void Update(float dt);

	// RENDERING
	void Paint(float dt, int integrator_color, int draw_vectors,
		float acceleration_scale, int motion_blur) const;
	void PaintGeometry() const;


private:
	// don't use this constructor
	System() { assert(0); }

	// REPRESENTATION
	ParticleSet *particles;   //质点系统的质点集合
	Generator   *generator;  //质点系统的生成器
	Integrator  *integrator;   //质点系统的积分方法
	ForceField  *forcefield;  //力场类型
	float current_time;  //当前时间
};
