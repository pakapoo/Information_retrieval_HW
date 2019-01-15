#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <map>
#include<iomanip>
#include <windows.h>
#include <list>
#include <math.h>
#include <utility>      // std::pair, std::make_pair
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
struct Arr5
{
    int num[5];
};
void printVec(vector< pair<string,double> > &vec){
    vector<pair<string,double> >::iterator it;
    for(it = vec.begin(); it!= vec.end(); ++it){
        cout<<it->first<<" : "<<it->second<<endl;
    }
}
void HAC(int cluster_num);
void dictMerge(int first, int second, int N[1096], std::vector<std::map<string,double>>& vecOfMaps);


double cosine(string docX, string docY);
double cosine(std::map<string, double> first, std::map<string, double> second);
void getTFIDF(string doc, map<string, Arr5> dict, double N);
void TrainMultinomialNB(int classes[][16],  int num[13]);
int ApplyMultinomialNB(string doc,  int num[13]);
void SelectFeatures(int classes[][16]);
bool comp_by_value(pair<string,double> &p1, pair<string,double> &p2){
    return p1.second > p2.second;
}


int main(){
	/*
	string line, path;
	map<string, Arr5> dict;           
	char delim[] = " ,.!\n''\"?();:-`~_%@$#1234567890}{/*&"; 
	string stopwords[10000];
	ifstream doc("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\Stopwords.txt");
	int count = 0, doc_num = 0;
	while (getline(doc, line)){
		stopwords[count] = line;
		count++;
	}
	
	char *t;
	int i=0, k=0, r=0;
	
	char InputPath[65535] = "C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM12";    //放要讀取檔案的資料夾路徑到InputPath字串裡
    char szDir[65535];
    char dir[65535];
    WIN32_FIND_DATA FileData;
    HANDLE          hList;
    sprintf(szDir, "%s\\*", InputPath );
	
	
if ( (hList = FindFirstFile(szDir, &FileData))==INVALID_HANDLE_VALUE )
    printf("No files be found.\n\n");
else {
    while (1) {
    	if (!FindNextFile(hList, &FileData)) {
            if (GetLastError() == ERROR_NO_MORE_FILES)
                break;
        }
    //sprintf(dir, "%s\\%s", InputPath, FileData.cFileName);
    string x = FileData.cFileName;
	ifstream doc("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM12\\"+x);
	cout<<endl<<x<<endl;    //print currently processing file
	doc_num++;
	cout<<doc_num<<endl;
	k=0, r=0, i=0;               //initialize
	map<string, int> document;    //存tf 
	map<string, int>::iterator mp1; //initialize
	for(mp1 = document.begin(); mp1  != document.end(); mp1++){
		(*mp1).second = 0;
	}
	char target[15000][50];
	memset(target, 0, sizeof(target));
	string result[15000];
	map<string, Arr5>::iterator mp; //initialize
	for(mp = dict.begin(); mp  != dict.end(); mp++){
		(*mp).second.num[3] = 0;
	}
	while (getline(doc, line)){
		transform(line.begin(), line.end(), line.begin(), ::tolower);  //convert to lowercase
	    t = strtok ((char*)line.c_str(), delim);   //parse with delim
	    while (t != NULL){
	    	strcpy(target[i], t);      //copy the string pointed to char array 'target'
	    	cout<<i<<" "<<(target[i])<<endl;
			i++;
	    	t = strtok(NULL, delim);   //t pointing to the next delimiter position
	  	} 
	}*/

	/* 'target' is a char array, awaiting to undergo Porter's algorithm */
	/*while(strlen(target[k]) != 0){
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
			result[r] = target[k];
			document[result[r]]++;
			
			if(dict.count(result[r])){
				Arr5 temp;
				temp = dict[result[r]];
				temp.num[0]++;
				dict[result[r]] = temp;
				if (dict[result[r]].num[3] != 1){
					dict[result[r]].num[2] = dict[result[r]].num[2]+1;
					dict[result[r]].num[3] = 1;
				}
				
				cout<<result[r]<<" "<<document[result[r]]<<" "<<dict[result[r]].num[2]<<endl;
			}
			
			else{
				Arr5 temp1;
				int array[] = {1,0,0,0,0};
				std::copy(array, array+5, temp1.num);
				dict[result[r]] = temp1;
				if (dict[result[r]].num[3] != 1){
					dict[result[r]].num[2] = dict[result[r]].num[2]+1;
					dict[result[r]].num[3] = 1;
				}
				
				cout<<r<<" "<<result[r]<<" "<<dict[result[r]].num[0]<<" "<<dict[result[r]].num[2]<<endl;
			} 

			r++;
		}
		
		k++;		
	} 
	
	cout<<endl<<endl;
	
	ofstream outfile ("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM_OUT\\"+x);
	outfile<<std::left<<setw(70)<<"term"<<setw(70)<<"tf"<<endl;
	map<string, int>::iterator it;
	for(it = document.begin(); it != document.end(); it++){
		outfile<<std::left<<setw(70)<<(*it).first;
		outfile<<std::left<<setw(70)<<(*it).second<<endl;
	}
	outfile.close();
	}
}

	ofstream outfile ("C:\\Users\\Mark\\Desktop\\dictionary.txt");
	outfile<<std::left<<setw(70)<<"t_index"<<setw(70)<<"term"<<setw(70)<<"df"<<endl;

	map<string, Arr5>::iterator it;
	int v = 1, sum = 0;
	
	//dictionary export
	for(it = dict.begin(); it != dict.end(); it++){
		(*it).second.num[1] = v;
		cout<<std::left<<setw(70)<<(*it).second.num[1];
		cout<<std::left<<setw(70)<<(*it).first;
		cout<<std::left<<setw(70)<<(*it).second.num[2]<<endl;
		outfile<<std::left<<setw(70)<<(*it).second.num[1];
		outfile<<std::left<<setw(70)<<(*it).first;
		outfile<<std::left<<setw(70)<<(*it).second.num[2]<<endl;
        v++;
	}  
	cout<<"total doc number: "<<doc_num-1;    //total doc number 
	*/

	/*
	char InputPathA[65535] = "C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM_OUT";    //放要讀取檔案的資料夾路徑到InputPath字串裡
    char szDirA[65535];
    char dirA[65535];
    WIN32_FIND_DATA AFileData;
    HANDLE          AhList;
    sprintf(szDirA, "%s\\*", InputPathA );
    int f=0;
if ( (AhList = FindFirstFile(szDirA, &AFileData))==INVALID_HANDLE_VALUE )
    printf("No files be found.\n\n");
else {
	while (1) {
	    if (!FindNextFile(AhList, &AFileData)) {
	        if (GetLastError() == ERROR_NO_MORE_FILES)
	            break;
	    }
	    else{
	    	f++;
			string x = AFileData.cFileName;
			getTFIDF(x, dict, doc_num-1);	
		}
	}
}
	string a = "Doc1.txt", b = "Doc2.txt";
	cosine(a, b);
	cout<<"    "<<f-1;*/
	
	/*int classes[13][16];
	int testing[195];
	int num[13];
	int count = 0;
	char *kk;
	int class_num = 0;
	int p = 0;
	string line2;
	ifstream doc2("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\class.txt");
	while (getline(doc2, line2)){
		p = 0;
	    kk = strtok ((char*)line2.c_str(), " ");   //parse with delim
	    while (kk != NULL){
	    	classes[class_num][p] =  atoi(kk);      //copy the string pointed to char array 'target'
	    	if(p!=0)
	    	{
	    		testing[count] = atoi(kk);
	    		count++;
			}
	    	//cout<<p<<" "<<(classes[class_num][p])<<" ";
			p++;
			//cout<<"count"<<" "<<count<<" ";
	    	kk = strtok(NULL, " ");   //t pointing to the next delimiter position
	  	} 
	  	//cout<<endl;
	  	class_num++;
	}
	SelectFeatures(classes);
	TrainMultinomialNB(classes, num);

	char InputPathA[65535] = "C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM_OUT";    //放要讀取檔案的資料夾路徑到InputPath字串裡
	ofstream myfile ("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索");
	myfile.open ("result.csv");
	myfile <<"Id"<<","<<"Value"<<"\n";	
    char szDirA[65535];
    char dirA[65535];
    int startid = 0;
    WIN32_FIND_DATA AFileData;
    HANDLE          AhList;
    sprintf(szDirA, "%s\\*", InputPathA );
    int f=0;
	if ( (AhList = FindFirstFile(szDirA, &AFileData))==INVALID_HANDLE_VALUE )
	    printf("No files be found.\n\n");
	else {
		while (1) {
		    if (!FindNextFile(AhList, &AFileData)) {
		        if (GetLastError() == ERROR_NO_MORE_FILES)
		            break;
		    }
		    else{
		    	int is_test = 0;
		    	f++;
				string x = AFileData.cFileName;
				for(int i=0; i<195; i++)
				{
					if(atoi(x.substr(0, x.find(".txt", 0)).c_str())==testing[i])
					{
						is_test = 1;
						break; 
					}
				}
				if (startid>0 && is_test!=1)
				{ 
					myfile << x.substr(0, x.find(".txt", 0))<<","<<ApplyMultinomialNB(x, num)<<"\n";
					}	
				startid ++;
			}
		}
	}*/
	
	//HAC(8);
	HAC(20);
	//HAC(13);

	
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
	int k = strlen(target)-1;
	if (target[k] == 's') {
	char temp[100] = "";
		if (ends("sses", target))              // SSES -> SS  
		{
			strncpy(temp, target, strlen(target)-2);
			if(strlen(temp) != 0)
				strcpy(target, temp);
		}
		else if (ends("ies", target))          // IES  -> I 
		{
			strncpy(temp, target, strlen(target)-2);
			if(strlen(temp) != 0)
				strcpy(target, temp);
		}
		else if (k>=1 && (target[k-1] != 's'))   			 // S    ->   ,but SS   -> SS  	
		{
			strncpy(temp, target, strlen(target)-1);
			if(strlen(temp) != 0)
				strcpy(target, temp);
		}
	}
	char temp[100] = "";
	if (ends("eed", target)) {                 //(m>0) EED -> EE   
		if (m(target) > 0)
		{
			strncpy(temp, target, strlen(target)-1);
			if(strlen(temp) != 0)
				strcpy(target, temp);	
		}
	} 
	else if ((ends("ed", target) || ends("ing", target)) && vowelinstem(target)) {    //(*v*) ED  ->  , ING ->      and 1(c)
		if (ends("ed", target))
		{
			strncpy(temp, target, strlen(target)-2);
			if(strlen(temp) != 0)
				strcpy(target, temp);	
		}
		if (ends("ing", target))
		{
			strncpy(temp, target, strlen(target)-3);
			if(strlen(temp) != 0)
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
	
	char temp[100] = "";
	switch (target[strlen(target)-2]) {
		case 'a':
			if (ends("ational", target)) {strncpy(temp, target, strlen(target)-7); if(strlen(temp) != 0) strcpy(target, temp); strcat(target, "ate"); break; }
			if (ends("tional", target)) {strncpy(temp, target, strlen(target)-6); if(strlen(temp) != 0) strcpy(target, temp); strcat(target, "tion"); break; }
			break;
		case 'c':
			if (ends("enci", target)) {strncpy(temp, target, strlen(target)-4); if(strlen(temp) != 0) strcpy(target, temp); strcat(target, "ence"); break; }
			if (ends("anci", target)) {strncpy(temp, target, strlen(target)-4); if(strlen(temp) != 0) strcpy(target, temp); strcat(target, "ance"); break; }
		break;
		case 'e':
			if (ends("izer", target)) {strncpy(temp, target, strlen(target)-4); if(strlen(temp) != 0) strcpy(target, temp); strcat(target, "ize"); break; }
			break;
		case 'l':
			if (ends("bli", target)) {strncpy(temp, target, strlen(target)-3); if(strlen(temp) != 0) strcpy(target, temp); strcat(target, "ble"); break; }
			if (ends("alli", target)) {strncpy(temp, target, strlen(target)-4); if(strlen(temp) != 0) strcpy(target, temp); strcat(target, "al"); break; }
			if (ends("entli", target)) {strncpy(temp, target, strlen(target)-5); if(strlen(temp) != 0) strcpy(target, temp); strcat(target, "ent"); break; }
			if (ends("eli", target)) {strncpy(temp, target, strlen(target)-3); if(strlen(temp) != 0) strcpy(target, temp); strcat(target, "e"); break; }
			if (ends("ousli", target)) {strncpy(temp, target, strlen(target)-5); if(strlen(temp) != 0) strcpy(target, temp); strcat(target, "ous"); break; }
			break;
		case 'o':
			if (ends("ization", target)) {strncpy(temp, target, strlen(target)-7); if(strlen(temp) != 0) strcpy(target, temp); strcat(target, "ize"); break; }
			if (ends("ation", target)) {strncpy(temp, target, strlen(target)-5); if(strlen(temp) != 0) strcpy(target, temp); strcat(target, "ate"); break; }
			if (ends("ator", target)) {strncpy(temp, target, strlen(target)-4); if(strlen(temp) != 0) strcpy(target, temp); strcat(target, "ate"); break; }
			break;
		case 's':
			if (ends("alism", target)) {strncpy(temp, target, strlen(target)-5); if(strlen(temp) != 0) strcpy(target, temp); strcat(target, "al"); break; }
			if (ends("iveness", target)) {strncpy(temp, target, strlen(target)-7); if(strlen(temp) != 0) strcpy(target, temp); strcat(target, "ive"); break; }
			if (ends("fulness", target)) {strncpy(temp, target, strlen(target)-7); if(strlen(temp) != 0) strcpy(target, temp); strcat(target, "ful"); break; }
			if (ends("ousness", target)) {strncpy(temp, target, strlen(target)-7); if(strlen(temp) != 0) strcpy(target, temp); strcat(target, "ous"); break; }
			break;
		case 't':
			if (ends("aliti", target)) {strncpy(temp, target, strlen(target)-5); if(strlen(temp) != 0) strcpy(target, temp); strcat(target, "al"); break; }
			if (ends("iviti", target)) {strncpy(temp, target, strlen(target)-5); if(strlen(temp) != 0) strcpy(target, temp); strcat(target, "ive"); break; }
			if (ends("biliti", target)) {strncpy(temp, target, strlen(target)-6); if(strlen(temp) != 0) strcpy(target, temp); strcat(target, "ble"); break; }
			break;
		case 'g':
			if (ends("logi", target)) {strncpy(temp, target, strlen(target)-1); if(strlen(temp) != 0) strcpy(target, temp); break; }
			break;
		default :
			break;
	}
	return;
}

void step4(char target[]) {
	if (m(target) == 0)
		return;
	
	char temp[100] = "";	
	switch (target[strlen(target)-1]) {
		case 'e':
			if (ends("icate", target)) {strncpy(temp, target, strlen(target)-3); if(strlen(temp) != 0) strcpy(target, temp); break; }
			if (ends("ative", target)) {strncpy(temp, target, strlen(target)-5); if(strlen(temp) != 0) strcpy(target, temp); break; }
			if (ends("alize", target)) {strncpy(temp, target, strlen(target)-3); if(strlen(temp) != 0) strcpy(target, temp); break; }
			break;
		case 'i':
			if (ends("iciti", target)) {strncpy(temp, target, strlen(target)-3); if(strlen(temp) != 0) strcpy(target, temp); break; }
			break;
		case 'l':
			if (ends("ical", target)) {strncpy(temp, target, strlen(target)-2); if(strlen(temp) != 0) strcpy(target, temp); break; }
			if (ends("ful", target)) {strncpy(temp, target, strlen(target)-3); if(strlen(temp) != 0) strcpy(target, temp); break; }
			break;
		case 's':
			if (ends("ness", target)) {strncpy(temp, target, strlen(target)-4); if(strlen(temp) != 0) strcpy(target, temp); break; }
			break;
	}
	return;
}

void step5(char target[]) {
	if (m(target) < 2)
		return;
	
	char temp[100] = "";    //have to initialize!!!
	switch (target[strlen(target)-2]) {
		case 'a':
			if (ends("al", target)) {strncpy(temp, target, strlen(target)-2); if(strlen(temp) != 0) strcpy(target, temp); break; }
		case 'c':
			if (ends("ance", target)) {strncpy(temp, target, strlen(target)-4); if(strlen(temp) != 0) strcpy(target, temp); break; }
			if (ends("ence", target)) {strncpy(temp, target, strlen(target)-4); if(strlen(temp) != 0) strcpy(target, temp); break; }
		case 'e':
			if (ends("er", target)) {strncpy(temp, target, strlen(target)-2); if(strlen(temp) != 0) strcpy(target, temp); break; }
		case 'i':
			if (ends("ic", target)) {strncpy(temp, target, strlen(target)-2); if(strlen(temp) != 0) strcpy(target, temp); break; }
		case 'l':
			if (ends("able", target)) {strncpy(temp, target, strlen(target)-4); if(strlen(temp) != 0) strcpy(target, temp); break; }
			if (ends("ible", target)) {strncpy(temp, target, strlen(target)-4); if(strlen(temp) != 0) strcpy(target, temp); break; }
		case 'n':
			if (ends("ant", target)) {strncpy(temp, target, strlen(target)-3); if(strlen(temp) != 0) strcpy(target, temp); break; }
			if (ends("ement", target)) {strncpy(temp, target, strlen(target)-5); if(strlen(temp) != 0) strcpy(target, temp); break; }
			if (ends("ment", target)) {strncpy(temp, target, strlen(target)-4); if(strlen(temp) != 0) strcpy(target, temp); break; }
			if (ends("ent", target)) {strncpy(temp, target, strlen(target)-3); if(strlen(temp) != 0) strcpy(target, temp); break; }
		case 'o':
			if (ends("ion", target) && ((strlen(target)-4) >= 0) && (target[strlen(target)-4] == 's' || target[strlen(target)-4] == 't')) 
				{strncpy(temp, target, strlen(target)-3); if(strlen(temp) != 0) strcpy(target, temp); break; }
			if (ends("ou", target)) {strncpy(temp, target, strlen(target)-2); if(strlen(temp) != 0) strcpy(target, temp); break; }
		case 's':
			if (ends("ism", target)) {strncpy(temp, target, strlen(target)-3); if(strlen(temp) != 0) strcpy(target, temp); break; }
		case 't':
			if (ends("ate", target)) {strncpy(temp, target, strlen(target)-3); if(strlen(temp) != 0) strcpy(target, temp); break; }
			if (ends("iti", target)) {strncpy(temp, target, strlen(target)-3); if(strlen(temp) != 0) strcpy(target, temp); break; }
		case 'u':
			if (ends("ous", target)) {strncpy(temp, target, strlen(target)-3); if(strlen(temp) != 0) strcpy(target, temp); break; }
		case 'v':
			if (ends("ive", target)) {strncpy(temp, target, strlen(target)-3); if(strlen(temp) != 0) strcpy(target, temp); break; }
		case 'z':
			if (ends("ize", target)) {strncpy(temp, target, strlen(target)-3); if(strlen(temp) != 0) strcpy(target, temp); break; }
		default:
			return;
	}
	return;
}

void step6(char target[]) {
			
	char temp[100] = "";
	strncpy(temp, target, strlen(target)-1);
	
	char tempt[100] = "";
	if (m(target)>1 && target[strlen(target)-1] == 'e') 
	{
		strncpy(tempt, target, strlen(target)-1);
		if(strlen(temp) != 0) 
			strcpy(target, tempt);
	}
	if (m(target)==1 && target[strlen(target)-1] == 'e' && !cvc(temp) && strlen(temp)>=3) 
	{
		strncpy(tempt, target, strlen(target)-1); 
		if(strlen(temp) != 0)
			strcpy(target, tempt);
	}
	if (m(target)>1 && target[strlen(target)-1] != 'L' && (target[strlen(target)-1] == target[strlen(target)-2]))
	{
		strncpy(tempt, target, strlen(target)-1); 
		if(strlen(temp) != 0)
			strcpy(target, tempt);
	}
}

double cosine(string docX, string docY){
	
	
	ifstream doc1("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM_TFIDF\\"+docX);
	ifstream doc2("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM_TFIDF\\"+docY);
	map<string, double> dict1;
	map<string, double> dict2;
	string line;
	char *t, *s;
	getline(doc1, line);
	getline(doc2, line);
	char delim[] = " ";
	//cout<<endl;
	while (getline(doc1, line)){
	    t = strtok ((char*)line.c_str(), delim);   //parse with delim
	    while (t != NULL){
	    	string term(t);
			s = strtok(NULL, delim);   //t pointing to the next delimiter position
			double ans = atof(s);
			//cout<<term<<"\t"<<s<<endl;
			dict1[term] = ans;
			t = strtok(NULL, delim);
	    }
	}
	//cout<<endl;
	//cout<<dict1.find("accept")->second<<dict1.find("thi")->second<<dict1.find("strike")->second+dict1.find("thi")->second;
	while (getline(doc2,line)){
	    t = strtok ((char*)line.c_str(), delim);   //parse with delim
	    while (t != NULL){
	    	string term(t);
			s = strtok(NULL, delim);   //t pointing to the next delimiter position
			double ans = atof(s);
			//cout<<term<<"\t"<<s<<endl;
			dict2[term] = ans;
			t = strtok(NULL, delim);
	    }
	} 
	
	double sum = 0, unit1 = 0, unit2 = 0;
	map<string, double>::iterator it1;
	map<string, double>::iterator it2;


	map<string, double>::iterator it;
	for(it = dict1.begin(); it != dict1.end(); it++){
		if(dict2.find(it->first) != dict2.end()){
			//std::cout<<(*it).first<<" "<<(*it).second<<endl;
			//std::cout<<(*dict2.find(it->first)).first<<" "<<(*dict2.find(it->first)).second<<endl;
			sum += (*it).second * (dict2.find(it->first)->second);
		}
	}
	//cout<<sum;
	return sum;
}

double cosine(std::map<string, double> first1, std::map<string, double> second1)
{
	double sum = 0;
	map<string, double>::iterator it;
	for(it = first1.begin(); it != first1.end(); it++){
		if(second1.find(it->first) != second1.end()){
			sum += (*it).second * (second1.find(it->first)->second);
		}
	}
	return sum;
}

void getTFIDF(string doc, map<string, Arr5> dict, double N){
	
	ifstream docM("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM_OUT\\"+doc);
	ofstream outfile ("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM_TFIDF\\Doc"+doc);
	map<string, double> dict1;
	string line;
	char *t, *s;
	getline(docM, line);
	char delim[] = " ";
	while (getline(docM, line)){
	    t = strtok ((char*)line.c_str(), delim);   //parse with delim
	    while (t != NULL){
	    	string term(t);
			s = strtok(NULL, delim);   //t pointing to the next delimiter position
			double ans = atof(s);
			dict1[term] = ans;
			t = strtok(NULL, delim);
	    }
	}
	
	map<string, double>::iterator it;
	map<string, double>::iterator it1;
	map<string, double>::iterator it2;
	double sum = 0, unit1 = 0;
	outfile<<std::left<<"The size of document terms is:  "<<dict1.size()<<endl;
	

	for(it = dict1.begin(); it != dict1.end(); it++){
		string temp = (*it).first;
		
		//cout<<temp<<" "<<(*it).second<<" "<<log10(N/((*dict.find(it->first)).second.num[2]))<<" "<<((*dict.find(it->first)).second.num[2])<<" "<<N<<endl;
		dict1[(*it).first] = (*it).second * log10(N/((*dict.find(it->first)).second.num[2]));
		//cout<<(*dict1.find(it->first)).second<<endl;
	}	
	for(it1 = dict1.begin(); it1 != dict1.end(); it1++){
		unit1 += (*it1).second * (*it1).second;
		cout<<(*it1).second<<endl;
	}
	unit1 = sqrt(unit1);
	cout<<doc<<"unit = "<<unit1<<endl;
	for(it2 = dict1.begin(); it2 != dict1.end(); it2++){

		dict1[(*it2).first] = (*it2).second /unit1;
		//cout<<(*dict1.find(it->first)).second<<endl;
		outfile<<std::left<<setw(70)<<((*dict.find(it2->first)).second.num[1]);
		outfile<<std::left<<setw(70)<<(*it2).second<<endl;
	}
}

void TrainMultinomialNB(int classes[][16], int num[13])
{
	map<string, double> total;
	for(int i=0; i<13; i++){
		for(int j=1; j<16; j++){
			string doc = std::to_string(classes[i][j]);
			ifstream docM("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM_OUT\\"+doc+".txt");
			string line;
			char *t, *s;
			getline(docM, line);
			char delim[] = " ";
			while (getline(docM, line)){
		    t = strtok ((char*)line.c_str(), delim);   //parse with delim
		    while (t != NULL){
		    	string term(t);
				s = strtok(NULL, delim);   //t pointing to the next delimiter position
				double ans = atof(s);
				if(total.find(term) == total.end())
					total[term] = 1;
				t = strtok(NULL, delim);
		    }
			}
		}
	}
	
	for(int i=0; i<13; i++){
		map<string, double> dict1;
		int distinct_num = 0, total_num = 0;
		string clas = std::to_string(i+1);
		ofstream outfile ("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM_Class\\"+clas+".txt");
		
		map<string, double> featuredict;
		string doc = std::to_string(i+1);
		ifstream docM("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM_CLASS\\fs_"+doc+".txt");
		string line;
		char *t, *s;
		getline(docM, line);
		char delim[] = " ";
		while (getline(docM, line)){
	    t = strtok ((char*)line.c_str(), delim);   //parse with delim
	    while (t != NULL){
	    	string term(t);
			s = strtok(NULL, delim);   //t pointing to the next delimiter position
			double ans = atof(s);
			featuredict[term] = ans;
			t = strtok(NULL, delim);
	    }
		}
		
		
		for(int j=1; j<16; j++){
			string doc = std::to_string(classes[i][j]);
			ifstream docM("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM_OUT\\"+doc+".txt");
			string line;
			char *t, *s;
			getline(docM, line);
			char delim[] = " ";
			while (getline(docM, line)){
		    t = strtok ((char*)line.c_str(), delim);   //parse with delim
		    while (t != NULL){
		    	string term(t);
				s = strtok(NULL, delim);   //t pointing to the next delimiter position
				double ans = atof(s);
				if(dict1.find(term) == dict1.end())
				{
					dict1[term] = ans;
					distinct_num++;
					total_num++;
				}
				else
				{
					dict1[term] += ans;
					total_num++;
				}
				t = strtok(NULL, delim);
		    }
			}
		}
		outfile<<std::left<<setw(70)<<"term"<<setw(70)<<"prob"<<endl;
		map<string, double>::iterator it;
		for(it = dict1.begin(); it != dict1.end(); it++){
			if(featuredict.find((*it).first) != featuredict.end())
			{
				outfile<<std::left<<setw(70)<<(*it).first;
				outfile<<std::left<<setw(70)<<((*it).second+1)/(total_num+total.size()-1)<<endl;
			}
		}
		outfile.close();
		num[i] = total_num+total.size()-1;
	}
}

int ApplyMultinomialNB(string d, int num[13])
{
	int result = -9999999;
	int class_result = 0;
	map<string, int> dict1;
	
	ifstream docM("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM_OUT\\"+d);
	string line;
	char *m, *n;
	getline(docM, line);
	char delim[] = " ";
	while (getline(docM, line)){
    m = strtok ((char*)line.c_str(), delim);   //parse with delim
    while (m != NULL){
    	string term(m);
		n = strtok(NULL, delim);   //t pointing to the next delimiter position
		double ans = atoi(n);
		dict1[term] = ans;
		m = strtok(NULL, delim);
    }
	}
	
	map<string, double> dictT;
	for(int i=1; i<=13; i++)
	{
		double temp = 0;
		string doc = std::to_string(i);
		ifstream docM("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM_Class\\"+doc+".txt");
		string line;
		char *t, *s;
		getline(docM, line);
		char delim[] = " ";
		while (getline(docM, line)){
	    t = strtok ((char*)line.c_str(), delim);   //parse with delim
	    while (t != NULL){
	    	string term(t);
			s = strtok(NULL, delim);   //t pointing to the next delimiter position
			double ans = atof(s);
			dictT[term] = ans;
			t = strtok(NULL, delim);
	    }
		}
	}
		
	for(int i=1; i<=13; i++)
	{
		map<string, double> dict2;
		double temp = 0;
		string doc = std::to_string(i);
		ifstream docM("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM_Class\\"+doc+".txt");
		string line;
		char *t, *s;
		getline(docM, line);
		char delim[] = " ";
		while (getline(docM, line)){
	    t = strtok ((char*)line.c_str(), delim);   //parse with delim
	    while (t != NULL){
	    	string term(t);
			s = strtok(NULL, delim);   //t pointing to the next delimiter position
			double ans = atof(s);
			dict2[term] = ans;
			t = strtok(NULL, delim);
	    }
		}
		map<string, int>::iterator it;
		for(it = dict1.begin(); it != dict1.end(); it++){
			if(dict2.find((*it).first) == dict2.end() && (dictT.find((*it).first) != dict2.end()))
				temp  = temp +  (*it).second*log(1.0/num[i-1]);
			else if (dict2.find((*it).first) != dict2.end() )
				temp  = temp + (*it).second*log((dict2[(*it).first]));
			else;
			//cout<<"****"<<(*it).second<<" "<<(*it).first<<" "<<(pow((*it).second, (dict1[(*it).first])))<<"  "<<temp<<endl;
			/*if(d=="129.txt")
				cout<<(*it).first<<"   "<<temp<<endl;*/
		}
		//if(d=="127.txt")

		//cout<<temp*(1.0/13)<<" "<<result<<endl;
		if(temp*(1.0/13)>result)
		{
			result = temp*(1.0/13);
			class_result = i;
		}
		//cout<<"文章"<<d<<" "<<i<<" "<<result<<endl;
	}
	return class_result;	
	
}

void SelectFeatures(int classes[][16])
{
	map<string, double> dict1;
	int total = 0;
	for(int i=0; i<13; i++){
		for(int j=1; j<16; j++){
			string doc = std::to_string(classes[i][j]);
			ifstream docM("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM_OUT\\"+doc+".txt");
		string line;
		char *t, *s;
		getline(docM, line);
		char delim[] = " ";
		while (getline(docM, line)){
		    t = strtok ((char*)line.c_str(), delim);   //parse with delim
		    while (t != NULL){
		    	string term(t);
				s = strtok(NULL, delim);   //t pointing to the next delimiter position				
				if(dict1.find(term) == dict1.end())
				{
					dict1[term] = 1;
					//cout<<term<<endl;	
				}
				else
					dict1[term] += 1;
				t = strtok(NULL, delim);
		    }
		}
	}
	}
	ofstream outfile ("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM_Class\\merge.txt");
	outfile<<std::left<<setw(70)<<"term"<<setw(70)<<"total_num"<<endl;
	map<string, double>::iterator it;
	for(it = dict1.begin(); it != dict1.end(); it++){
		outfile<<std::left<<setw(70)<<(*it).first;
		outfile<<std::left<<setw(70)<<(*it).second<<endl;
	}
	
	for(int i=0; i<13; i++){
		map<string, Arr5> score;
		for(int j=1; j<16; j++){
			string doc = std::to_string(classes[i][j]);
			ifstream docM("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM_OUT\\"+doc+".txt");
		string line;
		char *t, *s;
		getline(docM, line);
		char delim[] = " ";
		while (getline(docM, line)){
		    t = strtok ((char*)line.c_str(), delim);   //parse with delim
		    while (t != NULL){
		    	string term(t);
				s = strtok(NULL, delim);   //t pointing to the next delimiter position
				
				if(score.find(term) == score.end())
				{
					score[term] = {1,0,0,0,0};
				}
				else
					score[term].num[0]++;
				
				t = strtok(NULL, delim);
		    }
		}
	}
	string now = std::to_string(i+1);
	ofstream outfile ("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM_Class\\fs_"+now+".txt");
	map<string, double> D2V;
	map<string, double> D2V2;
	map<string, Arr5>::iterator it1;
	for(it1 = score.begin(); it1 != score.end(); it1++){
		double expected_f[4];
		double chi_score = 0;
		score[(*it1).first].num[1] = 15-score[(*it1).first].num[0];
		score[(*it1).first].num[2] = dict1[(*it1).first] - score[(*it1).first].num[0];
		score[(*it1).first].num[3] = 180 - score[(*it1).first].num[2];
		expected_f[0] = 195.0*(15.0/195)*(dict1[(*it1).first]/195.0);
		expected_f[1] = 195.0*(15.0/195)*((195.0-dict1[(*it1).first])/195.0);
		expected_f[2] = 195.0*(180.0/195)*(dict1[(*it1).first]/195.0);
		expected_f[3] = 195.0*(180.0/195)*((195.0-dict1[(*it1).first])/195.0);
		chi_score = pow(score[(*it1).first].num[0]-expected_f[0], 2)/(expected_f[0]) + pow(score[(*it1).first].num[1]-expected_f[1], 2)/(expected_f[1]) + 
			pow(score[(*it1).first].num[2]-expected_f[2], 2)/(expected_f[2]) + pow(score[(*it1).first].num[3]-expected_f[3], 2)/(expected_f[3]);
		double MI = log2((score[(*it1).first].num[0]/195.0)/((15.0/195)*(dict1[(*it1).first]/195)));
		//MI = MI/(-log2((score[(*it1).first].num[0]/195.0)));
		double EMI = score[(*it1).first].num[0]*log2(score[(*it1).first].num[0]/(15*dict1[(*it1).first]))
		+score[(*it1).first].num[1]*log2(score[(*it1).first].num[1]/(15*(195.0-dict1[(*it1).first])))
		+score[(*it1).first].num[2]*log2(score[(*it1).first].num[2]/(180.0*dict1[(*it1).first]))
		+score[(*it1).first].num[3]*log2(score[(*it1).first].num[3]/(180.0*(195.0-dict1[(*it1).first])));
		if((score[(*it1).first].num[0]>6||score[(*it1).first].num[2]<1) && MI>1.5 && ((score[(*it1).first].num[0]-expected_f[0])+(score[(*it1).first].num[3]-expected_f[3])-
		(score[(*it1).first].num[1]-expected_f[1])-(score[(*it1).first].num[2]-expected_f[2]))>22)
			D2V[(*it1).first] = chi_score;
		else
			D2V[(*it1).first] = -chi_score;
		D2V2[(*it1).first] = MI;
		//outfile<<std::left<<setw(70)<<(*it1).first;
		/*outfile<<std::left<<setw(70)<<D2V[(*it1).first]<<"    "<<score[(*it1).first].num[0]<<"    "<<score[(*it1).first].num[1]
		<<"    "<<score[(*it1).first].num[2]<<"    "<<score[(*it1).first].num[3]<<"    "<<expected_f[0]<<"    "<<expected_f[1]
		<<"    "<<expected_f[2]<<"    "<<expected_f[3]<<"    "<<MI<<"     "<<EMI<<endl;*/
	}
	
	//&& ((score[(*it1).first].num[1]-expected_f[1])+(score[(*it1).first].num[2]-expected_f[2]))<0 && (expected_f[0]>1 || chi_score * expected_f[0]>20)
	//&&((score[(*it1).first].num[0]-expected_f[0])+(score[(*it1).first].num[3]-expected_f[3]))>0 && ((score[(*it1).first].num[1]-expected_f[1])+(score[(*it1).first].num[2]-expected_f[2])<0)
	vector<pair<string,double> > vec (D2V.begin(), D2V.end());
	sort(vec.begin(),vec.end(),comp_by_value);
	vector<pair<string,double> >::iterator it5;
    int count = 0;
    for(it5 = vec.begin(); it5!= vec.end() && count<45; ++it5){
    	if(D2V[(*it5).first]>20){
			// && (D2V2[(*it5).first] > 2) && count<50
			outfile<<std::left<<setw(70)<<(*it5).first;
			outfile<<std::left<<setw(70)<<D2V[(*it5).first]<<endl;
        	count++;
        	total++;
    	}
    	
    }
	//printVec(vec);
    //cout<<endl<<endl;
	}
	cout<<total<<endl;

	outfile.close();
}

void HAC(int cluster_num)
{
	bool I[1096];
	int N[1096];
	list<pair<int, int>> A;
	std::vector<std::map<string,double>> vecOfMaps;
	double **C = new double*[1096];
	double max = 0;
	int first = 0, second = 0;
	map<string, double> zero;
	vecOfMaps.push_back(zero);
	for(int i=1; i<=1095; i++)
	{
		int count = 0;
		ifstream docM("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM_TFIDF\\Doc"+to_string(i)+".txt");
		map<string, double> dict1;
		string line;
		char *t, *s;
		getline(docM, line);
		char delim[] = " ";
		while (getline(docM, line)){
		    t = strtok ((char*)line.c_str(), delim);   //parse with delim
		    while (t != NULL){
		    	string term(t);
				s = strtok(NULL, delim);   //t pointing to the next delimiter position
				double ans = atof(s);
				dict1[term] = ans;
				t = strtok(NULL, delim);
		    }
		    count++;
		}
		vecOfMaps.push_back(dict1);
		N[i] = 1;
	}

	/*map<string, double>::iterator it;
	for(it = vecOfMaps.at(5).begin(); it != vecOfMaps.at(5).end(); it++){
		cout<<(*it).first<<"    "<<(*it).second<<endl;
	}*/

	for(int i=1; i<=1095; i++)
	{	
		C[i] = new double[1096];
		for(int j=1; j<=1095; j++)
		{
			string a = "Doc"+to_string(i)+".txt", b = "Doc"+to_string(j)+".txt";
			C[i][j] = cosine(a, b);
			I[i] = 1;
			//cout<<"Similarity of "<<a<<" & "<<b<<" is "<<C[i][j]<<endl;
		}
	}
    
	for(int k=1; k<=(1095-cluster_num); k++)  //跑N-1次直到結束 
	{
		max = 0, first = 0, second = 0; 
		for(int i=1; i<=1095; i++)
		{	
			for(int j=1; j<=1095; j++)
			{
				if(C[i][j] > max && ((i != j) && (I[i]==1 && I[j]==1))){
					first = i;
					second = j;
					max = C[i][j];
				}
				/*if((i != j) && (I[i]==1 && I[j]==1))
					cout<<i<<" "<<j<<" "<<C[i][j]<<endl;*/
			}
		}

		dictMerge(first, second, N, vecOfMaps);  //merge second to first
		
		//test
		ofstream outfile ("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\IRTM_Clustering\\"+to_string(first)+"and"+to_string(second)+".txt");
		map<string, double>::iterator ittest;
		outfile<<"Total document : "<<N[first]<<endl;
		for(ittest = vecOfMaps.at(first).begin(); ittest != vecOfMaps.at(first).end(); ittest++){
			outfile<<std::left<<setw(70)<<(*ittest).first;
			outfile<<std::left<<setw(70)<<(*ittest).second<<endl;
		}
		
		
		A.push_back(make_pair(first,second));
		//cout<<"first: "<<first<<"   second: "<<second<<endl; 
		for(int g=1; g<=1095; g++)
		{
			C[first][g] = cosine(vecOfMaps.at(first), vecOfMaps.at(g));
			C[g][first] = cosine(vecOfMaps.at(g), vecOfMaps.at(first));	
		}
		I[second] = 0; 
    }
	


	int record_cluster[1096];
	for(int i=1; i<=1095; i++)
		record_cluster[i] = i;
	bool exist_cluster[1096];
	for(int i=1; i<=1095; i++)
		exist_cluster[i] = 1;
		
	ofstream outfile ("C:\\Users\\Mark\\Desktop\\大五\\資訊檢索\\clustering_answer\\"+to_string(cluster_num)+".txt");
	cout<<"Merge list :"<<endl; 
	for (list<pair<int, int>>::iterator ir =A.begin(); ir!=A.end();ir++) { 
    	cout << "<"<<(*ir).first << ", " << (*ir).second<<">"<<endl; 
    	if(record_cluster[(*ir).first] != 0 && record_cluster[(*ir).second] != 0){
			int temp = record_cluster[(*ir).second];
			for(int i=1; i<=1095; i++){
				if(record_cluster[i] == temp)
					record_cluster[i] = record_cluster[(*ir).first];
			}
			exist_cluster[temp] = 0;
		}
	}
	
	for(int i=1; i<=1095; i++){
		if(exist_cluster[i] == 1){
			for(int j=1; j<=1095; j++){
				if(record_cluster[j] == i){
					outfile<<j<<endl;
				}
			}
			outfile<<endl;
		}		
	}	
}

void dictMerge(int first1, int second1, int N[1096], std::vector<std::map<string,double>>& vecOfMaps)
{
	map<string, double>::iterator it1;
	for(it1 = vecOfMaps.at(first1).begin(); it1 != vecOfMaps.at(first1).end(); it1++){
		(*it1).second = N[first1]*(*it1).second;
	}
	map<string, double>::iterator it;
	for(it = vecOfMaps.at(second1).begin(); it != vecOfMaps.at(second1).end(); it++){
		if(vecOfMaps.at(first1).find((*it).first) == vecOfMaps.at(first1).end())
		{
			vecOfMaps.at(first1)[(*it).first] = N[second1]*(*it).second;
		}
		else
		{
			vecOfMaps.at(first1)[(*it).first] += N[second1]*(*it).second;
		}
	}
	map<string, double>::iterator it2;
	for(it2 = vecOfMaps.at(first1).begin(); it2 != vecOfMaps.at(first1).end(); it2++){
		(*it2).second = (*it2).second/(N[first1] + N[second1]);
	}
	N[first1] = N[first1] + N[second1];
}

