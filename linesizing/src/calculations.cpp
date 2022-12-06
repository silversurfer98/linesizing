#include"calc.h"

void colebrook_f::get_data(float* x, float scale, const char* c)
{

	std::cout << "Enter the " << c <<" : ";
	std::cin >> *x;
	while (std::cin.fail())
    {
        std::cin.clear(); // clear input buffer to restore cin to a usable state
        std::cin.ignore(); // ignore last input
        std::cout << "You can only enter numbers.\n";
        std::cout << "Enter the " << c <<" : ";
        std::cin >> *x;
    }

	*x = *x * scale;
}

void colebrook_f::prep_data()
{
	get_data(&fl, 2.77778e-04, "flowrate in m3/hr");
	get_data(&dia, 25.4, "diameter in inch");
	get_data(&l, 1, "equivalent length in m");
	get_data(&e, 1e-03, "rougness factor in mm");
	get_data(&den, 1, "density in kg/m3");
	get_data(&dvisc, 1e-03, "dynamic visc in cP (0.001 Pa.s --> 1 cP)");

}

void colebrook_f::initialize()
{
	vel = fl / (pi * 0.25 * dia * dia);
	re = vel * dia * den / dvisc;

	c = e / (3.7 * dia);
	r = 2.51 / re;

}


// x = 1 / sqrt(f)
inline float colebrook_f::colebrook(float x)
{
	float a = c + (r * x);
	//return x + (coeff * log(a));
	return x + (2 * log10(a));

}

inline float colebrook_f::colebrook_derv(float x)
{
	float a = c + (r * x);
	a = r / a;
	//return 1 + coeff * a;
	return 1 + 2 * a;
}

float colebrook_f::iterative_3_pt_algo(float x0)
{
	float y0, z0, x1, t1, t2, t3;

	float xt1 = colebrook(x0);
	float xtd = colebrook_derv(x0);
	y0 = x0 - (xt1 / xtd);

	float xt2 = colebrook(y0);
	z0 = y0 - (xt1 * xt2) / ((xt1 - (2 * xt2)) * xtd);

	float xt3 = colebrook(z0);
	t1 = 1 - (2 * (xt2 / xt1) - ((xt2 * xt1) * (xt2 * xt1)));
	t2 = (1 - (xt3 / xt2)) * (1 - 2 * (xt2 / xt1));
	t3 = xt3 / (xtd * t1 * t2);

	x1 = z0 - t3;
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

float colebrook_f::p_drop(float f)
{
	return f * l * den * vel * vel / (2 * dia);
}

void colebrook_f::report()
{
	float fric_factor = 0;
	float pdrop = 0;
	if(re<2000)
	{
		std::cout<<"\n\n ------- The flow is laminar no need for complex f calc ------- \n\n";
		fric_factor = 64/re;
		pdrop = p_drop(fric_factor);

		std::cout << "\n\n************** RESULTS ********************\n";
		std::cout << "Diameter in m : " << dia;
		std::cout << "\nVelocity in m/s : " << vel;
		std::cout << "\nfriction factor : " << fric_factor;
		std::cout << "\nReynold number : " << re;
		//std::cout << "pressure drop is " << pdrop * 1e-05 << " in bar\n\n";
		std::cout << "\npressure drop is " << pdrop << " in pascal";
		std::cout << "\n*******************************************\n\n";
		
	}

	else
	{
		std::cout<<"\n ----- flow is obviously turbulent / transition state -----\n";
		std::cout << " \n\n enter the method to solve : \n1. 3 point iteration\n2. newton raphson\nEnter ur choice : ";
		uint16_t ch = 0;
		std::cin >> ch;

		if (ch == 1)
		{
			fric_factor = iterative_3_pt();
			pdrop = p_drop(fric_factor);

			std::cout << "\n\n************** RESULTS ********************\n";
			std::cout << "Diameter in m : " << dia;
			std::cout << "\nVelocity in m/s : " << vel;
			std::cout << "\nfriction factor : " << fric_factor;
			std::cout << "\nReynold number : " << re;
			//std::cout << "pressure drop is " << pdrop * 1e-05 << " in bar\n\n";
			std::cout << "\npressure drop is " << pdrop << " in pascal";
			std::cout << "\n*******************************************\n\n";

		}

		else if (ch == 2)
		{
			fric_factor = newton_raphson();
			pdrop = p_drop(fric_factor);

			std::cout << "************** RESULTS ********************\n";
			std::cout << "\n\nDiameter in m : " << dia;
			std::cout << "\nVelocity in m/s : " << vel;
			std::cout << "\nfriction factor : " << fric_factor;
			std::cout << "\nReynold number : " << re;
			//std::cout << "pressure drop is " << pdrop * 1e-05 << " in bar\n\n";
			std::cout << "\npressure drop is " << pdrop << " in pascal";
			std::cout << "\n*******************************************\n\n";

		}
		else
		{
			std::cout << "\n\nwaathaaa\n\n\n";
			report();
		}
	}
}