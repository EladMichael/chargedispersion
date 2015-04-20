#include <TFile.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraph2D.h>
#include <TMultiGraph.h>
#include <TH1.h>
#include <iostream>
#include <algorithm>
using namespace std;

	// This code on the assumption that the histograms are named as follows:
	// PRF_li_i_lx_x_lz_z
	// in our convention, for example, pad 4, at the second step in x
	// and the first step in z would look like:
	// PRF_li_4_lx_2_lz_1

void Normalize(vector<double> &z)
{
double max = 0;
for (int i = 0; i < z.size(); ++i)
	{
		if(z[i]>max){max=z[i];}
	}

for (int i=0;i<z.size();++i)
	{
		z[i]=z[i]/max;
	}
}

void PRF()
{
TFile * f= new TFile("YOUR PATH HERE"); //File Path to the ROOT file
TH1D * h1 = new TH1D();
char buffer [50];
int a=0; //Counter for each event
double sum=0; //Sum of All pads maximum reading for each event
int xevents = 11; //How many steps in x (including 0)
int yevents = 4; //How many steps in y (including 0)
int pads = 14; //How many pads total
int perrow = 7; //Pads per row (For Symmetry calculations)

vector< vector<double> > maxima(xevents*yevents); //Collection of vectors, each vector has all readings from Pad 1 to n and the sum at the end

for (int i = 0; i < yevents; i++)
{
	for (int j = 0; j < xevents; j++)
	{
		for (int k = 1; k < pads; k++)
		{
			sprintf(buffer,"PRF_li_%i_lx_%i_ly_%i",k,j,i);
			h1 = (TH1D*)f->Get(buffer); //Loading the histogram with the name described in the previous line
			
			// The if statement is doubling the value of the second row of histograms. This simulates having a
			// Top and bottom row, but only for events that are centered about the y-axis! If the events are not
			// centered about the y-axis, then get rid of the command in the if, and keep one in the "else".
			
			if(k>perrow){maxima[a].push_back(2*h1->GetBinContent(h1->GetMaximumBin()));}
			else{maxima[a].push_back(h1->GetBinContent(h1->GetMaximumBin()));}
			
			delete(h1); //Clearing histograms
		}
	 sum=0; //resetting the sum
	 for (int i = 0; i < maxima[a].size(); ++i)
	  	{
	  		sum+=maxima[a][i];
	 	}
	 maxima[a].push_back(sum); //appending the sum to the vector, it will always be the last element
	 a++;
	}
}
// Insert whichever PRF generating script you'd like to see the PRF for below this comment:
// This script does nothing without adding a PRFType!

}
