#include <iostream>
#include <math.h>

#define NUMBERS 4
#define SCALE 1
#define INTERVAL 50
#define JUMP 10

using namespace std;


#pragma region DZIALA
void crtMiddlePoints(double *distance, double *points)
{
	double tmp = 0;
	int k = 0;
	for (int i = 0; i < NUMBERS - 1; i++)
	{
		tmp = distance[i + 1] - distance[i];
		tmp = tmp / SCALE;

		for (int j = 0; j < SCALE; j++)
			points[k++] = distance[i] + tmp*(j+1);
	}
}

int crtSection(int counter, int *i)
{
	int section = 0;
	if (counter > INTERVAL)
		*i = counter - INTERVAL;
	section = counter + INTERVAL;
	if (section > NUMBERS)
		section = NUMBERS;
	
	return section;
}

double polynomial(double *distance, int counter, double element)
{
	double result = 1;
	int i = 0;
	int section = 0;

	section = crtSection(counter, &i);

	for (; i < section; i++)
	{
		if (element == distance[i])
			continue;
		result *= (element - distance[i]);
	}
	
	return result; 
}

double lagrangeInterpolation(double *distance, double *height, double point)
{
	double result = 0;
	double *polynomialDistanceResults;
	double polynomialResult = 0.0;
	polynomialDistanceResults = (double *)malloc(sizeof(double)*INTERVAL);

	polynomialResult = 0.0;
		
		polynomialResult = polynomial(distance, 0, point);

		for (int j = 0; j < INTERVAL; j++)
			polynomialDistanceResults[j] = polynomial(distance, j, distance[j]);
		
		for (int j = 0; j < INTERVAL; j++)
		{
			double tmp = 0;
			tmp = pow(point - distance[j], -1);
			tmp *= height[j] / polynomialDistanceResults[j];
			result += tmp;

		}
		
		result = result*polynomialResult;

		return result;
}

#pragma endregion



int main()
{
	
#pragma region ZMIENNE 

	double *distance; // Odleg³oœci
	double *height; // Wysokoœci 
	double *points; // Punkty poœrednie 
	double *results; // Wyniki 

	distance = (double*)malloc(sizeof(double)* NUMBERS);
	height = (double*)malloc(sizeof(double)* NUMBERS);
	points = (double*)malloc(sizeof(double)*NUMBERS*SCALE);
	results = (double*)malloc(sizeof(double)*NUMBERS*SCALE);

	//double distance[] = { 12, 13, 14, 15, 16 };
	//double height[] = { 24, 25, 23, 20, 16 };

	for (int i = 0; i < NUMBERS; i++)
	{
		cin >> distance[i];
		cin >> height[i];
		for (int j = 0; j < JUMP; j++)
		{
			double tmp;
			cin >> tmp;
			cin >> tmp;		
		}
	}

	for (int i = 0; i < NUMBERS*SCALE; i++)
		points[i] = 0;

	points[0] = distance[0];
	for (int i = 1; i < NUMBERS*SCALE; i++)
		points[i] = points[i-1]+0.5*2;

	for (int i = 0; i < NUMBERS*SCALE; i++)
		results[i] = 0;


	//crtMiddlePoints(distance, points);
	cout.precision(20);

#pragma endregion

	for (int i = 0; i < NUMBERS; i++)
		results[i] = lagrangeInterpolation(distance, height, points[i]);


	for (int i = 0; i < NUMBERS; i++)
	{
		//cout /*<< points[i] << ' ' */<< results[i] << endl;
		//cout << points[i] << endl;
		cout << distance[i] << " " << height[i]<< endl;
		//cout << height[i] << endl;

	}

	return 0;
} 