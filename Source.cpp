#include <iostream>
#include <conio.h>
#include <cmath>
#include <math.h>

using namespace std;

/*
Note: 
Target can only be between 0 and 1.
Inputs can only be between 0 and 1.
There is only 1 hidden layer.
There is only 1 output neuron.
*/

int main()
{
	/*MAKE INPUT VALUES*/
	int NumOfInputs;
	int NumOfHidNeur;
	double e = 2.71828182845904523536;
	double *ValOfHiddenNeurons = NULL;
	double *ValOfOutputWeights = NULL;
	double *ValHiddenError = NULL;
	double *ValOfWeights = NULL;	
	double *ValOfInputs = NULL;
	double *MultiplyPointer = NULL;
	double InputVal;
	double WightVal;
	double target;

	cout << "What is the target" << endl;
	cin >> target;

	cout << "How many inputs" << endl;
	cin >> NumOfInputs;

	cout << "How many Hidden Neurons" << endl;
	cin >> NumOfHidNeur;

	ValOfInputs = new double[NumOfInputs];
	ValOfHiddenNeurons = new double[NumOfHidNeur];
	ValHiddenError = new double[NumOfHidNeur];

	cout << endl;

	for(int a = 0; a < NumOfInputs; a++)
	{
		cout << "What is the value for input " << a << endl;
		a+1;
		cin >> InputVal;
		*(ValOfInputs + a) = InputVal;
	}
	cout << endl;

	/*SET HIDDEN WEIGHTS - Randomly made*/
	ValOfWeights = new double[NumOfInputs];
	for(int a = 0; a < NumOfInputs; a++)
	{
		*(ValOfWeights + a) = (float)rand()/RAND_MAX;
	}

	/*SET OUTPUT WEIGHTS - Randomly made*/
	ValOfOutputWeights = new double[NumOfHidNeur];
	for(int a = 0; a < NumOfHidNeur; a++)
	{
		*(ValOfOutputWeights + a) = (float)rand()/RAND_MAX;
	}

	for(int i = 0; i < 500; i++)
	{
		/*RESET ERRORS AND FINALS*/
		double OutError = 0;
		double OutFinal = 0;
		for(int z = 0; z < NumOfHidNeur; z++)
		{
			ValHiddenError[z] = 0;
		}
		int WH = 0;

		/*INPUTS TO HIDDEN LAYER*/
		for(int a = 0; a < NumOfHidNeur; a++)
		{
			/*SUMIFICATION*/
			MultiplyPointer = new double[NumOfInputs];
			for(int b = 0; b < NumOfInputs; b++)
			{
				MultiplyPointer[b] = ValOfInputs[b] * ValOfWeights[WH];
				WH++;
			}

			/*ADD VALUES*/
			double netj = 0;
			for(int b = 0; b < NumOfInputs; b++)
			{
				netj += MultiplyPointer[b];
			}

			/*SIGMOIDAL UNI-POLAR*/
			ValOfHiddenNeurons[a] = (1/(1 + pow(e, -netj)));
		}

		/*HIDDEN LAYER TO OUTPUT*/
		/*SUMIFICATION OUTPUT*/
		MultiplyPointer = new double[NumOfHidNeur];
		for(int c = 0; c < NumOfHidNeur; c++)
		{
			MultiplyPointer[c] = ValOfHiddenNeurons[c] * ValOfOutputWeights[c];
		}

		/*ADD VALUES OUTPUT*/
		double netj = 0;
		for(int d = 0; d < NumOfHidNeur; d++)
		{
			netj += MultiplyPointer[d];
		}

		/*SIGMOIDAL UNI-POLAR OUTPUT*/
		OutFinal = (1/(1 + pow(e, -netj)));
		cout << "target = " << target << endl;
		cout << "Output final = " << OutFinal << endl;

		/*BACK PROPAGATION - No learning rate value*/
		/*GET OUTPUT LAYER ERROR*/
		OutError = OutFinal * (1 - OutFinal) * (target - OutFinal);

		/*GET HIDDEN LAYER ERROR*/
		for(int f = 0; f < NumOfHidNeur; f++)
		{
			ValHiddenError[f] = ValOfHiddenNeurons[f] * (1 - ValOfHiddenNeurons[f]) * (OutError * ValOfOutputWeights[f]);
		}

		/*OUTPUT LAYER WEIGHT CHANGE*/
		for(int g = 0; g < NumOfHidNeur; g++)
		{
			ValOfOutputWeights[g] = ValOfOutputWeights[g] + (OutError * OutFinal);
		}

		/*HIDDEN LAYER WEIGHT CHANGE*/
		int HWNew = 0;
		for(int h = 0; h < NumOfHidNeur; h++)
		{
			for(int i = 0; i < NumOfInputs; i++)
			{
				ValOfWeights[HWNew] = ValOfWeights[HWNew] + (ValHiddenError[h] * ValOfWeights[i]);
				HWNew++;
			}
		}
	}

	cout << endl << "Press any key to close" << endl;
	_getch();
	return 0;
}