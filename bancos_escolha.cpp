#ifdef defined(__WIN32) || defined(WIN32)
	#define OS_Windows
#endif

#include<vector>
using std::vector;

#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#include<string.h>
using std::string;
using std::getline;

enum banner { master_card, visa };

struct bank {
    string name;
    double teds_rate;
    banner card_banner;
    bool possibility_investments;
	double monthly_payment;
};

bank new_bank();
string take_decisioon(vector<bank> banks);
void list_banks(vector<bank> banks);
void print_bank_champion(string name, vector<bank> banks);

int main() {
    vector<bank> banks;
    int choice;

    do{
		//check OS for clear screen
		#ifdef OS_Windows
			system("cls");
		#else
			system("clear");
		#endif

        //which bank ..
        cout << "======= Which bank to choose ======= " << endl;
        cout << " 1 - New bank" << endl;
        cout << " 2 - Take decision" << endl;
        cout << " 3 - Remove bank" << endl;
        cout << "======================================" << endl;

        cin >> choice;

        if (choice == 1){
            struct bank newbank = new_bank();
            banks.push_back( newbank );
        }
        else if (choice == 3){
            int choice_for_remove;

            list_banks(banks);
            cin >> choice_for_remove;

            vector<bank>::iterator index = banks.begin() + (choice_for_remove - 1);
            
            banks.erase(index);
        }

    }while(choice != 2);

	//check OS for clear screen
	#ifdef OS_Windows
		system("cls");
	#else
		system("clear");
	#endif

	string name_bank_champion = take_decisioon(banks);
	print_bank_champion(name_bank_champion, banks);

}

void print_bank_champion(string name, vector<bank> banks) {
	struct bank b;
	//indentifier bank
	for(int i=0; i<banks.size(); i++)
		if( banks[i].name == name){
			b = banks[i];
			break;
		}

	cout << " ====== bank champion ====== " << endl;
    cout << "name: " << "___________________ " << b.name << endl;
	cout << "transfer rate: " << "__________ R$ " << b.teds_rate << endl;
	cout << "card banner: " << "____________ " << (b.card_banner == banner::master_card ? "master card" : "visa") << endl;
	cout << "possibility investments: " << " " << (b.possibility_investments ? "yes" : "no") << endl;
	cout << "monthly payment: " << "________ R$ " << b.monthly_payment << endl;
    cout << " =========================== " << endl;
}

void list_banks(vector<bank> banks){
    cout << " ====== select bank ======= " << endl;
    
    for(int i=0; i<banks.size(); i++)
        cout << i + 1 << " - " << banks[i].name << endl;
    
    cout << " ======================== " << endl;
}

bank new_bank() {
    string name;
    double teds_rate;
    banner card_banner;
    bool possibility_investments;
    double monthly_payment;

    int choice_card_banner;
    char choice_possibility_investments;

    cout << "name: ";
	while(getline(cin, name))
  		if(name != "")
  			break;

    cout << "teds rate: ";
    cin >> teds_rate;

	cout << endl;
    cout << "===== card_banner ====== " << endl;
    cout << " 1 - MASTER CARD" << endl;
    cout << " 2 - VISA" << endl;
    cout << "========================" << endl;
	cout << endl;
    cin >> choice_card_banner;
    
    card_banner = (choice_card_banner == 1) ? banner::master_card : banner::visa;

    cout << "possibility investments (y/n): ";
    cin >> choice_possibility_investments;

    possibility_investments = (tolower(choice_possibility_investments) == 'y') ? true : false;

	cout << "monthly payment: ";
	cin >> monthly_payment;

    struct bank b;
    b.name = name;
    b.card_banner = card_banner;
    b.possibility_investments = possibility_investments;
    b.teds_rate = teds_rate;
	b.monthly_payment = monthly_payment;

    return b;
}

string take_decisioon(vector<bank> banks) {
    string champion_bank = "";
    double MAX_PONTUATION = 0;
    
    for(int i=0; i<banks.size(); i++){
        double pontuation = 0;
        
        bank b = banks[i];
        
        if(b.possibility_investments)
            pontuation += 6;
        
        if(b.card_banner == banner::master_card)
            pontuation += 2;
        
        pontuation += (b.teds_rate == 0) ? 10: (10 / b.teds_rate);

		pontuation += (b.monthly_payment == 0) ? 10 : (10 / b.monthly_payment);
        
        if (pontuation > MAX_PONTUATION){
            MAX_PONTUATION = pontuation;
            
            champion_bank = b.name;
        }
    }
    
    return champion_bank;
}
