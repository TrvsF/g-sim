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
	void		append_codons(std::string& genus, int ammount);
	inline void append_codons(std::string& genus, int ammount)
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
		// size of chromosome
		for (int i = 0; i < 2; i++)
		{ 
			switch (i)
			{
			case MIDPOINTS:
				append_codons(genus, 4);
				genus += STOP;
				break;
			case TRIEDGES:
				append_codons(genus, 24);
				genus += STOP;
				break;
			case AGRESSION:
				append_codons(genus, 2);
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
	
		// get midpoint of agent 
		Vector2D midpointvec = VEC2_ZERO;
		int codonsize = midpointcodons.size();
		int codonmidpoint = (int)round(codonsize / 2.0);
		for (int i = 0; i < codonsize; i++)
		{
			// split codon list into 2, lhs for x & rhs for y
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

		// get other points of agent
		Vector2D currentvec = VEC2_ZERO;
		std::vector<Vector2D> points;
		std::string currentcodons;

		int split = 2; // TODO : can be changed?
		bool x = true;
		const int N = split * 3;

		for (int i = 0; i < pointcodons.size(); i++)
		{
			// read current codon
			currentcodons += pointcodons[i];
			// every split change from x to y or vica versa
			if (i % split == 0 && i) // not on first pass
			{ 
				if (x)
				{
					char* end;
					int decimal = strtoull(currentcodons.c_str(), &end, 2);
					if (decimal & 1 << (N - 1)) decimal |= ~((1 << N) - 1);
				
					decimal = fmin(20, decimal); // silly hack : TODO fix random first x being very big!
					currentvec.x = decimal;
				}
				else
				{
					char* end;
					int decimal = strtoull(currentcodons.c_str(), &end, 2);
					if (decimal & 1 << (N - 1)) decimal |= ~((1 << N) - 1);

					currentvec.y = decimal;
					// push point to list
					points.push_back(currentvec + midpointvec);
				}
				currentcodons = "";
				x = !x;
			}
		}

		// build agent from generated points
		agent->GetGeometry()->Set({ agent->GetGeometry()->Pos() }, points);

		// TODO : traits

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