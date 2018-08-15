
#include "parser.h"
#include "system.h"
#include "Generator.h"
#include "Integrator.h"
#include "ForceField.h"


#include "HoseGenerator.h"
#include "RingGenerator.h"

#include "EulerIntegrator.h"
#include "TrapzIntegrator.h"            //..梯形法
#include "MidpointIntegrator.h"
#include "RungeKuttaIntegrator.h"

#include "RadialForceField.h"
#include "GravityForceField.h"
#include "ConstantForceField.h"
#include "VerticalForceField.h"
#include "WindForceField.h"             //..风力场

// ====================================================================
// ====================================================================

Parser::Parser(const char *filename)
{
	// 打开文件
	assert(filename != NULL);
	file = fopen(filename, "r");
	assert(file != NULL);
	char token[MAX_PARSER_TOKEN_LENGTH];

	// 根据文件格式 先获取系统数目
	getToken(token);
	assert(!strcmp(token, "num_systems"));
	num_systems = readInt();
	//申请缓冲区
	systems = new System*[num_systems];

	// 读取对应的质点系统
	for (int i = 0; i < num_systems; i++)
	{
		System *s = ParseSystem();
		assert(s != NULL);
		systems[i] = s;
	}
	fclose(file);
}

//释放缓冲区
Parser::~Parser() {

	for (int i = 0; i < num_systems; i++) {
		delete systems[i];
	}
	delete[] systems;
}

// ====================================================================

System* Parser::ParseSystem()
{

	/*

	质点系统文件格式如：

	system
	hose_generator {
	position -5 0 0
	position_randomness 0.6
	velocity  4 0 0
	color 1 1 0
	}
	euler_integrator {
	}
	constant_forcefield {
	}

	先指明为System
	之后对应具体的Genertor(生成器)
	积分方法
	力场类别



	*/

	char token[MAX_PARSER_TOKEN_LENGTH];
	getToken(token);
	assert(!strcmp(token, "system"));
	Generator  *generator = ParseGenerator();    // 粒子生成器类对象
	Integrator *integrator = ParseIntegrator();   // 积分类对象
	ForceField *forcefield = ParseForceField();   // 力场类对象
	return new System(generator, integrator, forcefield);
}

// ====================================================================
// ====================================================================
// ====================================================================

Generator* Parser::ParseGenerator()
{
	// read the generator type
	char type[MAX_PARSER_TOKEN_LENGTH];
	getToken(type);

	// 粒子生成器 初始值
	//位置
	Vec3f position = Vec3f(0, 0, 0);
	float position_randomness = 0;
	//速度
	Vec3f velocity = Vec3f(0, 0, 0);
	float velocity_randomness = 0;
	//颜色
	Vec3f color = Vec3f(1, 1, 1);
	Vec3f dead_color = Vec3f(1, 1, 1);
	float color_randomness = 0;
	//质量
	float mass = 1;
	float mass_randomness = 0;
	//生命期
	float lifespan = 10;
	float lifespan_randomness = 0;
	int desired_num_particles = 1000;
	int grid = 10;
	float ring_velocity = 1;

	// read the provided values
	char token[MAX_PARSER_TOKEN_LENGTH];
	getToken(token);
	assert(!strcmp(token, "{"));
	while (1) {
		getToken(token);
		if (!strcmp(token, "position")) {
			position = readVec3f();
		}
		else if (!strcmp(token, "position_randomness")) {
			position_randomness = readFloat();
		}
		else if (!strcmp(token, "velocity")) {
			velocity = readVec3f();
		}
		else if (!strcmp(token, "velocity_randomness")) {
			velocity_randomness = readFloat();
		}
		else if (!strcmp(token, "color")) {
			color = readVec3f();
			dead_color = color;
		}
		else if (!strcmp(token, "dead_color")) {
			dead_color = readVec3f();
		}
		else if (!strcmp(token, "color_randomness")) {
			color_randomness = readFloat();
		}
		else if (!strcmp(token, "mass")) {
			mass = readFloat();
		}
		else if (!strcmp(token, "mass_randomness")) {
			mass_randomness = readFloat();
		}
		else if (!strcmp(token, "lifespan")) {
			lifespan = readFloat();
		}
		else if (!strcmp(token, "lifespan_randomness")) {
			lifespan_randomness = readFloat();
		}
		else if (!strcmp(token, "desired_num_particles")) {
			desired_num_particles = readInt();
		}
		else if (strcmp(token, "}")) {
			printf("ERROR unknown generator token %s\n", token);
			assert(0);
		}
		else {
			break;
		}
	}

	// create the appropriate generator
	Generator *answer = NULL;
	if (!strcmp(type, "hose_generator")) {
		answer = new HoseGenerator(position, position_randomness,
			velocity, velocity_randomness);
	}
	else if (!strcmp(type, "ring_generator")) {
		answer = new RingGenerator(position_randomness, velocity, velocity_randomness);
	}
	else {
		printf("WARNING:  unknown generator type '%s'\n", type);
		printf("WARNING:  unknown generator type '%s'\n", type);
	}

	// set the common generator parameters
	assert(answer != NULL);
	answer->SetColors(color, dead_color, color_randomness);
	answer->SetMass(mass, mass_randomness);
	answer->SetLifespan(lifespan, lifespan_randomness, desired_num_particles);

	return answer;
}

// ====================================================================
// ====================================================================
// ====================================================================

Integrator* Parser::ParseIntegrator() {
	// read the integrator type
	char type[MAX_PARSER_TOKEN_LENGTH];
	getToken(type);

	// there are no variables
	char token[MAX_PARSER_TOKEN_LENGTH];
	getToken(token);
	assert(!strcmp(token, "{"));
	getToken(token);
	assert(!strcmp(token, "}"));

	// create the appropriate integrator
	Integrator *answer = NULL;
	if (!strcmp(type, "euler_integrator")) {
		answer = new EulerIntegrator();
	}
	else if (!strcmp(type, "midpoint_integrator")) {
		answer = new MidpointIntegrator();
	}
	else if (!strcmp(type, "rungekutta_integrator")) {
		answer = new RungeKuttaIntegrator();
	}
	else {
		printf("WARNING:  unknown integrator type '%s'\n", type);
	}
	assert(answer != NULL);
	return answer;
}

// ====================================================================
// ====================================================================
// ====================================================================

ForceField* Parser::ParseForceField() {
	// read the forcefield type
	char type[MAX_PARSER_TOKEN_LENGTH];
	getToken(type);

	// forcefield variable defaults
	Vec3f gravity = Vec3f(0, 0, 0);
	Vec3f force = Vec3f(0, 0, 0);
	float magnitude = 1;

	// read the provided values
	char token[MAX_PARSER_TOKEN_LENGTH];
	getToken(token);
	assert(!strcmp(token, "{"));
	while (1) {
		getToken(token);
		if (!strcmp(token, "gravity")) {
			gravity = readVec3f();
		}
		else if (!strcmp(token, "force")) {
			force = readVec3f();
		}
		else if (!strcmp(token, "magnitude")) {
			magnitude = readFloat();
		}
		else if (strcmp(token, "}")) {
			printf("ERROR unknown gravity token %s\n", token);
			assert(0);
		}
		else {
			break;
		}
	}

	// create the appropriate force field
	ForceField *answer = NULL;
	if (!strcmp(type, "gravity_forcefield")) {
		answer = new GravityForceField(gravity);
	}
	else if (!strcmp(type, "constant_forcefield")) {
		answer = new ConstantForceField(force);
	}
	else if (!strcmp(type, "radial_forcefield")) {
		answer = new RadialForceField(magnitude);
	}
	else if (!strcmp(type, "vertical_forcefield")) {
		answer = new VerticalForceField(magnitude);
	}
	else if (!strcmp(type, "wind_forcefield")) {
		answer = new WindForceField(magnitude);
	}
	else {
		printf("WARNING:  unknown forcefield type '%s'\n", type);
	}
	assert(answer != NULL);
	return answer;
}

// ====================================================================
// ====================================================================
// HELPER FUNCTIONS

int Parser::getToken(char token[MAX_PARSER_TOKEN_LENGTH]) {
	// for simplicity, tokens must be separated by whitespace
	assert(file != NULL);
	int success = fscanf(file, "%s ", token);
	if (success == EOF) {
		token[0] = '\0';
		return 0;
	}
	return 1;
}


Vec3f Parser::readVec3f() {
	float x, y, z;
	int count = fscanf(file, "%f %f %f", &x, &y, &z);
	if (count != 3) {
		printf("Error trying to read 3 floats to make a Vec3f\n");
		assert(0);
	}
	return Vec3f(x, y, z);
}


Vec2f Parser::readVec2f() {
	float u, v;
	int count = fscanf(file, "%f %f", &u, &v);
	if (count != 2) {
		printf("Error trying to read 2 floats to make a Vec2f\n");
		assert(0);
	}
	return Vec2f(u, v);
}


float Parser::readFloat() {
	float answer;
	int count = fscanf(file, "%f", &answer);
	if (count != 1) {
		printf("Error trying to read 1 float\n");
		assert(0);
	}
	return answer;
}


int Parser::readInt() {
	int answer;
	int count = fscanf(file, "%d", &answer);
	if (count != 1) {
		printf("Error trying to read 1 int\n");
		assert(0);
	}
	return answer;
}
