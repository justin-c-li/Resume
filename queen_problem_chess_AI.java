import java.util.Random;

/*
 * Queen solving Genetic Algorithm
 * author: Justin Li
 * this problem takes a while to run and solve all the solutions
 * */

public class queen_problem_chess_AI {
	static int chromosome[][]=new int[8][3];
	static int solution_chromosomes[][][]=new int[92][8][3];
	static int chess_board[][]=new int[8][8];
	static double fitness[]=new double[8];
	static double pmutation=0.20; //I like mutation so I used 0.2 for mutation
	static double pcrossover=0.03; //I don't like crossover so I used 0.05 for it
	static Random rand=new Random();
	static double total_fitness=0;

	static void GeneticAlgorithm(){
		int select;
		initialize();
		do{
			fitness_function();
			select=selection();
			crossover(select);
			mutation(select);
		}while(total_fitness>0.4);
	}

	static void initialize(){
		int temp;
		for (int i=0; i<8; i++){
			for (int j=0; j<8; j++){
				chess_board[i][j]=0;
			}
			temp=rand.nextInt(8);
			chess_board[i][temp]=1;
			binary_conversion(i,temp);
		}
	}

	public static void display(){
		for (int i=7; i>=0; i--){
			System.out.print("row:"+i+"	");
			System.out.print("|");
			for (int j=0; j<8; j++){
				if(chess_board[i][j]==0){
					System.out.print(" |");
				}
				else{
					System.out.print("Q|");
				}

			}

			System.out.println();
		}
	}
	
	public static void solutions(){
		for (int i=0; i<92; i++){
			System.out.print(i+1+":");
			for (int j=0; j<8; j++){
				for (int k=0; k<3; k++){
					System.out.print(solution_chromosomes[i][j][k]);
				}
			}
			System.out.println();
		}
	}

	static void clear(int n){
		for (int i=0; i<8; i++){
			chess_board[n][i]=0;
		}
	}

	static int decimal_conversion(int n){
		int decimal = 0;
		for (int i=0; i<3; i++){
			if(chromosome[n][i]==1){
				decimal+=Math.pow(2,i);
			}
		}
		return decimal;
	}

	static void binary_conversion(int n, int num){
		int decimal=num;
		clear(n);
		chess_board[n][num]=1;
		for (int i=2; i>=0; i--){
			if(decimal-Math.pow(2,i)>=0){
				chromosome[n][i]=1;
				decimal-=Math.pow(2,i);
			}
			else{
				chromosome[n][i]=0;
			}
		}
	}

	static void mutation(int n){
		int temp;
		if(rand.nextDouble()<=pcrossover){
			temp=rand.nextInt(3);
			if(chromosome[n][temp]==0){
				chromosome[n][rand.nextInt(3)]=1;
			}
			else if(chromosome[n][temp]==1){
				chromosome[n][rand.nextInt(3)]=0;
			}
			else{
				System.out.println("Error with chromosome detected");
			}
		}
		binary_conversion(n,decimal_conversion(n));
	}

	static void crossover(int n){
		int temp;
		int n2 = 0;
		int z;
		if(rand.nextDouble()<=pcrossover){
			do{
				n2=rand.nextInt(8);
			}while(n2==n);
			z=rand.nextInt(4);
			if(z>2){
			}
			else{
				for(int i=z; i<3; i++){
					temp=chromosome[n][i];
					chromosome[n][i]=chromosome[n2][i];
					chromosome[n2][i]=temp;
				}
			}
		}
		binary_conversion(n,decimal_conversion(n));
		binary_conversion(n2,decimal_conversion(n2));
	}

	static void fitness_function(){
		int selected=0;
		int x=0;

		for (int i=0; i<8; i++){
			fitness[i]=0.05;
			//setting selected to the y position
			selected=decimal_conversion(i);
			//vertical check

			for (int j=0; j<8; j++){
				if(j==i){
					j++;
				}
				if(j>7){
					break;
				}
				if(selected==decimal_conversion(j)){
					fitness[i]++;
				}
			}

			//checks diagonally for conflict from top left to bottom right
			x=selected+i;			
			for (int k=0; k<8; k++){
				//makes sure it starts within the boards of the chessboard
				while(x>7 || k==i){
					x--;
					k++;
				}
				if(k>7 || x<0){
					break;
				}
				if(chess_board[k][x]==1 && k!=i){
					fitness[i]++;
				}
				x--;
				if(x<0){
					break;
				}
			}

			//checks diagonally from bottom left to top right
			x=selected-i;
			for (int l=0; l<8; l++){
				while(x<0 || l==i){
					x++;
					l++;
				}
				if(l>7 || x>7){
					break;
				}
				if(chess_board[l][x]==1 && l!=i){
					fitness[i]++;
				}
				x++;
				if(x>7){
					break;
				}
			}
			total_fitness=0;
			for (int f=0; f<8; f++){
				total_fitness+=fitness[f];
			}
		}
	}

	static int selection(){
		double select;
		double fitness_calc = 0;
		fitness_function();
		select=rand.nextDouble();
		fitness_calc=fitness[0]/total_fitness;
		if(select<=fitness_calc){
			return 0;
		}
		for (int j=1; j<7; j++){
			if((select>fitness_calc) && (select<=(fitness_calc+fitness[j]/total_fitness))){
				return j;
			}
			fitness_calc+=fitness[j]/total_fitness;
		}
		if((select>fitness_calc) && (select<=1)){
			return 7;
		}
		return -1;
	}

	public static void main(String[] args){
		int solution=0;
		while(solution<92){
			GeneticAlgorithm();
			boolean pass=true;
			if(solution==0){}//To make sure it does run for sure when solution empty
			else if(solution>0){
				for(int a=0; a<solution; a++){
					int same=0;
					for (int b=0; b<8; b++){
						for (int c=0; c<3; c++){
							if(solution_chromosomes[a][b][c]==chromosome[b][c]){
								same++;
							}
						}
					}
					if(same==24){
						pass=false;
						break;
					}
				}
			}
			else{
				System.out.println("ERROR");
			}
			if(pass){
				for (int i=0; i<8; i++){
					for (int j=0; j<3; j++){
						solution_chromosomes[solution][i][j]=chromosome[i][j];
					}
				}
				solution++;
			}
		}
		solutions();
		display(); //example of my chessboard for the last child chromosome made
	}
}
