#include <iostream>
#include <string>
#include <limits>
#include <conio.h>

	using namespace std;
	
		class house{
			private:
				float temp, maxSqm, flooringCost, bedroomCost[5], bedroomTotal, kitchenCost, bathroomCost[3], bathroomTotal, paintingTotal, classCounter, LBTotal, UBTotal, flooringLB, flooringUB, houseTotalLB, houseTotalUB;
				int bedroomMax, bathroomMax, paintingWorkerLB, paintingWorkerUB, paintingDayLB, paintingDayUB;//LB = Lower Boundary, UB = Upper Boundary
				
			public:
				void setHouseChoice(int classHouseChoice){
					switch (classHouseChoice){
						case 1:
							bedroomMax=4; 
							bathroomMax=2; 
							maxSqm=180; 
							flooringCost=123450;
							paintingWorkerLB=5;
							paintingWorkerUB=10;
							paintingDayLB=5;
							paintingDayUB=10;
						break;
						case 2:
							bedroomMax=5; 
							bathroomMax=3; 
							maxSqm=250 ;
							flooringCost=180500;
							paintingWorkerLB=10;
							paintingWorkerUB=15;
							paintingDayLB=7;
							paintingDayUB=14;
						break;
					}
				}
				
				void setExtraFees(float classExtraFees){
					flooringCost=flooringCost+classExtraFees;
				}
				
				void setBedroomCost(float classBedroomSqm, int classBedroomCounter){
					if(classBedroomSqm<30){
						bedroomCost[classBedroomCounter]=classBedroomSqm*125;
					}
					else if(classBedroomSqm>=30 && classBedroomSqm<40){
						bedroomCost[classBedroomCounter]=classBedroomSqm*175.25;
					}
					else if(classBedroomSqm>=40){
						bedroomCost[classBedroomCounter]=classBedroomSqm*205.50;
					}
					bedroomTotal=bedroomTotal+bedroomCost[classBedroomCounter];
				}
				
				void setBathroomCost(float classBathroomSqm, int classBathroomCounter){
					bathroomCost[classBathroomCounter] = 6550;
					bathroomTotal = bathroomTotal + bathroomCost[classBathroomCounter];
				}
				
				void setKitchenCost(float classKitchenSqm){
					if(classKitchenSqm<=50){
						kitchenCost=12500;
					}
					else if(classKitchenSqm>50){
						temp=classKitchenSqm-50;
						temp=temp*75.45;
						kitchenCost=12500+temp;
					}
				}
				
				void setWorkerFees(){
					paintingWorkerLB=paintingWorkerLB*paintingDayLB;
					paintingWorkerUB=paintingWorkerUB*paintingDayUB;
					flooringLB=(10*7)*550;
					flooringUB=(15*15)*550;
					LBTotal=flooringLB+(paintingWorkerLB*650);						
					UBTotal=flooringUB+(paintingWorkerUB*650);
				}
				
				float getLowerBoundary(){
					return LBTotal;
				}
				
				float getUpperBoundary(){
					return UBTotal;
				}
				
				float getPaintingTotal(){
					paintingTotal = bedroomTotal + kitchenCost + bathroomTotal;
					return paintingTotal;
				}
				
				float getFlooringTotal(){
					return flooringCost;
				}
					
				float getHouseTotalLB(){
					houseTotalLB = LBTotal + paintingTotal + flooringCost;
				}
				
				float getHouseTotalUB(){
					houseTotalUB = UBTotal + paintingTotal + flooringCost;
				}
				
				int getBedroomMax(){
					return bedroomMax;
				}
				
				int getBathroomMax(){
					return bathroomMax;
				}
				
				int getMaxSqm(){
					return maxSqm;
				}
			};
		  
		void integerValidation(int &number, int range1, int range2){
			while (!(cin >> number) || number<range1 || number>range2) {
		        cout <<"	Invalid input. Please try again: ";
		        cin.clear(); 
		        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    		}
		}
		
		void floatValidation(float &number, float range1, float range2) {
		    while (!(cin >> number) || number < range1 || number > range2) {
		        cout <<"	Invalid input. Please try again: ";
		        cin.clear();
		        cin.ignore(numeric_limits<streamsize>::max(), '\n');
		    }
		}
		
		bool limitValidation(float limit, float roomSqm){
			if(limit<roomSqm){
				cout<<"	You have went above the square meter limit, Please run the program again.";
				return true;
			}
			return false;	//square meter limit validation
		}
	
	int main(){
		float sqmLimit, bedroomSqm, kitchenSqm, bathroomSqm;
		int numberOfHouses=0, houseChoice=0, loopCounter=0, bedroomCount=0, bathroomCount=0, extraFees=0;
		house houseArray[5];
		
		cout<<"	Please Input the Number of Houses(1-5): ";
		integerValidation(numberOfHouses, 1, 5);
		
		for(loopCounter=0; loopCounter<numberOfHouses; loopCounter++){
			cout<<"\n	1. Lin\n	2. Lan\n	Please Input the type of house(1 or 2): ";
			integerValidation(houseChoice, 1, 2);
			
	    	houseArray[loopCounter].setHouseChoice(houseChoice);  
	    	sqmLimit=houseArray[loopCounter].getMaxSqm();
	    	
			cout<<"	Please Enter the Number of Bedrooms: ";
			integerValidation(bedroomCount, 0, houseArray[loopCounter].getBedroomMax());
			
			if(bedroomCount>2 && bedroomCount<=4)
				extraFees=extraFees+(bedroomCount-2)*8500;
				
			cout<<"	Please Enter the Number of Bathrooms: ";
			integerValidation(bathroomCount, 0, houseArray[loopCounter].getBathroomMax());
			
			if(bathroomCount>1 && bathroomCount<=2)
				extraFees=extraFees+(bathroomCount-1)*4750;
				
			for(int i=0;i<bedroomCount;i++){
				cout<<"	Input the total square meters for bedroom no."<<i+1<<": ";
				floatValidation(bedroomSqm, 1, houseArray[loopCounter].getMaxSqm());
				if (limitValidation(sqmLimit, bedroomSqm)) {
					getch();
	         		return 0; // Terminate the program if the limit is exceeded
				}
	    		houseArray[loopCounter].setBedroomCost(bedroomSqm, i);
				sqmLimit=sqmLimit-bedroomSqm;
				cout<<"	Square Meters left: "<<sqmLimit<<"\n";
			}
			
			cout<<"	Input the total square meters for the kitchen: ";
			floatValidation(kitchenSqm, 1, houseArray[loopCounter].getMaxSqm());
			if (limitValidation(sqmLimit, kitchenSqm)) {
					getch();
	         		return 0; // Terminate the program if the limit is exceeded
				}
			houseArray[loopCounter].setKitchenCost(kitchenSqm);
			sqmLimit=sqmLimit-kitchenSqm;
			cout<<"	Square Meters left: "<<sqmLimit<<"\n";
			
			
			for(int i=0;i<bathroomCount;i++){
				cout<<"	Input the total square meters for bathroom no."<<i+1<<": ";
				floatValidation(bathroomSqm, 1, houseArray[loopCounter].getMaxSqm());
				if (limitValidation(sqmLimit, bathroomSqm)) {
					getch();
	         		return 0; // Terminate the program if the limit is exceeded
				}
	    		houseArray[loopCounter].setBathroomCost(bathroomSqm, i);
				sqmLimit=sqmLimit-bathroomSqm;
				cout<<"	Square Meters left: "<<sqmLimit<<"\n";
			}
			
			houseArray[loopCounter].setExtraFees(extraFees);
			houseArray[loopCounter].setWorkerFees();
			
			cout<<"\n\n	Painting Cost: "<< houseArray[loopCounter].getPaintingTotal()<<"\n";
			cout<<"	Flooring Cost: "<< houseArray[loopCounter].getFlooringTotal()<<"\n";
			cout<<"	Worker Cost (Cheapest, More Time): "<< houseArray[loopCounter].getLowerBoundary()<<"\n";
			cout<<"	Worker Cost (More Cost, Less Time): "<< houseArray[loopCounter].getUpperBoundary()<<"\n";
			cout<<"\n	House Cost(Cheapest, More Time): "<< houseArray[loopCounter].getHouseTotalLB()<<"\n";
			cout<<"	House Cost(More Cost, Less Time): "<< houseArray[loopCounter].getHouseTotalUB()<<"\n";
			
			cout<<"\n	Press Any Key to move to the next house.";
			getch();
			extraFees=0;
			system("cls");
			
	}
		return 0;
	}