/*
 * SimpleStringMatch.cpp
 *
 *  Created on: 11.02.2016 г.
 *      Author: User
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include "ProbMatrix.cpp"

using namespace std;

struct StringMatching
{
	ProbabilityMatrix left;
	ProbabilityMatrix right;

	StringMatching(ProbabilityMatrix leftIn, ProbabilityMatrix rightIn) : left(leftIn), right(rightIn){}

	int overlap(){
		int looplimit = min(left.sequence.size(),right.sequence.size());
		for(int i = 0; i < looplimit; i++)
		{
			int window = left.sequence.size()-i;

			if(left.sequence.substr(left.sequence.size()-window,window)==right.sequence.substr(0,window))
			{
				return window;
			}
		}
		return 0;
	}
	ProbabilityMatrix joinedMatrix()
	{
		stringstream sequence;
		stringstream score;
		int overlapping = overlap();

		sequence << left.sequence.substr(0,left.sequence.size()-overlapping)<<right.sequence;
		score << left.score.substr(0,left.score.size()-overlapping);


		string OverlappingQSsequenceLeft = left.score.substr(left.score.size()-overlapping,overlapping);
		string OverlappingQSsequenceRight = right.score.substr(0,overlapping);

		for(int i = 0; i<overlapping;i++)
		{
			//Cast the QS character to its' numerical value
			double tempLeft = (double)((int) OverlappingQSsequenceLeft[i]);
			double tempRight = (double)((int) OverlappingQSsequenceRight[i]);

			char temp = (char) ((tempLeft+tempRight)/2);
			score<<temp;
		}
		score<<right.score.substr(overlapping,right.score.size()-overlapping);

		ProbabilityMatrix joinedMatrix(sequence.str(),score.str());
		return joinedMatrix;
	}
};
