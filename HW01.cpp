#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
using namespace std;

bool ends(string s, char target[]);
bool cons(int i, char target[]);
int m(char target[]);
bool vowelinstem(char target[]);
bool cvc(char target[]);
void step1(char target[]);
void step2(char target[]);
void step3(char target[]);
void step4(char target[]);
void step5(char target[]);
void step6(char target[]);

int main(){
	
	ifstream doc("C:\\Users\\Mark\\Desktop\\text.txt");   //read file
	
	string line;
	vector <string> token;
	char delim[] = " ,.\n''"; 
	char *t;
	char target[1000][30];
	int i=0, k=0;
	string stopwords[] = {"are","and", "the", "of", "two", "on", "in", "with", "against", "you", "to", "for", "the", "s", "that"};

	while (getline(doc, line)){
		transform(line.begin(), line.end(), line.begin(), ::tolower);  //convert to lowercase
	    t = strtok ((char*)line.c_str(), delim);   //parse with delim
	    while (t != NULL){
	    	strcpy(target[i], t);      //copy the string pointed to char array 'target'
	    	//printf ("%s\n", target[i]);
	    	i++;
	    	t = strtok(NULL, delim);   //t pointing to the next delimiter position
	  	} 
	}

	ofstream outfile ("C:\\Users\\Mark\\Desktop\\output.txt");

	/* 'target' is a char array, awaiting to undergo Porter's algorithm */
	while(strlen(target[k]) != 0){
		step1(target[k]);
		step2(target[k]);
		step3(target[k]);
		step4(target[k]);
		step5(target[k]);
		step6(target[k]);
		
		int check_delete = 1;
		for(int j=0; j<sizeof(stopwords)/sizeof(stopwords[0]); j++)
		{
			if (strcmp(target[k], stopwords[j].c_str())==0)
			{
				check_delete = 0;
				break;
			}
		}
		if(check_delete){
			cout<<target[k]<<endl;
			outfile <<target[k]<<endl;
		}
		k++;
	} 
		outfile.close();

	
	return 0;
}


/* check if a word end with the input string s */
bool ends(string s, char target[]) {
	int l = s.length(), k = strlen(target);
	int o = k-l+1;
	if (o < 0)
		return false;
	char sc[100] = "";
	strcpy(sc, s.c_str());
	for (int i = 0; i < s.length(); i++){
		if (target[o+i-1] != sc[i])
			return false;
	}
	return true;
}

/* cons(i) is true <=> target[i] is a consonant */
bool cons(int i, char target[]) {
	switch (target[i]) {
		case 'a': case 'e': case 'i': case 'o': case 'u': 
			return false;
		case 'y': 
			if (i==0)
				return true;
			else 
				return !cons(i-1, target);     //if Y is preceded by a consonant, then it's not a consonant
		default: 
			return true;
	}
}

/* c is a consonant sequence and v a vowel sequence
			  <c><v>       gives 0
			  <c>vc<v>     gives 1
			  <c>vcvc<v>   gives 2
			  <c>vcvcvc<v> gives 3
			  ....		 					*/
int m(char target[]) {
	int n = 0, i = 0, j = strlen(target)-1;
	while(true) {                     //get the end of starting c, meaning the next one is v
		if (i > j)                    
			return n;
		if (!cons(i, target))         
			break; 
		i++;                          
	}
	i++;
	while(true) {
		while(true) {
			if (i > j)                //get the end of v, meaning the next one is c
				return n;             //extreme case: CV will return 0
			if (cons(i, target)) 
				break;                
			i++;
		}
		i++;
		n++;
		while(true) {                 //get the end of c, meaning the next one is v
			if (i > j) 
				return n;			  //extreme case: CVC will return 1
			if (!cons(i, target)) 
				break;
			i++;
		}
		i++;
	}
}

/* find if there's vowel in input char array */
bool vowelinstem(char target[]) {
	int i;
	for (i = 0; i <= strlen(target)-1; i++)
		if (! cons(i, target))
			return true;
	return false;
}

/* the stem ends cvc, where the second c is not W, X or Y */
bool cvc(char target[]) {
	int i = strlen(target)-1;
	if (i < 2 || !cons(i, target) || cons(i-1, target) || !cons(i-2, target))
		return false;
	int last = target[i];
	if (last == 'w' || last == 'x' || last == 'y')
		return false;
	return true;
}


/* step1() gets rid of plurals and -ed or -ing. e.g.
	1(a)	
				SSES -> SS                      
			    IES  -> I                         
			    SS   -> SS                     
			    S    ->    		  
	1(b)		  
		  (m>0) EED -> EE                                          
		  (*v*) ED  ->                                                   
		  (*v*) ING ->   
	1(c)
		If the second or third of the rules in Step 1b is successful, the following is done:

			    AT -> ATE                       conflat(ed)  ->  conflate
			    BL -> BLE                       troubl(ed)   ->  trouble
			    IZ -> IZE                       siz(ed)      ->  size
			    (*d and not (*L or *S or *Z))
			       -> single letter
			                                    hopp(ing)    ->  hop
			                                    tann(ed)     ->  tan
			                                    fall(ing)    ->  fall
			                                    hiss(ing)    ->  hiss
			                                    fizz(ed)     ->  fizz
			    (m=1 and *o) -> E               fail(ing)    ->  fail
			                                    fil(ing)     ->  file                   
	       									*/
void step1(char target[]) {
	char temp[100];
	int k = strlen(target)-1;
	if (target[k] == 's') {
		if (ends("sses", target))              // SSES -> SS  
		{
			strncpy(temp, target, strlen(target)-2);
			strcpy(target, temp);
		}
		else if (ends("ies", target))          // IES  -> I 
		{
			strncpy(temp, target, strlen(target)-2);
			strcpy(target, temp);
		}
		else if (k>=1 && (target[k-1] != 's'))   			 // S    ->   ,but SS   -> SS  	
		{
			strncpy(temp, target, strlen(target)-1);
			strcpy(target, temp);
		}
	}
	if (ends("eed", target)) {                 //(m>0) EED -> EE         mÁÙ¨S¼g 
		if (m(target) > 0)
		{
			strncpy(temp, target, strlen(target)-1);
			strcpy(target, temp);	
		}
	} 
	else if ((ends("ed", target) || ends("ing", target)) && vowelinstem(target)) {    //(*v*) ED  ->  , ING ->      and 1(c)
		if (ends("ed", target))
		{
			strncpy(temp, target, strlen(target)-2);
			strcpy(target, temp);	
		}
		if (ends("ing", target))
		{
			strncpy(temp, target, strlen(target)-3);
			strcpy(target, temp);	
		}
			
		if (ends("at", target))
			strcat(target, "e");
		else if (ends("bl", target))
			strcat(target, "e");
		else if (ends("iz", target))
			strcat(target, "e");
		else if ((target[strlen(target)-1] == target[strlen(target)-2])&&(target[strlen(target)-1] != 'l')
					&&(target[strlen(target)-1] != 's')&&(target[strlen(target)-1] != 'z')&&(strlen(target) != 1))
		{			
			target[strlen(target)-1]='\0';
		}
		else if (m(target) == 1 && cvc(target))		
			strcat(target, "e");
			
		
	}
}

/* step2() if there is "another" vowel in the token, replace ending y with i */
void step2(char target[]) {
	char temp[100] = "";
	strncpy(temp, target, strlen(target)-1);
	if (ends("y", target) && vowelinstem(temp))
		target[strlen(target)-1] = 'i';
}

void step3(char target[]) {
	if (m(target) == 0)
		return;
	
	char temp[100];
	switch (target[strlen(target)-2]) {
		case 'a':
			if (ends("ational", target)) {strncpy(temp, target, strlen(target)-7); strcpy(target, temp); strcat(target, "ate"); break; }
			if (ends("tional", target)) {strncpy(temp, target, strlen(target)-6); strcpy(target, temp); strcat(target, "tion"); break; }
			break;
		case 'c':
			if (ends("enci", target)) {strncpy(temp, target, strlen(target)-4); strcpy(target, temp); strcat(target, "ence"); break; }
			if (ends("anci", target)) {strncpy(temp, target, strlen(target)-4); strcpy(target, temp); strcat(target, "ance"); break; }
		break;
		case 'e':
			if (ends("izer", target)) {strncpy(temp, target, strlen(target)-4); strcpy(target, temp); strcat(target, "ize"); break; }
			break;
		case 'l':
			if (ends("bli", target)) {strncpy(temp, target, strlen(target)-3); strcpy(target, temp); strcat(target, "ble"); break; }
			if (ends("alli", target)) {strncpy(temp, target, strlen(target)-4); strcpy(target, temp); strcat(target, "al"); break; }
			if (ends("entli", target)) {strncpy(temp, target, strlen(target)-5); strcpy(target, temp); strcat(target, "ent"); break; }
			if (ends("eli", target)) {strncpy(temp, target, strlen(target)-3); strcpy(target, temp); strcat(target, "e"); break; }
			if (ends("ousli", target)) {strncpy(temp, target, strlen(target)-5); strcpy(target, temp); strcat(target, "ous"); break; }
			break;
		case 'o':
			if (ends("ization", target)) {strncpy(temp, target, strlen(target)-7); strcpy(target, temp); strcat(target, "ize"); break; }
			if (ends("ation", target)) {strncpy(temp, target, strlen(target)-5); strcpy(target, temp); strcat(target, "ate"); break; }
			if (ends("ator", target)) {strncpy(temp, target, strlen(target)-4); strcpy(target, temp); strcat(target, "ate"); break; }
			break;
		case 's':
			if (ends("alism", target)) {strncpy(temp, target, strlen(target)-5); strcpy(target, temp); strcat(target, "al"); break; }
			if (ends("iveness", target)) {strncpy(temp, target, strlen(target)-7); strcpy(target, temp); strcat(target, "ive"); break; }
			if (ends("fulness", target)) {strncpy(temp, target, strlen(target)-7); strcpy(target, temp); strcat(target, "ful"); break; }
			if (ends("ousness", target)) {strncpy(temp, target, strlen(target)-7); strcpy(target, temp); strcat(target, "ous"); break; }
			break;
		case 't':
			if (ends("aliti", target)) {strncpy(temp, target, strlen(target)-5); strcpy(target, temp); strcat(target, "al"); break; }
			if (ends("iviti", target)) {strncpy(temp, target, strlen(target)-5); strcpy(target, temp); strcat(target, "ive"); break; }
			if (ends("biliti", target)) {strncpy(temp, target, strlen(target)-6); strcpy(target, temp); strcat(target, "ble"); break; }
			break;
		case 'g':
			if (ends("logi", target)) {strncpy(temp, target, strlen(target)-1); strcpy(target, temp); break; }
			break;
		default :
			break;
	}
	return;
}

void step4(char target[]) {
	if (m(target) == 0)
		return;
	
	char temp[100];	
	switch (target[strlen(target)-1]) {
		case 'e':
			if (ends("icate", target)) {strncpy(temp, target, strlen(target)-3); strcpy(target, temp); break; }
			if (ends("ative", target)) {strncpy(temp, target, strlen(target)-5); strcpy(target, temp); break; }
			if (ends("alize", target)) {strncpy(temp, target, strlen(target)-3); strcpy(target, temp); break; }
			break;
		case 'i':
			if (ends("iciti", target)) {strncpy(temp, target, strlen(target)-3); strcpy(target, temp); break; }
			break;
		case 'l':
			if (ends("ical", target)) {strncpy(temp, target, strlen(target)-2); strcpy(target, temp); break; }
			if (ends("ful", target)) {strncpy(temp, target, strlen(target)-3); strcpy(target, temp); break; }
			break;
		case 's':
			if (ends("ness", target)) {strncpy(temp, target, strlen(target)-4); strcpy(target, temp); break; }
			break;
	}
	return;
}

void step5(char target[]) {
	if (m(target) < 2)
		return;
	
	char temp[100];
	switch (target[strlen(target)-2]) {
		case 'a':
			if (ends("al", target)) {strncpy(temp, target, strlen(target)-2); strcpy(target, temp); break; }
		case 'c':
			if (ends("ance", target)) {strncpy(temp, target, strlen(target)-4); strcpy(target, temp); break; }
			if (ends("ence", target)) {strncpy(temp, target, strlen(target)-4); strcpy(target, temp); break; }
		case 'e':
			if (ends("er", target)) {strncpy(temp, target, strlen(target)-2); strcpy(target, temp); break; }
		case 'i':
			if (ends("ic", target)) {strncpy(temp, target, strlen(target)-2); strcpy(target, temp); break; }
		case 'l':
			if (ends("able", target)) {strncpy(temp, target, strlen(target)-4); strcpy(target, temp); break; }
			if (ends("ible", target)) {strncpy(temp, target, strlen(target)-4); strcpy(target, temp); break; }
		case 'n':
			if (ends("ant", target)) {strncpy(temp, target, strlen(target)-3); strcpy(target, temp); break; }
			if (ends("ement", target)) {strncpy(temp, target, strlen(target)-5); strcpy(target, temp); break; }
			if (ends("ment", target)) {strncpy(temp, target, strlen(target)-4); strcpy(target, temp); break; }
			if (ends("ent", target)) {strncpy(temp, target, strlen(target)-3); strcpy(target, temp); break; }
		case 'o':
			if (ends("ion", target) && ((strlen(target)-4) >= 0) && (target[strlen(target)-4] == 's' || target[strlen(target)-4] == 't')) 
				{strncpy(temp, target, strlen(target)-3); strcpy(target, temp); break; }
			if (ends("ou", target)) {strncpy(temp, target, strlen(target)-2); strcpy(target, temp); break; }
		case 's':
			if (ends("ism", target)) {strncpy(temp, target, strlen(target)-3); strcpy(target, temp); break; }
		case 't':
			if (ends("ate", target)) {strncpy(temp, target, strlen(target)-3); strcpy(target, temp); break; }
			if (ends("iti", target)) {strncpy(temp, target, strlen(target)-3); strcpy(target, temp); break; }
		case 'u':
			if (ends("ous", target)) {strncpy(temp, target, strlen(target)-3); strcpy(target, temp); break; }
		case 'v':
			if (ends("ive", target)) {strncpy(temp, target, strlen(target)-3); strcpy(target, temp); break; }
		case 'z':
			if (ends("ize", target)) {strncpy(temp, target, strlen(target)-3); strcpy(target, temp); break; }
		default:
			return;
	}
	return;
}

void step6(char target[]) {
			
	char temp[100] = "";
	strncpy(temp, target, strlen(target)-1);
	
	char tempt[100];
	if (m(target)>1 && target[strlen(target)-1] == 'e') 
	{
		strncpy(tempt, target, strlen(target)-1); 
		strcpy(target, tempt);
	}
	if (m(target)==1 && target[strlen(target)-1] == 'e' && !cvc(temp) && strlen(temp)>=3) 
	{
		strncpy(tempt, target, strlen(target)-1); 
		strcpy(target, tempt);
	}
	if (m(target)>1 && target[strlen(target)-1] != 'L' && (target[strlen(target)-1] == target[strlen(target)-2]))
	{
		strncpy(tempt, target, strlen(target)-1); 
		strcpy(target, tempt);
	}
}





