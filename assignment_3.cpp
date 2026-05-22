

int calculateFitness(const vector<int>& board) {
	int fitness = 0;
	int n= board.size();

    // this for outer loop for queen compersions
	for (int i=0 ; i<n; i++){
		// compersions after queen one
		for (int j= i+1; j<n; j++) {
			if(abs(board[i] - board[j]) != abs(i-j) && board[i] != board[j]) {
				fitness++;
			}
		}
	}
    return fitness;


}

int selection(const vector<vector<int>>& poplution) {
	int total_fitness =0;
    int n = poplution.size();
	for (int i=0;i<n;i++){
		
		total_fitness += calculateFitness(poplution[i]);

	}
    
	int random_num = rand() % total_fitness;
	int running_sum =0;

	for (int i = 0; i<n ;i++) {
		running_sum += calculateFitness(poplution[i]);

		if (running_sum >= random_num){
			return i;
		}

	}
    return 0;

}




vector<int> crossover(const vector<int>& parent1, const vector<int>& parent2) 
{
	int n =  parent1.size();

	vector<int> child(n);
     
	int c =  rand() % n;

	for (int i=0; i < n; i++) {
	
		if(i < c){
			child[i] = parent1[i];
		}else{

			child[i] = parent2[i];
		}
		}
	return child;



}



void mutate(vector<int>& child) {
	int n =  child.size();

	int column = rand() % n;
	int row =  rand() % n;

	child[column] = row;
}


vector<int> intial_pop(){
     vector<int> pop(8);
	for(int i=0 ; i < 8 ; i++ ){
		pop[i] = rand() % 8 ;
	}

	return pop;

}
