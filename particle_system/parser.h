#pragma once

#include <assert.h>
#include "vectors.h"

#include "system.h"
#include "Generator.h"
#include "Integrator.h"
#include "ForceField.h"

#define MAX_PARSER_TOKEN_LENGTH 100

// ====================================================================
// ====================================================================



class Parser {

public:


	Parser(const char *file);
	~Parser();

	
	int getNumSystems() { return num_systems; }
	System* getSystem(int i) {
		assert(i >= 0 && i < num_systems);
		return systems[i];
	}

private:
	// don't use this constructor
	Parser() { assert(0); }

	// HELPER FUNCTIONS
	System* ParseSystem();
	Generator* ParseGenerator();
	Integrator* ParseIntegrator();
	ForceField* ParseForceField();

	// ..UTILITY FUNCTIONS
	int getToken(char token[MAX_PARSER_TOKEN_LENGTH]);
	Vec3f readVec3f();
	Vec2f readVec2f();
	float readFloat();
	int readInt();

	// REPRESENTATION
	int num_systems;
	System **systems;
	FILE *file;
};

