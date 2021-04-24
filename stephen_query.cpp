#include <iostream>

using namespace std;

bool isFirst = true;
bool newHero = true;

int rsp(int hero, int villain) {
    if(isFirst) {
        switch (hero)
        {
        case 1 :
            if(villain == 3) { isFirst = false; return 0; }
            else if(villain == 1) return 2;
            else { isFirst = false; return 1; }       
        case 2 : 
            if(villain == 1) { isFirst = false; return 0; }
            else if(villain == 2) return 2;
            else { isFirst = false; return 1; }
        default:
            if(villain == 2) { isFirst = false; return 0; }
            else if(villain == 3) return 2;
            else { isFirst = false; return 1; }
        }        
    }
    else {
        if(newHero) {
            switch (hero)
            {
            case 1 :
                if(villain == 3) return 0;
                else return 1;      
            case 2 : 
                if(villain == 1) return 0;
                else return 1;
            default:
                if(villain == 2) return 0;
                else return 1;
            }
        }
        else {
            switch (hero)
            {
            case 1 :
                if(villain == 2) return 1;
                else return 0;       
            case 2 : 
                if(villain == 3) return 1;
                else return 0;
            default:
                if(villain == 1) return 1;
                else return 0;
            }
        }
    }
}

int main() {
    int N, max_num = 0, fire_max = 0, ice_max = 0, cnt = 0;
    cin >> N;
    int fire[N];
    int ice[N];
    
    for(int i = 0; i < N; i++) {
        cin >> fire[i];
    }
    for(int i = 0; i < N; i++) {
        cin >> ice[i];
    }
    // hero == fire
    for(int i = 0; i < N; i++) {
        // lose
        if(rsp(fire[i], ice[i]) == 0) {
            newHero = true;
            fire_max = max(fire_max, cnt);
            cnt = 0;
        }
        // win
        else if(rsp(fire[i], ice[i]) == 1) {
            newHero = false;
            cnt++;
        }
        // draw
        else continue;
    }
    fire_max = max(fire_max, cnt);

    isFirst = true;
    newHero = true;
    cnt = 0;
    
    // hero == ice
    for(int i = 0; i < N; i++) {
        // lose
        if(rsp(ice[i], fire[i]) == 0) {
            newHero = true;
            ice_max = max(ice_max, cnt);
            cnt = 0;
        }
        // win
        else if(rsp(ice[i], fire[i]) == 1) {
            newHero = false;
            cnt++;
        }
        // draw
        else continue;
    }
    ice_max = max(ice_max, cnt);

    max_num = max(fire_max, ice_max);
    cout << max_num;
    return 0;
}