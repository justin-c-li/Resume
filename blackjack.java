import java.util.Scanner;

public class blackjack {
	static double[] card=new double[52];

	public static void initialize(){
		for (int i=0; i<52; i++){	
			card[i]=i%13+0.25*(i/13);
		}
		shuffle(52);
	}

	public static void shuffle(int top){
		double temp;
		int point;

		for(int j=0; j<40; j++){
			for(int i=0; i<top; i++){
				point=(int) (Math.random()*top);
				temp=card[point];
				card[point]=card[i];
				card[i]=temp;
			}
		}
		System.out.println("#####Deck has been shuffled#####");
	}

	public static int card(double card){
		int card_worth = 0;
		if((int)card==0){
			System.out.print("Ace");
			card_worth=1;
		}
		else if((int)card==1){
			System.out.print("2");
			card_worth=2;
		}
		else if((int)card==2){
			System.out.print("3");
			card_worth=3;
		}
		else if((int)card==3){
			System.out.print("4");
			card_worth=4;
		}
		else if((int)card==4){
			System.out.print("5");
			card_worth=5;
		}
		else if((int)card==5){
			System.out.print("6");
			card_worth=6;
		}
		else if((int)card==6){
			System.out.print("7");		
			card_worth=7;
		}
		else if((int)card==7){
			System.out.print("8");
			card_worth=8;
		}
		else if((int)card==8){
			System.out.print("9");
			card_worth=9;
		}
		else if((int)card==9){
			System.out.print("10");
			card_worth=10;
		}
		else if((int)card==10){
			System.out.print("Jack");
			card_worth=10;
		}
		else if((int)card==11){
			System.out.print("Queen");
			card_worth=10;
		}
		else if((int)card==12){
			System.out.print("King");
			card_worth=10;
		}
		else{
			System.out.print("Error at: "+card+", ");
		}

		if(card%1==0.0){
			System.out.println(" Hearts");
		}
		else if(card%1==0.25){
			System.out.println(" Diamonds");
		}
		else if(card%1==0.5){
			System.out.println(" Spades");
		}
		else if(card%1==0.75){
			System.out.println(" Clubs");
		}
		else{
			System.out.println("Error at: "+card);
		}
		return card_worth;
	}
	
	public static void main(String[] args){
		int money=100, card_point=0, card_start=0;;
		int playerhand, dealerhand, bet = 0, temp;
		boolean player_ace, dealer_ace, invalid;
		String  input;
		Scanner scan=new Scanner(System.in);
		
		initialize();
		while(money>0){
			playerhand=0;
			dealerhand=0;
			player_ace=false;
			dealer_ace=false;
			invalid=false;
			card_start=card_point;
			do{
				System.out.println("Input the amount you want to bet");
				System.out.println("Your money: $"+money);
				while(!scan.hasNextInt()){
			        System.out.println("Invalid Input enter numbers only");
			        scan.next();//Go to next
			    }
			    bet = scan.nextInt();
			    
				if(bet>money){
					System.out.println("You cannot bet more money than you have");
				}
				else if(bet<1){
					System.out.println("You must bet at least $1");
				}
			}while(bet>money || bet<1);
			System.out.println("You bet:" +bet);
			System.out.println("card point: "+card_point);
			for(int i=0;i<2;i++){
				System.out.print("Dealer Card: ");
				temp=card(card[card_point]);
				if(temp==1 && dealerhand<11){
					temp+=10;
					dealer_ace=true;
				}
				dealerhand+=temp;
				card_point++;
				if(card_point>51){
					shuffle(card_start);
					card_point=0;
				}
				
				System.out.print("Player Card: ");
				temp=card(card[card_point]);
				if(temp==1 && playerhand<11){
					temp+=10;
					player_ace=true;
				}
				playerhand+=temp;
				card_point++;
				if(card_point>51){
					shuffle(card_start);
					card_point=0;
				}
			}
			System.out.println("#Dealer Hand: "+dealerhand);
			System.out.println("#Player Hand: "+playerhand);

			do{
				System.out.println("Type 'hit' or 'pass' for next move");	
				input=scan.next();
				if(!input.equals("hit") && !input.equals("pass")){
					System.out.println("Error invalid command");
					invalid=true;
					continue;
				}
				if(input.equals("hit")){
					invalid=false;
					System.out.print("Player Card: ");
					temp=card(card[card_point]);
					if(temp==1 && playerhand<11){
						temp+=10;
						player_ace=true;
					}
					playerhand+=temp;
					if(playerhand>21 && player_ace){
						playerhand-=10;
						player_ace=false;
						
					}
					System.out.println("#Player Hand: "+playerhand);
					card_point++;
					if(card_point>51){
						shuffle(card_start);
						card_point=0;
					}
				}
				else if(input.equals("pass")){
					break;
				}
				if(playerhand>21 && !player_ace){
					break;
				}

			}while(input.equals("hit") || invalid);
			if(playerhand>21){
				System.out.println("You busted!");
				money-=bet;
				continue;
			}
			while(dealerhand<playerhand && dealerhand<21){
				System.out.print("Dealer Card: ");
				temp=card(card[card_point]);
				if(temp==1 && dealerhand<11){
					temp+=10;
					dealer_ace=true;
				}
				dealerhand+=temp;
				if(dealerhand>21 && dealer_ace){
					dealerhand-=10;
					dealer_ace=false;
				}
				card_point++;
				if(card_point>51){
					shuffle(card_start);
					card_point=0;
				}
			}
			System.out.println("#Dealer Hand: "+dealerhand);
			if(dealerhand>21 && !dealer_ace){
				System.out.println("Dealer busted!");
				money+=bet;
			}
			else if(playerhand<dealerhand){
				System.out.println("You lose");
				money-=bet;
			}
			else if(playerhand>dealerhand){
				System.out.println("You win");
				money+=bet;
			}
			else if(playerhand==dealerhand){
				System.out.println("tie");
			}
			System.out.println();
		}
		if(money<=0){
			System.out.println("Your broke, you lose!");
		}
	}
}
