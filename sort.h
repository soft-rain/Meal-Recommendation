#pragma once

#define MAX 100
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"

STORE* sort(STORE *s){	
	static STORE* temp;;

	for(int i = 0; i < MAX; i++){
		for(int j = 0; j < MAX; j++){
			if(s[j].star < s[j + 1].star){
				memcpy(&temp, &s[j], sizeof (STORE));
				memcpy(&s[j], &s[j + 1], sizeof (STORE));
				memcpy(&s[j + 1], &temp, sizeof (STORE));
			}
		
		}
	}

	return s;
}

