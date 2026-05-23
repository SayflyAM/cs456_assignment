#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

int calculateFitness(const vector<int> &board)
{
	int fitness = 0;
	int n = board.size();

	// this for outer loop for queen compersions
	for (int i = 0; i < n; i++)
	{
		// compersions after queen one
		for (int j = i + 1; j < n; j++)
		{
			if (abs(board[i] - board[j]) != abs(i - j) && board[i] != board[j])
			{
				fitness++;
			}
		}
	}
	return fitness;
}

int selection(const vector<vector<int>> &poplution)
{
	int total_fitness = 0;
	int n = poplution.size();
	for (int i = 0; i < n; i++)
	{

		total_fitness += calculateFitness(poplution[i]);
	}

	int random_num = rand() % total_fitness;
	int running_sum = 0;

	for (int i = 0; i < n; i++)
	{
		running_sum += calculateFitness(poplution[i]);

		if (running_sum >= random_num)
		{
			return i;
		}
	}
	return 0;
}

vector<int> crossover(const vector<int> &parent1, const vector<int> &parent2)
{
	int n = parent1.size();

	vector<int> child(n);

	int c = rand() % n;

	for (int i = 0; i < n; i++)
	{

		if (i < c)
		{
			child[i] = parent1[i];
		}
		else
		{

			child[i] = parent2[i];
		}
	}
	return child;
}

void mutate(vector<int> &child)
{
	int n = child.size();

	int column = rand() % n;
	int row = rand() % n;

	child[column] = row;
}

vector<int> intial_pop()
{
	vector<int> pop(8);
	for (int i = 0; i < 8; i++)
	{
		pop[i] = rand() % 8;
	}

	return pop;
}
int tournamentSelection(const vector<vector<int>> &population, int k)
{
	int n = population.size();

	int best_idx = rand() % n;

	for (int i = 0; i < k - 1; i++)
	{
		int ind_idx = rand() % n;
		if (calculateFitness(population[ind_idx]) > calculateFitness(population[best_idx]))
		{
			best_idx = ind_idx;
		}
	}
	return best_idx;
}

vector<int> genticAlgorithm(int run_number, ofstream &outFile, string selectionMethod)
{
	int pop_size = 100;

	vector<vector<int>> population;

	for (int i = 0; i < pop_size; i++)
	{
		population.push_back(intial_pop());
	}
	int generation = 0;

	while (true)
	{
		generation++;
		int best_fitness = 0;

		for (int i = 0; i < pop_size; i++)
		{
			int current_fitness = calculateFitness(population[i]);
			if (current_fitness == 28)
			{
				cout << "generation:" << generation << endl;
				outFile << "Run " << run_number << " - Generation: " << generation << endl;
				return population[i];
			}
			if (current_fitness > best_fitness)
			{
				best_fitness = current_fitness;
			}
		}
		outFile << "Generation " << generation << " - Best Fitness: " << best_fitness << endl;

		vector<vector<int>> new_population;

		for (int i = 0; i < pop_size; i++)
		{
			// int parent1_idx = selection(population);
			// int parent2_idx = selection(population);
			// int parent1_idx = tournamentSelection(population, 5);
			// int parent2_idx = tournamentSelection(population, 5);
			int parent1_idx, parent2_idx;
			if (selectionMethod == "Roulette")
			{
				parent1_idx = selection(population);
				parent2_idx = selection(population);
			}
			else
			{
				parent1_idx = tournamentSelection(population, 5);
				parent2_idx = tournamentSelection(population, 5);
			}
			while (parent1_idx == parent2_idx)
			{
				parent2_idx = (selectionMethod == "Roulette") ? selection(population) : tournamentSelection(population, 5);
			}

			vector<int> child;
			child = crossover(population[parent1_idx], population[parent2_idx]);

			mutate(child);
			new_population.push_back(child);
		}

		population = new_population;
	}
}

void printBoard(const vector<int> &board)
{

	int n = board.size();

	for (int r = 0; r < n; r++)
	{

		for (int c = 0; c < n; c++)
		{
			if (board[c] == r)
			{
				cout << "Q ";
			}
			else
			{
				cout << ". ";
			}
		}
		cout << endl;
	}
	cout << "-----------------" << endl;
}

int main()
{
	srand(time(0));
	ofstream outFile("results.txt");

	for (int i = 0; i < 5; i++)
	{

		vector<int> solution = genticAlgorithm(i, outFile, "Tournament");
		printBoard(solution);
	}
	outFile << "\n\n"
			<< endl;
	for (int i = 0; i < 5; i++)
	{

		vector<int> solution = genticAlgorithm(i, outFile, "Roulette");
		printBoard(solution);
	}

	outFile.close();

	return 0;
}