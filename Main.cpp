//============================================================================
// Name        : Main.cpp
// Author      : Yordan
// Version     : 1.1
// Copyright   : Your copyright notice
// Description : main
//============================================================================


#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "StringMatching.cpp"

using namespace std;

char dnaInverse(char in)
{
	switch(in)
	{
	case 'A': return 'T';
	case 'C': return 'G';
	case 'G': return 'C';
	case 'T': return 'A';
	default: return 'E';
	}

}
int main()
{
	string line;
	int lineCounter;

	string left_sequenceID;
	string left_sequence;
	string left_score;

	ifstream left_file ("left.txt", ios::in);
	if (left_file.is_open())
	{
		lineCounter = 0;
		while (getline(left_file, line))
		{
			switch (lineCounter%5)
			{
			  case 0: left_sequenceID = line; break;
			  case 1: left_sequence = line; break;
			  case 2: break;
			  case 3: left_score = line; break;
			  case 4: break;
			  default: break;
			}
			lineCounter++;
		}
		left_file.close();
	}

	string right_sequenceID;
	string right_sequence;
	string right_score;

	ifstream right_file ("right.txt", ios::in);
	if (right_file.is_open())
	{
		lineCounter = 0;
		while (getline(right_file, line))
		{
			switch (lineCounter%5)
			{
			  case 0: right_sequenceID = line; break;
			  case 1: right_sequence = line; break;
			  case 2: break;
			  case 3: right_score = line; break;
			  case 4: break;
			  default: break;
			}
			lineCounter++;
		}
		right_file.close();
	}

	char tempSequence;
	char tempScore;
	for(unsigned int i = 0; i<((right_sequence.size()/2)+(right_sequence.size()%2)); i++)
	{
		tempSequence = right_sequence[i];
		right_sequence[i] = dnaInverse(right_sequence[right_sequence.size()-1-i]);
		right_sequence[right_sequence.size()-1-i] = dnaInverse(tempSequence);

		tempScore = right_score[i];
		right_score[i] = right_score[right_score.size()-1-i];
		right_score[right_score.size()-1-i] = tempScore;
	}

	ProbabilityMatrix left_probability_matrix(left_sequence,left_score);
	left_probability_matrix.setInitialMatrix();
	left_probability_matrix.calculateDistributedMatrixProbability(100);

	ProbabilityMatrix right_probability_matrix(right_sequence,right_score);
	right_probability_matrix.setInitialMatrix();
	right_probability_matrix.calculateDistributedMatrixProbability(100);

	StringMatching in(left_probability_matrix, right_probability_matrix);
	ProbabilityMatrix resultingMatrix = in.joinedMatrix();
	cout<<resultingMatrix.sequence<<"\n";
	cout<<resultingMatrix.score<<"\n";
	resultingMatrix.setInitialMatrix();
	resultingMatrix.calculateDistributedMatrixProbability(100);
	resultingMatrix.printMatrix();
}
