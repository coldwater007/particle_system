#pragma once

//
// 该类将产生可重复的伪随机数流
// 通过使用Random 类来代替drand48()， 你可以多个相同的随机数流来直接比较各种质点系统选项 (不同的速度，或者位置随机性（randomness）, 不同的积分方法等)

#include "vectors.h"

class Random {

public:

	Random(int seed = 0) { last = seed; }
	~Random() {}

	// returns a random floating point between 0 & 1

	//返回一个随机的在0和1之间的浮点数
	float next() {
		last = (1366 * last + 150889) % 714025;
		float answer = last / float(714025);
		return answer;
	}

	// return a random vector with each component from -1 -> 1

	//返回一个每个值在-1到1之间的向量
	Vec3f randomVector() {
		float x = next() * 2 - 1;
		float y = next() * 2 - 1;
		float z = next() * 2 - 1;
		return Vec3f(x, y, z);
	}

private:

	int last;
};

