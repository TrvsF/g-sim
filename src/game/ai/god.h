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
		AGRESSION = 2,
		R		  = 3,
		G		  = 4,
		B		  = 5,
		SEX		  = 6,
	};

	// STOP codon
	const std::string STOP = "000";

	// (i dont think these should be inlines??)

	// get list of genes from genus
	std::vector<std::string>		get_genes(std::string genus);
	inline std::vector<std::string> get_genes(std::string genus)
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
	std::vector<std::string>		get_codons(std::string gene);
	inline std::vector<std::string> get_codons(std::string gene)
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

	void		generate_child_genome(std::string parent1, std::string parent2, std::string& child);
	inline void generate_child_genome(std::string parent1, std::string parent2, std::string& child)
	{
		bool parentflag = false;
		std::vector<std::string> genes1 = get_genes(parent1);
		std::vector<std::string> genes2 = get_genes(parent2);

		for (int i = 0; i < genes1.size(); i++)
		{
			if (parentflag)
			{
				child += genes1[i];
			}
			else
			{
				child += genes2[i];
			}
			child += STOP;

			if (maths::GetRandomInt(0, 3) == 0)
			{
				parentflag = !parentflag;
			}
		}
	}

	// generate random genus
	inline void GenerateGenus(std::string& genus)
	{
		// size of chromosome
		for (int i = 0; i < 7; i++)
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
			case R:
				append_codons(genus, 8);
				genus += STOP;
				break;
			case G:
				append_codons(genus, 8);
				genus += STOP;
				break;
			case B:
				append_codons(genus, 8);
				genus += STOP;
				break;
			case SEX:
				append_codons(genus, 1);
				genus += STOP;
				break;
			}
		}
	}

	void BuildAgent(object::Agent* agent, std::string genus);
	inline void BuildAgent(object::Agent* agent, std::string genus)
	{
		// get codons for each gene
		std::vector<std::string> genes			 = get_genes(genus);
		// TODO : relook @ this
		std::vector<std::string> midpointcodons  = get_codons(genes[0]);
		std::vector<std::string> pointcodons	 = get_codons(genes[1]);
		std::vector<std::string> agressioncodons = get_codons(genes[2]);
		std::vector<std::string> rcodons		 = get_codons(genes[3]);
		std::vector<std::string> gcodons		 = get_codons(genes[4]);
		std::vector<std::string> bcodons		 = get_codons(genes[5]);
		std::vector<std::string> sexcodons		 = get_codons(genes[6]);

		/*
		 -------------------------------
				AGENT MIDPOINT
		 -------------------------------
		*/
		// get midpoint of agent 
		Vector2D midpointvec = VEC2_ZERO;
		int codonsize		 = midpointcodons.size();
		int codonmidpoint    = (int)round(codonsize / 2.0);
		for (int i = 0; i < codonsize; i++)
		{
			// split codon list into 2, lhs for x & rhs for y
			if (i < codonmidpoint)
			{
				int decimal = maths::StringToDecimal(midpointcodons[i], false);
				midpointvec.x += decimal;
			}
			else
			{
				int decimal = maths::StringToDecimal(midpointcodons[i], false);
				midpointvec.y += decimal;
			}
		}

		/*
		 -------------------------------
				AGENT OUTERPOINTS
		 -------------------------------
		*/
		// get other points of agent
		std::vector<Vector2D> points;
		std::string currentcodons;
		Vector2D currentvec = VEC2_ZERO;
		int split = 2;		 // TODO : can be changed?
		bool x    = true;

		for (int i = 0; i < pointcodons.size(); i++)
		{
			// read current codon
			currentcodons += pointcodons[i];
			// every split change from x to y or vica versa
			if (i % split == 0 && i) // not on first pass
			{ 
				if (x)
				{
					int decimal = maths::StringToDecimal(currentcodons, true);
					currentvec.x = decimal % 24;
				}
				else
				{
					int decimal = maths::StringToDecimal(currentcodons, true);
					currentvec.y = decimal % 24;

					// push point to list
					points.push_back(currentvec + midpointvec);
				}
				currentcodons = "";
				x = !x;
			}
		}

		/*
		 -------------------------------
				AGENT AGRESSION
		 -------------------------------
		*/
		int agression;
		std::string codons;
		for (const auto& codon : agressioncodons)
		{
			codons += codon;
		}
		int decimal = maths::StringToDecimal(codons, false);
		agression = decimal % 11;

		/*
		 -------------------------------
				AGENT COLOUR
		 -------------------------------
		*/
		int colourcodonsize = rcodons.size(); // should be 8!

		std::string rgene;
		for (int i = 0; i < colourcodonsize; i++)
		{
			const auto& codons = rcodons[i];
			int totalbits	   = 0;

			for (const auto& codon : codons)
			{
				if (codon == '1')
				{
					totalbits++;
				}
			}
			rgene += totalbits > 1 ? '1' : '0';
		}
		std::string bgene;
		for (int i = 0; i < colourcodonsize; i++)
		{
			const auto& codons = bcodons[i];
			int totalbits = 0;

			for (const auto& codon : codons)
			{
				if (codon == '1')
				{
					totalbits++;
				}
			}
			bgene += totalbits > 1 ? '1' : '0';
		}
		std::string ggene;
		for (int i = 0; i < colourcodonsize; i++)
		{
			const auto& codons = gcodons[i];
			int totalbits = 0;

			for (const auto& codon : codons)
			{
				if (codon == '1')
				{
					totalbits++;
				}
			}
			ggene += totalbits > 1 ? '1' : '0';
		}

		int r = maths::StringToDecimal(rgene, false);
		int g = maths::StringToDecimal(ggene, false);
		int b = maths::StringToDecimal(bgene, false);

		/*
		 -------------------------------
				AGENT SEX
		 -------------------------------
		*/
		std::string bittle = sexcodons[0];
		int sex = maths::StringToDecimal(bittle, false) % 2;

		// build agent from generated points
		agent->GetGeometry()->Set({ agent->GetGeometry()->Pos() }, points, &agent->GetAABB());
		float area		 = agent->GetArea();
		float spikeyness = agent->GetSpikyness();
		
		SDL_Color agentcolour = { r, g, b };
		float walkspeed		= (spikeyness / (area * 0.1f)) + 1.0f;
		float maxturnspeed  = maths::GetRandomFloat(0.5f, 5.0f); // TODO : not random 
		int maxhealth		= area;
		int maxstamina		= area * 10;
		int maxdamage		= spikeyness;

		agent->SetTraits({ "", agentcolour, sex, walkspeed, maxturnspeed, maxhealth, maxstamina, maxdamage, agression });
		agent->SetGenome(genus);
	}

	inline void BuildAgent(object::Agent* agent)
	{
		// randomly generate genus
		std::string genus;
		GenerateGenus(genus);

		BuildAgent(agent, genus);
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