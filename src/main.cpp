#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <random>
#include <map>
#include <ratio>
#include <string>

int random_between(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}
int ordered_random(int randcount=100, int min=1, int max=10){
    static std::map<int, int> stats {};
    stats.clear();
    for(int i = 0; i < randcount; ++i){
        ++stats[random_between(min,max)];
    }
    
    for(const auto& e : stats) {
        std::cout << e.first << ": " << e.second << '\n';
    }
    return 0;
}

static std::string draw_card(int num, bool guess_correct = false)
{
    std::string n = std::to_string(num);

    // Center the number in width 7
    int padding = 5 - n.length();
    int left = padding / 2;
    int right = padding - left;

    std::string gstr;
    std::string h_or_l = "Will the next card be higher (\"h\") or lower? (\"l\")";
    if (guess_correct){
        gstr   = "   You have guessed correctly.";
    }

    std::string card;
    card += "┌───────┐\n";
    card += "│       │" + gstr + '\n';
    card += "│ " + std::string(left, ' ') + n + std::string(right, ' ') + " │   " + h_or_l +'\n';
    card += "│       │\n";
    card += "└───────┘\n";

    return card;
}

void game(int min=1, int max=100){
    int cur = min;
    int next = random_between(min, max);
    bool is_alive = true;
    char choice;
    std::cout << draw_card(cur);
    //std::cout << "Will the next card be higher (\"h\") or lower? (\"l\") ";

    while (is_alive) {
        while (!(choice == 'l' || choice =='h')){
            std::cin >> choice;
            if (!(choice == 'l' || choice =='h')){
                std::cout << "\nThat isn't a valid choice. Choose again: ";
            }
            else{
                break;
            }
        }
        std::cout << choice;
        bool firstpart = (choice == 'h' && cur<=next);
        bool secondpart = (choice == 'l' && cur>=next);
        bool correct = (choice == 'h' && next > cur) || (choice == 'l' && next < cur);
        //std::cout << " firstpart " << firstpart << " secondpart:" << secondpart;
        if ((correct) ){
            cur = next;

            do {
                next = random_between(min, max);
            } while (cur == next);
            std::cout << "\n\n\n\n\n" << draw_card(cur, true) /*<< "\nWill the next card be higher (\"h\") or lower? (\"l\") Choice: "*/;
            std::cin >> choice;
        }
        else {
            std::cout << "\nUnfortunately you've guessed wrong, and lost the game. The next number was " << next << ' ';
            is_alive=false;
        }
        
    }
}

int main(){
    game(-1000, 1000);
    //while (true) {std::cout<<draw_card(random_between(-100, 1000));}
    return 0;
}
