#include"calc.h"

void colebrook_f::get_data(float* x, float scale, const char* c)
{
	std::cout << "Enter the " << c <<" : ";
	std::cin >> *x;
	*x = *x * scale;
}

void colebrook_f::prep_data()
{
	get_data(&fl, 1, "flowrate in m3/s");
	get_data(&dia, 1e-03, "diameter in mm");
	get_data(&l, 1, "length in m");
	get_data(&e, 1e-06, "rougness factor in um");
	get_data(&den, 1, "density in kg/m3");
	get_data(&dvisc, 1e-03, "dynamic visc in mPa.s");

	vel = fl / (pi * 0.25 * dia * dia);
	re = vel * dia * den / dvisc;

	c = e / (3.7 * dia);
	r = 2.51 / re;

	/*c = 2.5e-05 / 3.7;
	r = 2.5 / 5e06;*/
}

inline float colebrook_f::colebrook(float x)
{
	float a = c + (r * x);
	return x + (coeff * mln(a));
}

inline float colebrook_f::colebrook_derv(float x)
{
	float a = c + (r * x);
	a = r / a;
	return 1 + coeff * a;
}

float colebrook_f::iterative_3_pt_algo(float x0)
{
	float y0, z0, x1, t1, t2, t3;
	//print("x0", x0);
	y0 = x0 - (colebrook(x0) / colebrook_derv(x0));
	//print("y0", y0);
	z0 = y0 - (colebrook(x0) * colebrook(y0)) / ((colebrook(x0) - (2 * colebrook(y0))) * colebrook_derv(x0));
	//print("z0", z0);
	t1 = 1 - (2 * (colebrook(y0) / colebrook(x0)) - ((colebrook(y0) * colebrook(x0)) * (colebrook(y0) * colebrook(x0))));
	t2 = (1 - (colebrook(z0) / colebrook(y0))) * (1 - 2 * (colebrook(y0) / colebrook(x0)));
	t3 = colebrook(z0) / (colebrook_derv(x0) * t1 * t2);

	x1 = z0 - t3;
	//print("x1", x1);
	return x1;
}

bool colebrook_f::absolute(float x, float y, float t)
{
	float temp = x - y;
	if (temp < 0)
		temp = temp * -1;
	if (temp < t)
		return false;
	else
		return true;
}

float colebrook_f::iterative_3_pt()
{
	//float x0 = -1 * coeff * mln(c);
	float x0 = 7.273124147;
	//print("intial guess", x0);
	float x1 = iterative_3_pt_algo(x0);

	//use this iteration if the case is worst xD
	/*x0 = x1;
	x1 = iterative_3_pt_algo(x0);*/

	float f = 1 / (x1 * x1);
	return f;
}

float colebrook_f::newton_raphson()
{
	float x0 = 7.273124147;
	float x1 = x0 - colebrook(x0) / colebrook_derv(x0);
	while (absolute(x0, x1, tolerance))
	{
		x0 = x1;
		x1 = x0 - colebrook(x0) / colebrook_derv(x0);
	}
	float f = 1 / (x1 * x1);
	return f;
}

float colebrook_f::p_drop()
{
	return iterative_3_pt() * l * den * vel * vel / (2 * dia);
}