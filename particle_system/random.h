#pragma once

//
// ���ཫ�������ظ���α�������
// ͨ��ʹ��Random ��������drand48()�� ����Զ����ͬ�����������ֱ�ӱȽϸ����ʵ�ϵͳѡ�� (��ͬ���ٶȣ�����λ������ԣ�randomness��, ��ͬ�Ļ��ַ�����)

#include "vectors.h"

class Random {

public:

	Random(int seed = 0) { last = seed; }
	~Random() {}

	// returns a random floating point between 0 & 1

	//����һ���������0��1֮��ĸ�����
	float next() {
		last = (1366 * last + 150889) % 714025;
		float answer = last / float(714025);
		return answer;
	}

	// return a random vector with each component from -1 -> 1

	//����һ��ÿ��ֵ��-1��1֮�������
	Vec3f randomVector() {
		float x = next() * 2 - 1;
		float y = next() * 2 - 1;
		float z = next() * 2 - 1;
		return Vec3f(x, y, z);
	}

private:

	int last;
};

