#pragma once
#include<iostream>
#include<math.h>

class colebrook_f
{
public:
	float fl, dia, l, e, den, dvisc, pi = 3.14159265359;
	float vel, re, c, r;
	//float coeff = 0.8685889638;   // 2 / ln 10

	//float f; // the battle is for this
	float tolerance = 1e-08;

	void get_data(float* x, float scale, const char* c);
	void prep_data();
	void initialize();

	float colebrook(float x);
	float colebrook_derv(float x);
	bool absolute(float x, float y, float t);

	float iterative_3_pt_algo(float x0);
	float iterative_3_pt();
	float newton_raphson();
	float p_drop(float f);

	void report();

};