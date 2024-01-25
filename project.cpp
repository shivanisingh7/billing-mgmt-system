#include<iostream>  
#include<process.h>  
#include<fstream>  
#include<string>
#include <stdlib.h>
#define SIZE 15  
using namespace std;

typedef struct product
{
	int code;
	int price;
	string name;
	
}prod;

class admin //base class
{

	protected:
		int n;//total number of food items
		prod lname[SIZE][3];  //menu
		string name;
		int code;
		int price;
	public:
		void get_data();
		void display_menu();
};

class reception:public admin  //derived class:reception base class:admin
{  
     
	protected:
	int code2; 
	int totalitems; 
	int n2;//quatity per item
	prod temp[SIZE][3];   //soln array
    float price[SIZE];  
    int vatprice[SIZE]; //price after adding tax 
    int tprice[SIZE];  //total price
 
public:
    
    void input();  
    void output(); 
};  


//class for tax calculation
class vat:public reception   //derived class:vat base class:reception
{  
    float vats;  
public:  

    void vatcal();  
    void outputs();  
    void sum();  
};
//******************************************************************  
//      INPUT FUNCTION FOR MENU(ADMIN ONLY) 
//******************************************************************   

void admin::get_data()
{
	cout<<"enter the number of items";
			cin>>n;
			for(int i=1;i<=n;i++)
			    
			{
				cout<<"enter name of product";
				cin>>name;
				lname[i][1].name=name;
				
				cout<<"enter item code";
				cin>>code;
				lname[i][2].code=code;
				
				cout<<"enter price";
				cin>>price;
				lname[i][3].price=price;
			}
	
} 

//******************************************************************  
//      DISPLAY FUNCTION FOR MENU(FOR ADMIN ONLY) 
//******************************************************************  

void admin::display_menu()
{
	
			cout<<"\n"<<"name"<<"\t"<<"code"<<"\t"<<"price"<<endl;
			for(int i=1;i<=n;i++)
			{
				cout<<"\n"<<lname[i][1].name<<"\t"<<lname[i][2].code<<"\t"<<lname[i][3].price<<endl;
			}
		
}
 
//******************************************************************  
//      INPUT FUNCTION(FOR RECEPTION) 
//******************************************************************  
 
void reception::input()  
{  
int c;
    system("CLS"); 
	cout<<"\n\n\t\t\t * * * * MENU * * * * \n"; 
    
    cout<<"\n"<<"name"<<"\t"<<"code"<<"\t"<<"price"<<endl;
	for(int i=1;i<=n;i++)
	{
		cout<<"\n"<<lname[i][1].name<<"\t"<<lname[i][2].code<<"\t"<<lname[i][3].price<<endl;
	}
   
    cout<<"\nEnter number of items = ";  
    cin>>totalitems;  
    
    for(int i=1;i<=totalitems;i++)
    {
    	cout<<"enter code of item";
    	cin>>code2;
    	for(int j=1;j<=n;j++)
    	{
    		if(lname[j][2].code==code2)
    		{
    			cout<<"enter quantity of item";
    			cin>>n2;
				
				temp[j][1].name=lname[j][1].name;
    			temp[j][2].code=lname[j][2].code;
    			temp[j][3].price=lname[j][3].price;
			    
				tprice[i]=n2*lname[i][3].price ; //total price= quantity*price
			}
			
		}
		
			
	}
}  

//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  
//     OUTPUT FUNCTION (FOR USER)
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  


void reception::output()  
{  
    int a;  
 
    ifstream infile("COUNT.TXT");  
    infile>>a;  
 
    ofstream outfile("COUNT.TXT");  
    a+=1;  
    outfile<<a;  
    outfile.close();  
 
    {ofstream outfile("HIS.TXT", ios::app);  
    outfile<<endl<<"Bill No.: "<<a<<endl;  
    outfile<<"------------------------------------------------------------------------"<<endl;  
cout<<"\n";  
    cout<<"Name of Item\t\t\Code \t\tPrice\t\tTotal Price\n"; 
	for(int i=1;i<=totalitems;i++)
	{
		outfile<<"Name:  "<<temp[i][1].name<<"code "<<temp[i][2].code<<"price "<<tprice[i];
		cout<<temp[i][1].name<<"\t\t        "<<temp[i][2].code<<"\t\t   "<<temp[i][3].price<<"\t\t    "<<tprice[i]<<endl;
	}  
 
    outfile<<"------------------------------------------------------------------------"<<endl;  
    outfile.close();  
    }  
}  
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  
//     VAT CALCULATION  
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  
void vat::vatcal()  
{  
    input();  
    for(int i=1;i<=totalitems;i++)  
    {  
        if(tprice[i]<=100.00)  
        {  
            vatprice[i]=tprice[i]+(0.03*tprice[i]);  
        }  
        else  
        {  
            vatprice[i]=tprice[i]+(0.1*tprice[i]);  
        }  
    }  
}  
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  
//      VAT OUTPUTS  
//*  * * * * * * * * * * * * * * * * * * * * ** * * * * * * * * * * * * * * * * * * * * * * * * *    
void vat::outputs()  
{  
    output();  
 
    float cash=0,sum=0,qty=0,sumt=0;  
 
    for(int i=1;i<=totalitems;i++)  
    {  
           sumt+=tprice[i];  
           sum+=vatprice[i];   
    }  
    cout<<"\nTotal:"<<sum;  
    cout<<"\n------------------------------------------------------------------------------";  
    cout<<"\t\t Sum= "<<sumt<<"\tWith Vat:"<<sum;  
    cout<<"\n------------------------------------------------------------------------------";  
 
pay:  
 
    cout<<"\n\n\t\t\t * * * * PAYMENT SUMMARY * * * * \n";  
    cout<<"\n\t\t\tTotal cash given: ";  
    cin>>cash;  
 
    if(cash>=sum)  
        cout<<"\n\t\t\tTotal cash repaid: "<<cash-sum<<'\n';  
         
    else  
    {   cout<<"\n\t\t\tCash given is less than total amount!!!";  
 
    goto pay;  
    }  
}  
 
 
int main()  
{  
    vat obj;  
    char opt, ch;  
    int a=1;
	cout << "\t\t\t=====================================" << endl;
	cout << "\t\t\t|                                   |" << endl;
	cout << "\t\t\t|                                   |" << endl;
	cout << "\t\t\t|               Welcome to          |" << endl;
	cout << "\t\t\t|           New Treat Everyday      |" << endl;
	cout << "\t\t\t|                                   |" << endl;
	cout << "\t\t\t|                                   |" << endl;
	cout << "\t\t\t=====================================" << endl;  
    ifstream fin;  
     do{  
    cout<<"\n\n\t\t\t------------------------------";  
    cout<<"\n\t\t\tBilling Management System";  
    cout<<"\n\t\t\t------------------------------";  
     cout<<"\n\n\t\t\tWhat you want to do?";  
     cout<<"\n\t\t\t1.\tTo create the menu for today(as admin)\n\t\t\t2.\torder and bill(bill desk)\n\t\t\t3.\tto view previous entries\n\t\t\t4.\texit\n";  
     cout<<"\n\nEnter your option: ";  
     cin>>opt;  
     switch(opt)  
     {  
     case'1':  
         obj.get_data();
		 obj.display_menu();
		 break;
     case'2':
	     obj.vatcal();
		 obj.outputs();
		 break;
 
     case'3':  
          fin.open("HIS.TXT", ios::in);  
         while(fin.get(ch))  
         {  
             cout<<ch;  
         }  
         fin.close(); 
		 break;  
	 case '4':
	 		exit(0); 
     default:  
         cout<<"\a";  
     }  
 
     }while(1);  
    return 0;  
}  

