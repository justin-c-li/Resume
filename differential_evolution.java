import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintWriter;
import java.util.Random;


public class differential_evolution {
	static Random rand=new Random();
	static int Xa=0;
	static int Xb=0;
	static int Xc=0;
	static int n=30+1; //Problem's dimensionality +1 for the cost value
	static int NP=2*(n-1); //population size -1 to get rid of the cost value
	static double F=0.50; //mutation constant
	static double CR=0.90; //crossover constant
	/*If you want table fitness_values written to a .csv file it has to be set to 19 any higher and excel
	 * will mess up since it can't handle that much data.*/
	//static int MAXnfc=20*(n-1);//used this for graphing
	static int MAXnfc=1000*(n-1); //-1 to get rid of the extra 1 from adding cost value
	static int nfc=0;
	static int run=50;

	static double individ[][]=new double[NP][n+1]; //+1 for cost value since I'm using individ[NP][0] for cost val
	static double new_individ[][]=new double[NP][n+1]; //+1 for cost value
	static double Vi[]=new double[n+1]; 

	static boolean round=false; //turns rounding on and off but may cause rounding errors so default off
	static int digit=2; //sets the digit to round to but may cause rounding errors
	static int generation=1;
	/*select functions 1 to 5 based upon the pdf and anything else will default to the pdf DE example*/
	static int function=1;
	static double array[][]=new double[run][MAXnfc*NP];
	static int run_count=0;
	static int count=0;

	public static void initialize(){
		double temp_sum=0;
		for (int i=0; i<NP; i++){
			for (int j=1; j<n+1; j++){
				if(function==1){
					individ[i][j]=5.12-(10.24*rand.nextDouble()); //to make it go between -5.12 to 5.12
				}
				/*I coded it this way instead of using or statements with function 1 for better coding practise
				 * since changes could be made to function 3 and 5 boundaries easier this way*/
				else if(function==2){
					individ[i][j]=5.12-(10.24*rand.nextDouble()); //to make it go between -5.12 to 5.12
				}
				else if(function==3){
					individ[i][j]=65-(130*rand.nextDouble());
				}
				else if(function==4){
					individ[i][j]=2-(4*rand.nextDouble());
				}
				/*I coded it this way instead of using or statements with function 1 for better coding practise
				 * since changes could be made to function 3 and 5 boundaries easier this way*/
				else if(function==5){
					individ[i][j]=5.12-(10.24*rand.nextDouble());
				}
				else{ //default
					individ[i][j]=rand.nextDouble();
				}
				if(round){individ[i][j]=round(individ[i][j],digit);}
				individ[i][0]=0;
				
				/*Finds the cost values for the individual and checks if it's >=0 and if not it will
				 *  make a new one until it gets one that satisfies the minimium for the function*/
				for (int l=1; l<n+1; l++){
					if(function==1){ //1st De Jong
						individ[i][0]+=Math.pow(individ[i][l], 2);
					}
					else if(function==2){ //Axis Parrallel Hyper-Ellipsoid
						individ[i][0]+=l*Math.pow(individ[i][l], 2);
					}
					else if(function==3){ //Schwefel's Problem 1.2
						if(l==1){
							individ[i][0]+=individ[i][l];
						}
						else{
							temp_sum=0;
							for (int m=1; m<l; m++){
								temp_sum+=individ[i][m];
							}
						}
						individ[i][0]+=Math.pow(temp_sum,2);
					}
					else if(function==4){ //Rosenbrock's valley
						/*stops it at n before it can run the calculation therefore it's n-1 since
						 * it never got to calculate at n because of the break */
						if(l==n){
							break;
						}
						individ[i][0]+=100*Math.pow((individ[i][l+1]-Math.pow(individ[i][l],2)), 2)
								+Math.pow((1-individ[i][l]),2);
					}
					else if(function==5){ //Rastrigin's Function
						individ[i][0]+=Math.pow(individ[i][l],2)-10*Math.cos(2*Math.PI*individ[i][l]);
					}
					else{//default function where f(x)=sum of x
						individ[i][0]+=individ[i][l];
					}
				}
				if(function==5){
					individ[i][0]+=10*n;
				}
				if(individ[i][0]<0){ //makes it loop if the function gives a cost value thats less then 0 since 0 is min
					i--;
				}
				else if(round){individ[i][0]=round(individ[i][0],digit);}
				else{};
			}
		}
		//System.out.println("Initial Population");
		//display();
	}

	//rounds off number to the digits
	public static double round(double a, double digits){
		int temp=0;
		temp=(int)(a*Math.pow(10,digits));
		if(((a*Math.pow(10, digits))%1)>=0.5){
			temp++;
		}
		a=(double)(temp/Math.pow(10,digits));
		return a;
	}
	
	//gets the fitness value
	public static void cost_val(){
		Vi[0]=0;
		double temp=0;
		double temp2=0;
		double sum_temp=0;
		for (int i=1; i<n+1; i++){
			if(function==1){ //1st De Jong
				if(Vi[i]<-5.12){temp=-5.12;} //these restrict x in the bound
				else if(Vi[i]>5.12){temp=5.12;}
				else{temp=Vi[i];}
				Vi[0]+=Math.pow(temp, 2);
			}
			else if(function==2){ //Axis Parrallel Hyper-Ellipsoid
				if(Vi[i]<-5.12){temp=-5.12;}
				else if(Vi[i]>5.12){temp=5.12;}
				else{temp=Vi[i];}
				Vi[0]+=i*Math.pow(temp, 2);
			}
			else if(function==3){ //Schwefel's Problem 1.2
				if(i==1){
					if(Vi[i]<-65){Vi[0]+=-65;}
					else if(Vi[i]>65){Vi[0]+=65;}
					else{Vi[0]+=Vi[i];}
				}
				else{
					sum_temp=0;
					for (int m=1; m<i; m++){
						if(Vi[i]<-65){temp=-65;}
						else if(Vi[i]>65){temp=65;}
						else{temp=Vi[m];}
						sum_temp+=temp;
					}
				}
				Vi[0]=Math.pow(sum_temp,2);
			}
			else if(function==4){ //Rosenbrock's valley
				/*stops it at n before it can run the calculation therefore it's n-1 since
				 * it never got to calculate at n because of the break */
				if(i==n){
					break;
				}
				if(Vi[i]<-2){temp=-2;}
				else if(Vi[i]>2){temp=2;}
				else{temp=Vi[i];}
				if(Vi[i+1]<-2){temp2=-2;}
				else if(Vi[i+1]>2){temp2=2;}
				else{temp=Vi[i+1];}
				Vi[0]+=100*Math.pow((temp2-Math.pow(temp,2)), 2)
						+Math.pow((1-temp),2);
			}
			else if(function==5){ //Rastrigin's Function
				if(Vi[i]<-5.12){temp=-5.12;}
				else if(Vi[i]>5.12){temp=5.12;}
				else{temp=Vi[i];}
				Vi[0]+=Math.pow(temp,2)-10*Math.cos(2*Math.PI*temp);
			}
			else{//default function where f(x)=sum of x
				Vi[0]+=Vi[i];
			}
		}
		if(function==5){
			Vi[0]+=10*n;
		}
		if(round){Vi[0]=round(Vi[0],digit);}
	}

	//Subtracts vector Xb from Xc
	public static void difference_vector(){
		for (int i=1; i<n+1; i++){
			Vi[i]=individ[Xc][i]-individ[Xb][i];
			if(round){Vi[i]=round(Vi[i],digit);}
		}
	}
	
	//Multiplies hte vector by the mutation constant
	public static void weighted_difference_vector(){
		for (int i=0; i<n+1; i++){
			Vi[i]*=F;
			if(round){Vi[i]=round(Vi[i],digit);}
		}
	}

	//adds vector Xa with the weighted difference vector
	public static void noisy_vector(){
		for (int i=1; i<n+1; i++){
			Vi[i]+=individ[Xa][i];
			if(round){Vi[i]=round(Vi[i],digit);}
		}
	}

	//Applies crossover between the noisy vector and the selected vector at the start
	public static void trial_vector(int a){
		for (int i=1; i<n+1; i++){
			if(rand.nextDouble()<=CR){
				Vi[i]=individ[a][i];
				if(round){Vi[i]=round(Vi[i],digit);}
			}
		}
	}

	public static void next_generation(int a){
		cost_val();
		if(Vi[0]<0 && individ[a][0]>=0){
			for(int i=0; i<n+1; i++){
				new_individ[a][i]=individ[a][i];
				if(round){new_individ[a][i]=round(new_individ[a][i],digit);}
			}
		}
		else if(individ[a][0]<0 && Vi[0]>=0){
			for(int i=0; i<n+1; i++){
				new_individ[a][i]=Vi[i];
				if(round){new_individ[a][i]=round(new_individ[a][i],digit);}
			}
		}
		else if(Vi[0]<=individ[a][0] && Vi[0]>=0 && individ[a][0]>=0){
			for(int i=0; i<n+1; i++){
				new_individ[a][i]=Vi[i];
				if(round){new_individ[a][i]=round(new_individ[a][i],digit);}
			}
		}
		else if(individ[a][0]<=Vi[0] && Vi[0]>=0 && individ[a][0]>=0){
			for(int i=0; i<n+1; i++){
				new_individ[a][i]=individ[a][i];
				if(round){new_individ[a][i]=round(new_individ[a][i],digit);}
			}
		}
		else{
			//System.out.println("ERROR");
		}
		array[run_count][count]=new_individ[a][0];
		count++;
	}

	public static void choose(int i){
		do{
			Xa=rand.nextInt(NP);
		}while(Xa==i);
		do{
			Xb=rand.nextInt(NP);
		}while(Xb==i || Xb==Xa);
		do{
			Xc=rand.nextInt(NP);
		}while(Xc==i|| Xc==Xa || Xc==Xb);

	}
	//Note that my Individual vectors go horizontal not vertical like the example
	public static void display(){
		for (int i=0; i<NP; i++){
			System.out.print("Individ "+(i+1)+": |");
			for (int j=0; j<n+1; j++){
				System.out.print(individ[i][j]+"|");
			}
			System.out.println();
		}
	}

	public static void replace_population(){
		for (int i=0; i<NP; i++){
			for (int j=0; j<n+1; j++){
				individ[i][j]=new_individ[i][j];
				if(round){new_individ[i][j]=round(new_individ[i][j],2);}
			}
		}
	}

	public static void differentialEvolution(){
		while(run_count<50){
			nfc=0;
			count=0;
			initialize();
			while(nfc<MAXnfc){
				nfc++;
				for (int i=0; i<NP; i++){
					choose(i);
					difference_vector();
					weighted_difference_vector();
					noisy_vector();
					trial_vector(i);
					next_generation(i);
				}
				replace_population();
				//System.out.println("Generation:"+generation);
				//generation++;
				//display();
			}
			run_count++;
		}
	}

	public static void main(String[] args) throws FileNotFoundException{
		double[] average=new double[run];
		double total_average=0;
		double[] sum=new double[run];
		double[] standard_deviation=new double[run];
		double[] avg_fitness=new double[MAXnfc*NP];
		double avg_dev=0;
		function=1;
		for(int z=0; z<5; z++){
			PrintWriter out = new PrintWriter(new FileOutputStream("DE_result"+function+".csv"));
			run_count=0;
			differentialEvolution();
			for(int i=0; i<run; i++){
				average[i]=0;
				sum[i]=0;
				for (int j=0; j<(MAXnfc*NP); j++){
					average[i]+=array[i][j];
				}
				average[i]/=MAXnfc*NP;
				for (int k=0; k<MAXnfc*NP; k++){
					sum[i]+=Math.pow(array[i][k]-average[i],2);
				}
				standard_deviation[i]=Math.sqrt(sum[i]/(MAXnfc-1));
			}
			avg_dev=0;
			total_average=0;
			for(int i=0; i<run; i++){
				avg_dev+=standard_deviation[i];
				total_average+=average[i];
			}
			avg_dev/=run;
			total_average/=run;
			for (int a=0; a<(MAXnfc*NP);a++){
				avg_fitness[a]=0;
				for (int b=0; b<run; b++){
					avg_fitness[a]+=array[b][a];					
				}
				avg_fitness[a]/=run;
				out.println(avg_fitness[a]);
			}
			System.out.println("average f"+function+":	"+total_average);
			System.out.println("standard deviation f"+function+":	"+avg_dev);
			out.close();
			function++;
		}
	}
}
