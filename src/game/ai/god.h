#ifndef GOD_H_
#define GOD_H_

#include "../world/entities/agent.h"
#include "../world/game-object.h"

#include <string>
#include "../src/util/maths.h"

namespace ai
{
	enum GenomeSections
	{
		MIDPOINTS = 0,
		TRIEDGES  = 1
	};

	const std::string STOP = "000";

	void get_newgene(std::string& genus);
	inline void get_newgene(std::string& genus)
	{
		int one = maths::GetRandomInt(0, 1);
		int two = maths::GetRandomInt(0, 1);
		int thr = maths::GetRandomInt(0, 1);
		// if is early stop regen 
		bool stopcheck = !one && !two && !thr;
		if (stopcheck)
		{
			one = 1;
			two = maths::GetRandomInt(0, 1);
			thr = maths::GetRandomInt(0, 1);
		}

		char c_one = char(one + 48);
		char c_two = char(two + 48);
		char c_thr = char(thr + 48);

		genus += c_one;
		genus += c_two;
		genus += c_thr;
	}

	inline void GenerateGenus(std::string& genus)
	{
		int GENES;
		int GENESIZE;
		// genomes are sperated by 
		for (int i = 0; i < 2; i++)
		{ 
			switch (i)
			{
			case MIDPOINTS:
				GENES	 = 2; 
				GENESIZE = 4; 
				for (int t = 0; t < GENES * GENESIZE; t++)
				{
					get_newgene(genus);
				}
				genus += STOP;
				break;
			case TRIEDGES:
				GENES = 6;
				GENESIZE = 4;
				for (int t = 0; t < GENES * GENESIZE; t++)
				{
					get_newgene(genus);
				}
				genus += STOP;
				break;
			}
		}
	}

	inline void ReadGenus(std::string genus)
	{
		int splits = std::floor(genus.size() / 3) - 1; // skips last stop
		for (int i = 0; i < splits; i++)
		{
			int geneindex = i * 3;
			const char left  = genus[geneindex];
			const char mid   = genus[geneindex + 1];
			const char right = genus[geneindex + 2];

			bool isstop = !left && !mid && !right;
			if (isstop) {  }
		}
	}
	
	inline void PrintGenus(std::string genus)
	{
		// get char array of genus
		bool nexttrait = false;
		const char* dnabit;
		for (dnabit = genus.c_str(); *dnabit != '\0'; dnabit++)
		{
			if (nexttrait) {}
			const char dna = dnabit[0];
			std::cout << dna;
		}
	}
}
#endif