#include<iostream>
#include<cmath>
#include<string.h>

int decoder(char*);
int findint(char*);
void hamming(int, char*);


int main(){
	char bts[12];
	hamming(149,bts);

	int ans = decoder(bts);
	std::cout << ans << std::endl;
	return 0;
}

int decoder(char *bts){
	int ans = 0;
	int errcorr = 0;
	for (int i=0; i<12; i++){
		if (bts[i] == 1){
			errcorr ^= i+1;
		}
	}
	std::cout << errcorr << std::endl;
	if (errcorr > 12)
		return -1;
	if (errcorr != 0){
		if (bts[errcorr-1] == '0')
			bts[errcorr-1] = '1';
		else
			bts[errcorr-1] = '0'; 
	}
	ans = findint(bts);
	if (errcorr != 0){
		char newham[12];
		hamming(ans,newham);

		if (strcmp(bts,newham)!=0){
			return -1;
		}
	}
	return ans;
}

int findint(char *bts){
	int ans = 0;
	int ans_index[8] = {2,4,5,6,8,9,10,11};
	for (int i = 0;i<8;i++)
		ans += (int)(bts[ans_index[i]]-48)*pow(2,7-i);
	return ans;
}

void hamming(int input_num, char* output_bits){
    int errcorr = 0;
    for(int i = 11, tmp = input_num; i >= 0; --i){
        output_bits[i] = '0';
        switch(i){
            case 0: case 1: case 3: case 7: continue;
            default:
                if(tmp & 1){
                    output_bits[i] = '1';
                    errcorr ^= (i+1);
                }
                tmp = tmp >> 1;
        }
    }
    
    int r[4] = {0, 1, 3, 7};
    for(int i = 3; i >= 0; --i){
        if(errcorr & 1) output_bits[r[3-i]] = '1';
        errcorr = errcorr >> 1;
    }
}