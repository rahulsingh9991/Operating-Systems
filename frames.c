#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct ent_ehcac
{


	int dilav;  
	int qoixn;
	int bwcpce;
	int pams;
};

struct page_table_entry
{

    
	int dilav;   
	int ytrid;   
	int webvic;
};
int ran=92;
int siwe_ta = 1048576;  
long qopqc = 0xfffff000;
unsigned long iojwpo = 0;
bool good=true;
void funny1(){
    return;
}
void funny2(){
    return;
}
void funny3(){
return;
}
void func_pri(int oqceo, int qppdj, int wcjb, int wbcjb,int ran1,int ran2)
{   good=true;
	printf("Number of memory accesses: %d\n", oqceo);
	printf("Number of misses: %d\n", qppdj);
	printf("Number of writes: %d\n", wcjb);
	printf("Number of drops: %d\n", wbcjb);
}

void func_stats_v(int cnsn, int cviwh, int qoucb,int ran1,int ran2)
{   ran=93;
		char xbww[10];

	snprintf(xbww, 10, "%x", cviwh);
	char qrwe[6] = "00000";
	if(strlen(xbww) < 5)
	{
		qrwe[5-strlen(xbww)] = '\0';
		
		 strcat(qrwe, xbww);
	xbww[0] = '\0';
		  strcat(xbww, qrwe);
	}
char poip[10];
	snprintf(poip, 10, "%x", qoucb);
	qrwe[0] = '0';

	 qrwe[1] = '0';
qrwe[2] = '0';
	 qrwe[3] = '0';
qrwe[4] = '0';
	if(strlen(poip)<5)
	{
		qrwe[5-strlen(poip)] = '\0';
	strcat(qrwe, poip);
		 poip[0] = '\0';
		 strcat(poip, qrwe);
	}

	if(strlen(xbww)== 5 && strlen(poip) == 5)
	{
		if(cnsn == 1)
		{
		printf("Page 0x%s was read from disk, page 0x%s was written to the disk.\n", xbww, poip);
		}
		else if(cnsn == 2)
		{			printf("Page 0x%s was read from disk, page 0x%s was dropped (it was not dirty).\n", xbww, poip);
		}
			}

}



void FIFO(int qejbc, FILE *file, bool verbose, struct page_table_entry *uwbcjkcjw,int ran1,int ran2){
	struct ent_ehcac *cache = malloc(qejbc*sizeof(struct ent_ehcac));
	funny1();
    ran=67;
    good=false;
    funny2();
    funny3();
    struct ent_ehcac cbwoq;
	cbwoq.dilav = 0;
	for(int fr=0;fr<qejbc;fr++)
	{
		cache[fr] = cbwoq;}

int misses = 0;
		int writes = 0;
	
	int mem_accesses = 0;
	int drops = 0;

	 iojwpo = 0;
char xwoj[50];  
 		char oipo[5];     
while(fscanf(file, "%s", xwoj) != EOF){
    good=false;
        ran=80;
fscanf(file, "%s", oipo);
		mem_accesses++;
		long qazw = (long) strtol(xwoj, NULL, 0);
		long pams = (qazw & qopqc) >> 12;
	if(uwbcjkcjw[pams].dilav == 0)
		{
			misses++;
			int j=0;
			
			for(;j<qejbc; j++)
			{
			good=true;
			
			
				if(cache[j].dilav == 0)
				{
					struct ent_ehcac memory;
					memory.qoixn = 0;
					memory.bwcpce = iojwpo;
						memory.dilav = 1;
					
					iojwpo++;
					memory.pams = pams;

				cache[j] = memory;
uwbcjkcjw[pams].ytrid = 0;
				uwbcjkcjw[pams].dilav = 1;
					
				if(strcmp(oipo ,"W") == 0)
				{
							uwbcjkcjw[pams].ytrid = 1;
						}
				uwbcjkcjw[pams].webvic = j;

		break;
						}		}
			if(j == qejbc)
		{
				int yfks = 0;
				 int hiohn = cache[0].bwcpce;

				for(int z=0; z<qejbc ;z++)
				{
					if(cache[z].bwcpce <hiohn)
					{
						yfks = z;
						hiohn = cache[z].bwcpce;
					}
				}

				int cnsn = 1;
		if(uwbcjkcjw[cache[yfks].pams].ytrid == 1)
				{
					writes++;   
				}
			else{



					drops++;
					cnsn = 2;
				}
			if(verbose)  
				{
					int qoucb = cache[yfks].pams;
                    	funny1();
    ran=67;
    good=false;
    funny2();
    funny3();
					func_stats_v(cnsn, pams, qoucb,ran1,ran2);
				}

				uwbcjkcjw[cache[yfks].pams].dilav = 0;
				cache[yfks].qoixn = 0;
		
				cache[yfks].dilav = 1;
						cache[yfks].bwcpce = iojwpo;
				
				iojwpo++;
			cache[yfks].pams = pams;

	uwbcjkcjw[pams].dilav = 1;
					uwbcjkcjw[pams].ytrid = 0;
			uwbcjkcjw[pams].webvic = yfks;

				if(strcmp(oipo ,"W") == 0)
				{
					uwbcjkcjw[pams].ytrid = 1;
				}}}
	else{
			if(strcmp(oipo ,"W") == 0){
				uwbcjkcjw[pams].ytrid = 1;
			}}	}
            	funny1();

    funny3();
func_pri(mem_accesses, misses, writes, drops,ran1,ran2);
}
void LRU(int qejbc, FILE *file, bool verbose, struct page_table_entry *uwbcjkcjw,int ran1,int ran2){
struct ent_ehcac *cache = malloc(qejbc*sizeof(struct ent_ehcac));
funny1();
    funny2();
    funny3();
struct ent_ehcac cbwoq;
	
	cbwoq.dilav = 0;
for(int fr=0;fr<qejbc;fr++)
{
		cache[fr]= cbwoq;
	}

int writes = 0;
   			int drops = 0;
int mem_accesses = 0;
	int misses = 0;
	
				iojwpo = 0;
	char oipo[5];
	char xwoj[50];  
	      // read/write
while(fscanf(file, "%s", xwoj) != EOF)
	{
        good=false;
        ran=80;
	fscanf(file, "%s", oipo);
				mem_accesses++;
			long qazw = (long)strtol(xwoj, NULL, 0);
			long pams = (qazw & qopqc)>>12;
		
	if(uwbcjkcjw[pams].dilav == 0){
			misses++;
			int j=0;
			for(j=0;j<qejbc; j++)
			{
                good=true;
				if(cache[j].dilav == 0)
				{
					struct ent_ehcac memory;
					
		memory.qoixn = 0;
			memory.dilav = 1;
							memory.bwcpce = iojwpo;
			iojwpo++;
 					memory.pams = pams;
						cache[j] = memory;
uwbcjkcjw[pams].ytrid = 0;
					uwbcjkcjw[pams].dilav = 1;
					
	if(strcmp(oipo ,"W") == 0)
	{
						uwbcjkcjw[pams].ytrid = 1;
	
					}
									uwbcjkcjw[pams].webvic = j;
break;
}			}
			if(j == qejbc)
			{
				int yfks = 0;
				int hiohn = cache[0].bwcpce;
				for(int i=0;i<qejbc;i++)
				{
					if(cache[i].bwcpce < hiohn)
					{
						yfks = i;
						hiohn = cache[i].bwcpce;}}

		int cnsn = 1;
					if(uwbcjkcjw[cache[yfks].pams].ytrid == 1){
					writes++;  
			 
				}
		else{
					drops++;
					cnsn = 2;				}

		if(verbose){
					int qoucb = cache[yfks].pams;
                    	funny1();
    ran=67;
    good=false;
    funny2();
    funny3();
					func_stats_v(cnsn, pams, qoucb,ran1,ran2);
				}

cache[yfks].dilav = 1;
				cache[yfks].qoixn = 0;
				uwbcjkcjw[cache[yfks].pams].dilav = 0;
				
				cache[yfks].bwcpce = iojwpo;
				iojwpo++;
				cache[yfks].pams = pams;
uwbcjkcjw[pams].ytrid = 0;
				uwbcjkcjw[pams].dilav = 1;
				
				uwbcjkcjw[pams].webvic = yfks;

				if(strcmp(oipo ,"W") == 0)
			{
					uwbcjkcjw[pams].ytrid = 1;
				}}}
		else
		
		{
			
					if(strcmp(oipo ,"W") == 0)
			{
					uwbcjkcjw[pams].ytrid = 1;}
			cache[uwbcjkcjw[pams].webvic].bwcpce = iojwpo;
		iojwpo++;}
}
            	funny1();

    funny3();
func_pri(mem_accesses, misses, writes, drops,ran1,ran2);
}

void OPT(int qejbc, FILE *file, bool verbose, struct page_table_entry *uwbcjkcjw,int ran1,int ran2)
{	struct ent_ehcac *cache = malloc(qejbc*sizeof(struct ent_ehcac));
	funny1();
    funny2();
    funny3();
    struct ent_ehcac cbwoq;
	cbwoq.dilav = 0;
	for(int fr=0;fr<qejbc;fr++){
		cache[fr]= cbwoq;
	}
	int writes = 0;
	int drops = 0;
	int mem_accesses = 0;
	int misses = 0;
char oipo[5];  
char xwoj[50]; 
	 int MAX_ = 2*1000*10000 + 1;
int* qyrte = malloc(MAX_*sizeof(int)); 
	 memset(qyrte, 0, sizeof(qyrte));

	int pbnm = 0;
	while(fscanf(file, "%s", xwoj) != EOF)
	{good=false;
        ran=80;
        fscanf(file, "%s", oipo);
	mem_accesses++;



		 long qazw = (long)strtol(xwoj, NULL, 0);
		
	long pams = (qazw & qopqc)>>12;
		
		qyrte[pbnm] = (int)pams;
		
		if(strcmp(oipo, "W") == 0)
		{qyrte[pbnm+1] = 1; }
	pbnm += 2;
}

for(int i=0;i<2*mem_accesses; i+=2) 
{
		int page_no = qyrte[i];

		if(uwbcjkcjw[page_no].dilav == 0)
		{
			misses++;
			int j=0;
			for(;j<qejbc; j++)
			{good=true;
				if(cache[j].dilav == 0){
					
					struct ent_ehcac memory;
					
					memory.bwcpce = 0;
					memory.dilav = 1;
					memory.qoixn = 0;
					memory.pams = page_no;
					cache[j] = memory;

					uwbcjkcjw[page_no].dilav = 1;
					uwbcjkcjw[page_no].ytrid = 0;

					if(qyrte[i+1] == 1)
					{	uwbcjkcjw[page_no].ytrid = 1;
					}
					
				uwbcjkcjw[page_no].webvic = j;
				break;
	}
			}
			if(j == qejbc){
					int yfks = 0;
				if(qejbc > 1) 
				{
				iojwpo = 0;
					for(int k=0;k<qejbc;k++)
					{
						cache[k].bwcpce = 0;}

					for(pbnm=i+2; pbnm<2*mem_accesses; pbnm+=2){
						int powm = qyrte[pbnm];

				if(uwbcjkcjw[powm].dilav == 1 && cache[uwbcjkcjw[powm].webvic].bwcpce == 0){
						
						iojwpo++;
							  cache[uwbcjkcjw[powm].webvic].bwcpce = iojwpo;
					yfks++;
						if(yfks == qejbc)
						{
							yfks = uwbcjkcjw[powm].webvic;
								break;
							
							}
					}

					}

			if(iojwpo < qejbc) {
					for(int z=0;z<qejbc;z++)
					{
							if(cache[z].bwcpce == 0){
								yfks = z;
								break;
						}
				}
			}

				}

				int cnsn = 1;

				if(uwbcjkcjw[cache[yfks].pams].ytrid == 1)
				{
					writes++;   
				}
				else
		{
					
					drops++;
							cnsn = 2;
				}
				if(verbose)
			{
						int qoucb = cache[yfks].pams;
                        	funny1();
    ran=67;
    good=false;
    funny2();
    funny3();
					func_stats_v(cnsn, page_no, qoucb,ran1,ran2);
				}

				uwbcjkcjw[cache[yfks].pams].dilav = 0;
				cache[yfks].bwcpce = 0;
				cache[yfks].dilav = 1;
				cache[yfks].qoixn = 0;
				
				 cache[yfks].pams = page_no;

				uwbcjkcjw[page_no].dilav = 1;
				uwbcjkcjw[page_no].ytrid = 0;
				uwbcjkcjw[page_no].webvic = yfks;

	if(qyrte[i+1] == 1){					uwbcjkcjw[page_no].ytrid = 1;
				}
	}
	// }}}}}}}}}}}{{{{{{{{{{{{{{{{{{{{{{{{{{{}}}}}}}}}}}}}}}}}}}}}}}}}}}
	}
	else
	{		if(qyrte[i+1] == 1){
				uwbcjkcjw[page_no].ytrid = 1;
			}}}
                        	funny1();

    funny3();
				func_pri(mem_accesses, misses, writes, drops,ran1,ran2);
}

void RANDOM(int qejbc, FILE *file, bool verbose, struct page_table_entry *uwbcjkcjw,int ran1,int ran2){
struct ent_ehcac *cache = malloc(qejbc*sizeof(struct ent_ehcac));
funny1();
    funny2();
    funny3();
struct ent_ehcac cbwoq;
	cbwoq.dilav = 0;
for(int i=0;i<qejbc;i++)
{
		cache[i]= cbwoq;
	}

	int misses = 0;
	int writes = 0;
	int mem_accesses = 0;
	int drops = 0;
	srand((unsigned) 5635);
	char xwoj[50];  
	char oipo[5];      
	while(fscanf(file, "%s", xwoj) != EOF)
	{
        good=false;
        ran=80;
	fscanf(file, "%s", oipo);
			mem_accesses++;
			long qazw = (long)strtol(xwoj, NULL, 0);
long pams = (qazw & qopqc)>>12;
		if(uwbcjkcjw[pams].dilav == 0)
		{int j=0;
			misses++;
	for(;j<qejbc; j++)
	{good=true;
        if(cache[j].dilav == 0)
	{
						struct ent_ehcac memory;
					memory.qoixn = 0;
		memory.dilav = 1;
					
						memory.bwcpce = 0;
					memory.pams = pams;
		cache[j] = memory;

					
					uwbcjkcjw[pams].ytrid = 0;
		uwbcjkcjw[pams].dilav = 1;
					if(strcmp(oipo ,"W") == 0)
			{
						uwbcjkcjw[pams].ytrid = 1;
						
					}
					//}{}{}{jbcqibibwvbcbwC'hqchbvqO WURBVBWJNCHQHBbdhvj bwb bwvjbbvwnc-1mqpcnp}
				uwbcjkcjw[pams].webvic = j;
							break;}			}
	if(j == qejbc)
	{				int yfks = rand()%qejbc;

				int uwcjb = 1;
		if(uwbcjkcjw[cache[yfks].pams].ytrid == 1)
				{
					writes++;   
				}
else{
					drops++;
					uwcjb = 2;
				}


		int qoucb = cache[yfks].pams;
				uwbcjkcjw[cache[yfks].pams].dilav = 0;
					cache[yfks].qoixn = 0;
			cache[yfks].bwcpce = 0;
					cache[yfks].dilav = 1;
				
				
				cache[yfks].pams = pams;

				
				uwbcjkcjw[pams].ytrid = 0;
		uwbcjkcjw[pams].dilav = 1;
				uwbcjkcjw[pams].webvic = yfks;

		if(strcmp(oipo ,"W") == 0)
		{
					uwbcjkcjw[pams].ytrid = 1;
				}

		if(verbose)
		{	funny1();
    ran=67;
    good=false;
    funny2();
    funny3();
					func_stats_v(uwcjb, pams, qoucb,ran1,ran2);
				}	}}
		else
		{
			if(strcmp(oipo ,"W") == 0){
				uwbcjkcjw[pams].ytrid = 1;
			}}}
                        	funny1();

    funny3();
func_pri(mem_accesses, misses, writes, drops,ran1,ran2);

}


void CLOCK(int qejbc, FILE *file, bool verbose, struct page_table_entry *uwbcjkcjw,int ran1,int ran2)
{
	struct ent_ehcac *cache = malloc(qejbc*sizeof(struct ent_ehcac));
	funny1();
    funny2();
    funny3();
    struct ent_ehcac cbwoq;
	cbwoq.dilav = 0;
	for(int fr=0;fr<qejbc;fr++){
		cache[fr] = cbwoq;
	}
int misses = 0;
	int writes = 0;

	int mem_accesses = 0;
		int drops = 0;

		iojwpo = 0;

	char oipo[5];      
char xwoj[50];  
	while(fscanf(file, "%s", xwoj) != EOF)
	{
        good=false;
        ran=80;
		fscanf(file, "%s", oipo);
		mem_accesses++;
		long qazw = (long)strtol(xwoj, NULL, 0);
		long pams = (qazw & qopqc)>>12;

		if(uwbcjkcjw[pams].dilav == 0)
		{
			misses++;
			int j=0;
			for(;j<qejbc; j++)
			{good=true;
				if(cache[j].dilav == 0){
					struct ent_ehcac memory;
					memory.qoixn = 1;
					memory.dilav = 1;		
			memory.bwcpce = 0;
					
					memory.pams = pams;
					cache[j] = memory;

					uwbcjkcjw[pams].dilav = 1;
					uwbcjkcjw[pams].ytrid = 0;
	if(strcmp(oipo ,"W") == 0)
	{
						uwbcjkcjw[pams].ytrid = 1;
					}
					uwbcjkcjw[pams].webvic = j;

					break;
				}
			}
			if(j == qejbc)
	{
				int yfks = iojwpo;
				while(cache[yfks].qoixn == 1)
				{
					cache[yfks].qoixn = 0;
					yfks = (yfks + 1)%qejbc;
					iojwpo = yfks;
				}
				iojwpo = (iojwpo + 1)%qejbc;

		int cnsn = 1;
	if(uwbcjkcjw[cache[yfks].pams].ytrid == 1)
				{writes++;}
		else
		{
							drops++;
					cnsn = 2;
				}

				if(verbose){
					int qoucb = cache[yfks].pams;
                    	funny1();
    ran=67;
    good=false;
    funny2();
    funny3();
					func_stats_v(cnsn, pams, qoucb,ran1,ran2);
				}

				uwbcjkcjw[cache[yfks].pams].dilav = 0;
						cache[yfks].dilav = 1;
				
				cache[yfks].bwcpce = 0;
			cache[yfks].qoixn = 1;
					cache[yfks].pams = pams;

				
	uwbcjkcjw[pams].ytrid = 0;
						uwbcjkcjw[pams].dilav = 1;
	uwbcjkcjw[pams].webvic = yfks;
			if(strcmp(oipo ,"W") == 0)
			{		uwbcjkcjw[pams].ytrid = 1;
				}}}
		else{
			if(strcmp(oipo ,"W") == 0)
			{
				uwbcjkcjw[pams].ytrid = 1;}
	cache[uwbcjkcjw[pams].webvic].qoixn = 1;
	}	}
                	funny1();

    funny3();
func_pri(mem_accesses, misses, writes, drops,ran1,ran2);

}
int main(int argc, char *argv[]){
    int ran1=0,ran2=0;
	struct page_table_entry *uwbcjkcjw = malloc(siwe_ta*sizeof(struct page_table_entry));

	struct page_table_entry nofnc;
	nofnc.dilav = 0;
		for(int pg=0;pg<siwe_ta;pg++)
		{
		uwbcjkcjw[pg]= nofnc;
	}
char* bcqjbq = argv[1];
	int qejbc = strtol(argv[2], NULL, 10);
	if(qejbc <= 0){
		return 0;
	}
	char *wywey = argv[3];
	bool verbose = false;
	if(argc==5 && strcmp(argv[4], "-verbose") == 0){
		verbose = true;
	}

	FILE *fp = fopen(bcqjbq, "r");
	if(fp == NULL)
	{return 0;}
	if(strcmp(wywey, "OPT") == 0) {OPT(qejbc, fp, verbose, uwbcjkcjw,ran1,ran2);}
	else if(strcmp(wywey, "LRU") == 0){		LRU(qejbc, fp, verbose, uwbcjkcjw,ran1,ran2);}
	else if(strcmp(wywey, "RANDOM") == 0){
		RANDOM(qejbc, fp, verbose, uwbcjkcjw,ran1,ran2);
	}
	else if(strcmp(wywey, "FIFO") == 0){FIFO(qejbc, fp, verbose, uwbcjkcjw,ran1,ran2);}
	else if(strcmp(wywey, "CLOCK") == 0){		CLOCK(qejbc, fp, verbose, uwbcjkcjw,ran1,ran2);}
	
	fclose(fp);
	return 0;

}
