#ifndef GOD_H_
#define GOD_H_

#include "../world/entities/agent.h"
#include "../world/game-object.h"

#include <vector>
#include <string>
#include "../src/util/maths.h"

namespace god
{
	enum Genes
	{
		MIDPOINTS = 0,
		TRIEDGES  = 1
	};

	const std::string STOP = "000";

	// i dont think these should be inlines??

	void		append_codon(std::string& genus);
	inline void append_codon(std::string& genus)
	{
		// generate random codon
		int one = maths::GetRandomInt(0, 1);
		int two = maths::GetRandomInt(0, 1);
		int thr = maths::GetRandomInt(0, 1);
		// if is stop regen 
		bool stopcheck = !one && !two && !thr;
		if (stopcheck)
		{
			one = 1;
			two = maths::GetRandomInt(0, 1);
			thr = maths::GetRandomInt(0, 1);
		}
		// add to genus
		genus += char(one + 48);
		genus += char(two + 48);
		genus += char(thr + 48);
	}

	std::vector<std::string>		GetGenes(std::string genus);
	inline std::vector<std::string> GetGenes(std::string genus)
	{
		// reads each codon from gene
		std::vector<std::string> genes;
		std::string gbuilder;

		int splits = std::floor(genus.size() / 3);
		for (int i = 0; i < splits; i++)
		{
			int gindex = i * 3;
			int left  = genus[gindex]	  - 48;
			int mid   = genus[gindex + 1] - 48;
			int right = genus[gindex + 2] - 48;

			bool isstop = !left && !mid && !right;
			if (isstop) 
			{
				// add gene & reset gene builder
				genes.push_back(gbuilder);
				gbuilder = "";
				continue;
			}

			gbuilder += genus[gindex];
			gbuilder += genus[gindex + 1];
			gbuilder += genus[gindex + 2];
		}
		return genes;
	}

	std::vector<std::string>		GetCodons(std::string gene);
	inline std::vector<std::string> GetCodons(std::string gene)
	{
		// for each codon from gene
		std::vector<std::string> codons;

		int splits = std::floor(gene.size() / 3);
		for (int i = 0; i < splits; i++)
		{
			int cindex = i * 3;
			int left  = gene[cindex]	 - 48;
			int mid   = gene[cindex + 1] - 48;
			int right = gene[cindex + 2] - 48;

			bool isstop = !left && !mid && !right;
			if (isstop) 
			{ 
				return codons; 
			}

			std::string codon;
			codon += gene[cindex];
			codon += gene[cindex + 1];
			codon += gene[cindex + 2];
			codons.push_back(codon);
		}
		return codons;
	}

	inline void GenerateGenus(std::string& genus)
	{
		int CODONS;
		int GENESIZE;
		// size of chromosome
		for (int i = 0; i < 2; i++)
		{ 
			switch (i)
			{
			case MIDPOINTS:
				CODONS   = 4; 
				GENESIZE = 1; // points
				for (int t = 0; t < CODONS * GENESIZE; t++)
				{
					append_codon(genus);
				}
				genus += STOP;
				break;
			case TRIEDGES:
				CODONS   = 4;
				GENESIZE = 6; // points
				for (int t = 0; t < CODONS * GENESIZE; t++)
				{
					append_codon(genus);
				}
				genus += STOP;
				break;
			}
		}
	}

	inline void BuildAgent(object::GameObject* object, object::Agent* agent)
	{
		// randomly generate genus
		std::string genus;
		GenerateGenus(genus);

		// get codons for each gene
		std::vector<std::string> genes			= GetGenes(genus);
		std::vector<std::string> midpointcodons = GetCodons(genes[0]); // unused
		std::vector<std::string> pointcodons	= GetCodons(genes[1]);
		
		// extract points
		std::vector<Vector2D> points;
		Vector2D	cvec;
		std::string cstr;

		bool right = true;
		for (int c = 0; c < pointcodons.size(); c++)
		{
			if (c % 2 == 0) // codons/2
			{ 
				char* end;
				float f = strtoull(cstr.c_str(), &end, 2);
				right ? cvec.y = f : cvec.x = f;
				right = !right;
				cstr = "";
			}

			if (c % 4 == 0 && c) 
			{ 
				points.push_back(cvec);
				cvec = VEC2_ZERO;
			}

			cstr += pointcodons[c];
		}

		// build agent
		agent->GetGeometry()->Set({ agent->GetGeometry()->Pos() }, points);
		agent->SetGenome(genus);
		// agent->SetTraits({ "name", {255, 255, 255}, 5.0f, 3.0f, 2000, 2000, 100, 5 });
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