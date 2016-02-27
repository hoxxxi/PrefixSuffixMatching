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
#include <vector>

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
	vector<ProbabilityMatrix> leftProbabilityMatrixes;
	vector<ProbabilityMatrix> rightProbabilityMatrixes;

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
			  case 3:
			  {
				  left_score = line;

				  //Add to vector
				  ProbabilityMatrix left_probability_matrix(left_sequence,left_score);
				  leftProbabilityMatrixes.push_back(left_probability_matrix);
			  } break;
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
			  case 3:
			  {
				  right_score = line;

				  // Convert read from right file to reverse DNA inverse
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

				  //Add to vector
				  ProbabilityMatrix right_probability_matrix(right_sequence,right_score);
				  rightProbabilityMatrixes.push_back(right_probability_matrix);
			  } break;
			  default: break;
			}
			lineCounter++;
		}
		right_file.close();
	}
	for(unsigned int vi = 0; vi < leftProbabilityMatrixes.size() && vi < rightProbabilityMatrixes.size();vi++)
	{
		StringMatching in(&leftProbabilityMatrixes.at(vi), &rightProbabilityMatrixes.at(vi));

		ProbabilityMatrix resultingMatrix = in.joinedMatrix();
		resultingMatrix.setInitialMatrix();
		resultingMatrix.calculateDistributedMatrixProbability(100);

		cout<<resultingMatrix.sequence<<"\n";
		cout<<resultingMatrix.score<<"\n";
		resultingMatrix.printMatrix();
	}
}
