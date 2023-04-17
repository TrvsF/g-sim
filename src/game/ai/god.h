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
		TRIEDGES  = 1,
		AGRESSION = 2
	};

	// STOP codon
	const std::string STOP = "000";

	// (i dont think these should be inlines??)

	// append random non-stop codon to genus
	void		append_codon(std::string& genus, int ammount);
	inline void append_codon(std::string& genus, int ammount)
	{
		for (int i = 0; i < ammount; i++)
		{
			// generate random codon
			int one = maths::GetRandomInt(0, 1);
			int two = maths::GetRandomInt(0, 1);
			int thr = maths::GetRandomInt(0, 1);
			// if is stop regen with first bit being a 1
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
	}

	// get list of genes from genus
	std::vector<std::string>		GetGenes(std::string genus);
	inline std::vector<std::string> GetGenes(std::string genus)
	{
		// setup vars
		std::vector<std::string> genes;
		std::string gbuilder;
		// split genus into codon parts to iterate through
		int splits = std::floor(genus.size() / 3);
		for (int i = 0; i < splits; i++)
		{
			// get codon
			int gindex = i * 3;
			int left  = genus[gindex]	  - 48;
			int mid   = genus[gindex + 1] - 48;
			int right = genus[gindex + 2] - 48;
			// if is stop codon
			bool isstop = !left && !mid && !right;
			if (isstop) 
			{
				// add gene & reset gene builder
				genes.push_back(gbuilder);
				gbuilder = "";
				continue;
			}
			// append codon to genebuilder
			gbuilder += genus[gindex];
			gbuilder += genus[gindex + 1];
			gbuilder += genus[gindex + 2];
		}
		return genes;
	}

	// get list of codons from gene (NOT including stop codons)
	std::vector<std::string>		GetCodons(std::string gene);
	inline std::vector<std::string> GetCodons(std::string gene)
	{
		// setup vars
		std::vector<std::string> codons;
		// split genus into codon parts to iterate through
		int splits = std::floor(gene.size() / 3);
		for (int i = 0; i < splits; i++)
		{
			// get codon
			int cindex = i * 3;
			int left  = gene[cindex]	 - 48;
			int mid   = gene[cindex + 1] - 48;
			int right = gene[cindex + 2] - 48;
			// if is stop codon return list
			bool isstop = !left && !mid && !right;
			if (isstop) 
			{ 
				return codons; 
			}
			// read codon & push
			std::string codon;
			codon += gene[cindex];
			codon += gene[cindex + 1];
			codon += gene[cindex + 2];
			codons.push_back(codon);
		}
		return codons;
	}

	// generate random genus
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
				CODONS   = 4; // coordinate base 2 size / 2
				GENESIZE = 1; // 1 set of points
				append_codon(genus, CODONS * GENESIZE);
				genus += STOP;
				break;
			case TRIEDGES:
				CODONS   = 8; // coordinate size / 2
				GENESIZE = 4; // 4 set of points
				append_codon(genus, CODONS * GENESIZE);
				genus += STOP;
				break;
			case AGRESSION:
				CODONS   = 4;
				GENESIZE = 1; // points
				append_codon(genus, CODONS * GENESIZE);
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
	
		// midpoint 
		Vector2D midpointvec = VEC2_ZERO;
		int codonsize = midpointcodons.size();
		int codonmidpoint = (int)round(codonsize / 2.0);
		for (int i = 0; i < codonsize; i++)
		{
			if (i < codonmidpoint)
			{
				char* end;
				int decimal = strtoull(midpointcodons[i].c_str(), &end, 2);
				midpointvec.x += decimal;
			}
			else
			{
				char* end;
				int decimal = strtoull(midpointcodons[i].c_str(), &end, 2);
				midpointvec.y += decimal;
			}
		}

		// !!!WANT TO READ EVERY 4 CODONS!!!
		// POINTS
		std::vector<Vector2D> points;
		int split = 4; // TODO : can be changed?
		int ammount = floor(pointcodons.size() / split);
		Vector2D currentvec = VEC2_ZERO;

		bool x = true;
		for (int i = 0; i < pointcodons.size(); i++)
		{
			// read current codon
			char* end;
			int decimal = strtoull(pointcodons[i].c_str(), &end, 2);
			if (decimal & 1 << 11) decimal |= ~0xfff;

			if (i % split/2 == 0 && i) // not on first pass
			{ 
				if (x)
				{

				}
				else
				{

				}
				x = !x;
			}
		}

		
		std::string cstr;
		Vector2D	cvec;

		bool right = true;
		for (int c = 0; c < pointcodons.size(); c++)
		{
			// reads 
			if (c % 2 == 0) // codons/2
			{ 
				char* end;
				int decimal = strtoull(cstr.c_str(), &end, 2);
				right ? cvec.y = (float)decimal : cvec.x = (float)decimal;
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