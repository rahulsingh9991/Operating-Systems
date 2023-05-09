#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mmu.h"
int error_no;
page_table_entry* pt_pointer;
#define NUM_FRAMES  ((RAM_SIZE) / PAGE_SIZE)
#define NUM_USABLE_FRAMES  ((RAM_SIZE - OS_MEM_SIZE) / PAGE_SIZE)
#define MB (1024*1024)
#define KB (1024)
#define pid_limit  (2*MAX_PROCS)
#define vpn_limit  1024

unsigned char RAM[RAM_SIZE];
unsigned char* OS_MEM = RAM;
unsigned char* PS_MEM = RAM + OS_MEM_SIZE;


unsigned bit_vmem = (1<<12) - 1;//011111111111(12 ones)
unsigned bit_pfn = (((1<<15) - 1) << 4);//1111111110000(15 ones followed by 4 zeros)
unsigned bit_vpn = ((1<<10) - 1) << 12;//1111111110000000000(10 ones followed by 12 zeros)

unsigned bit_write = O_WRITE;
unsigned bit_read = O_READ;
unsigned bit_exec = O_EX;
unsigned bit_others = O_READ | O_WRITE | O_EX | (1<<3);//0001 or 0010 or 0100 or 1000 = 1111
unsigned bit_present = 1<<3;//1000

char* list_pfn;
unsigned int* list_fork;
char* list_pid;
unsigned int pfn_lfree = 0;
unsigned int pid_lfree = 0;

unsigned int vpn_frm_vmem(unsigned int var) {
    return (var & bit_vpn) >> 12;// xbits which were 12th and 21st bit remains (these are required 10 bits) 
}

unsigned int pfn_frm_pagetableentry(unsigned int var) {
    return (var & bit_pfn) >> 4;//  xbits which were 4th and 18th bit remains (these are required 15 bits) 

}

unsigned int get_store_pid() {
    if(list_pid[pid_lfree]==1) 
    {//if list_pid is not null for a index value then it means it can be used for allocation
            list_pid[pid_lfree] = 0;
        return pid_lfree;
    }
    
    else
    {//run while till we get a non - null value in list_pid, pid_limit=200
        
        while(list_pid[pid_lfree]==0) 
        {pid_lfree = (pid_lfree + 1) % pid_limit;}
        
        list_pid[pid_lfree] = 0;
        return pid_lfree;

    }
}

unsigned int get_store_pfn() {
    if(list_pfn[pfn_lfree]==1) 
    {
          list_pfn[pfn_lfree] = 0;
        return pfn_lfree;
    }
    else 
    {
        while(list_pfn[pfn_lfree]==0) 
        {pfn_lfree = (pfn_lfree + 1) % NUM_USABLE_FRAMES;}
        
        list_pfn[pfn_lfree] = 0;
        return pfn_lfree;
    }
}


void os_init() {
     pt_pointer = (void *)OS_MEM;//starting address is zero of RAM, pt is pointing towards this
    memset(pt_pointer, 0, pid_limit * vpn_limit * sizeof(unsigned int));//creating page table starting from 0th address,size=200*1024*4=32768, value stored is zero intially
    
        list_pfn = pid_limit * vpn_limit+OS_MEM;// address is 200*1024 in bytes
     memset(list_pfn, 1, NUM_USABLE_FRAMES);//creating list of physical page free(char type) from 200*1024th address,size=128MB/4KB, value stored is 1 intially
    
     list_pid = pid_limit*vpn_limit + NUM_USABLE_FRAMES+OS_MEM;// address is 200*1024 + 128MB/4KB in bytes
    memset(list_pid, 1, pid_limit);//creating list of pid number free(char type) from 200*1024 + 128MB/4KB th address,size=200, value stored is 1 intially
    
    list_fork = pid_limit * vpn_limit +pid_limit+ NUM_USABLE_FRAMES  +(void *)OS_MEM;// address is 200*1024 + 128MB/4KB + 200  in bytes
    memset(list_fork, 0, pid_limit*sizeof(unsigned int));//creating list of fork copy pages(int type) from 200*1024 + 128MB/4KB + 200 th address,size=200*4, value stored is 0 intially

}


int create_ps(int code_size, int ro_data_size, int rw_data_size, int max_stack_size, unsigned char* code_and_ro_data)
{ 
    unsigned int vpn = 0;
    unsigned int val_pfn;
    int pid = get_store_pid();//return free pid(actually index value of list_pid list that is storing null value which represent it is is free)
    page_table_entry* pt_pointer_m = pid*vpn_limit+pt_pointer;//Each page table size is vpn_limit and number of page table are 200(MAX_pid). So if we want 2nd page table we need to cover size of page table one first,i.e.,1024(vpn_limit)  Here 4bytes stored in each translation is not considered.
    while(vpn < code_size/PAGE_SIZE) 
    {//Stroring only code data in this for loop
        val_pfn = get_store_pfn();//it is of 15 bits = 128MB/4KB=32768=2^15
        pt_pointer_m[vpn] = (val_pfn << 4) | bit_read | bit_exec | bit_present;//here 15 bits left shifted and lowest 4 bits contain protection bit .Value is stored at pt_pointer_m[vpn] represent translation in page table
        memcpy(pfn_frm_pagetableentry(pt_pointer_m[vpn]) * PAGE_SIZE + PS_MEM, code_and_ro_data, PAGE_SIZE);//pfn_frm_pagetableentry(pt_pointer_m[vpn]) returns the 15 bits of pt_pointer_m[vpn] from top most bit //PS_MEM stores starting address of process memory(After 72MB) //Copy occur at address PS_MEM + frame_number*page_size
        code_and_ro_data += PAGE_SIZE;//Updating the value of code_and_ro_data(char pointer) so that memcpy takes value from intial value pointer pointing + PAGE size(address onwards)  
    vpn++;
    }
    while(vpn < (code_size + ro_data_size)/PAGE_SIZE) 
    {//now stroring ro_data. vpn will begin with the number-> ceiling value of (code_size/PAGE_SIZE)
        val_pfn = get_store_pfn();
        pt_pointer_m[vpn] = (val_pfn << 4) | bit_read | bit_present;
        memcpy(pfn_frm_pagetableentry(pt_pointer_m[vpn]) * PAGE_SIZE+PS_MEM, code_and_ro_data, PAGE_SIZE);
        code_and_ro_data += PAGE_SIZE;
    vpn++;
    }
    while(vpn < (code_size + ro_data_size + rw_data_size)/PAGE_SIZE)
    {//rw alloaction
        *(pt_pointer_m + vpn) = (get_store_pfn() << 4)|bit_read|bit_present|bit_write;
    vpn++;}
    while(vpn < (vpn_limit - (max_stack_size)/PAGE_SIZE))
    {//heap allocation
        *(pt_pointer_m + vpn) = 0;//storing 0 represents null
    vpn++;
    }
    vpn = vpn_limit-1;
    while(vpn > vpn_limit - 1 - (max_stack_size)/PAGE_SIZE) 
    {//stack allocation
        *(pt_pointer_m + vpn) = (get_store_pfn() << 4)|bit_read|bit_present|bit_write;
    vpn--;
    }
    
    list_fork[pid] = (code_size + ro_data_size) / PAGE_SIZE;// list_fork is a list of integer of size(200*4) storing data for each process(among 200) storing //(code_size + ro_data_size) / PAGE_SIZE  equal to number of pages required for (code_size + ro_data_size)

     return pid;
}


void exit_ps(int pid)
{unsigned int vpn = 0;
    list_pid[pid] = 1;//setting the list free for pid index value . Now this pid number could be alloted to new process
    page_table_entry* pt_pointer_m = pt_pointer + pid * vpn_limit;
    while(vpn < vpn_limit) 
    {page_table_entry pte = *(pt_pointer_m + vpn);
        if(pte & bit_present) list_pfn[pfn_frm_pagetableentry(pte)] = 1;//pte is required to get pfn value . Since pte stores which process and what vpn.
        pt_pointer_m[vpn] = 0;
    vpn++;
    }
}
int fork_ps(int pid) 
{
    unsigned int vpn = 0;
    unsigned int pfn_n;
    unsigned int pfn_o;
    int generate_pid = get_store_pid();
    page_table_entry* pointer_o = pt_pointer + pid * vpn_limit;
    
     page_table_entry* pointer_n = pt_pointer + generate_pid * vpn_limit;
    while(vpn < vpn_limit) 
    {
        page_table_entry pte = *(pointer_o + vpn);
        if(bit_present & pte )
        {   pfn_o = pfn_frm_pagetableentry(pte);
            pfn_n = get_store_pfn();
            *(pointer_n + vpn) = (pte & bit_others) | (pfn_n << 4) ; //bit_others=1111 
            memcpy( pfn_n * PAGE_SIZE+PS_MEM, pfn_o * PAGE_SIZE+PS_MEM, PAGE_SIZE);
        }

    vpn++;
    }
    vpn = 0;
    list_fork[generate_pid] = list_fork[pid];

     int num_vir_pag_cop = list_fork[pid];
    while(vpn < num_vir_pag_cop) 
    {pfn_n = pfn_frm_pagetableentry(pointer_n[vpn]);
        pfn_o = pfn_frm_pagetableentry(pointer_o[vpn]);
        
    memcpy(pfn_n * PAGE_SIZE+PS_MEM, pfn_o * PAGE_SIZE+PS_MEM, PAGE_SIZE);
    vpn++;
    }
    return generate_pid;
}

void allocate_pages(int pid, int vmem_addr, int num_pages, int flags)
{

    page_table_entry* pt_pointer_m = pid * vpn_limit+pt_pointer;

    unsigned int vpn = vpn_frm_vmem(vmem_addr);
    unsigned int pfn;
    page_table_entry pte;
    unsigned int it = 0;
    while(it<num_pages)
     
    {
        pte = pt_pointer_m[vpn+it];
        if ((bit_present & pte)==1) {
            error_no = ERR_SEG_FAULT;
            exit_ps(pid);
            return;
        }
    it++;
    }
    it=0;
    while(it<num_pages) 
    {
        pt_pointer_m[vpn + it] = ( ((unsigned int) flags) | get_store_pfn()  | bit_present);
    it++;
    }

}

void deallocate_pages(int pid, int vmem_addr, int num_pages)
{


    unsigned int vpn = vpn_frm_vmem(vmem_addr);
    unsigned int pfn;
    page_table_entry pte;
    page_table_entry* pt_pointer_m = pt_pointer + pid * vpn_limit;
    unsigned int it=0;
    while(it<num_pages) 
    {
        pte = pt_pointer_m[vpn+it];
        if ((pte & bit_present)==0) 
        {//not allocated
            error_no = ERR_SEG_FAULT;
            exit_ps(pid);
            break;
        }
        else 
        {
             list_pfn[pfn_frm_pagetableentry(pte)] = 1;//if allocated then dealloacte
            pt_pointer_m[vpn+it] = 0;
        }
    it++;
    }
}

unsigned char read_mem(int pid, int vmem_addr)
{   unsigned int vmem_off = vmem_addr & bit_vmem;// bit_vmem (1<<12)=10000000000000000000(12 zeros)  ((1<<10) - 1)=011111111111(12 ones)
    unsigned int vpn = vpn_frm_vmem(vmem_addr);

    page_table_entry* pt_pointer_m =  pid * vpn_limit+pt_pointer;
    page_table_entry pte = pt_pointer_m[vpn];
    
    if((pte & bit_read)==0){
                error_no = ERR_SEG_FAULT;
        exit_ps(pid);
    }
    else{
        return PS_MEM[(pfn_frm_pagetableentry(pte) << 12) + vmem_off];
    }
}


void write_mem(int pid, int vmem_addr, unsigned char byte)
{    unsigned int vmem_off = vmem_addr & bit_vmem;
    unsigned int vpn = vpn_frm_vmem(vmem_addr);
    page_table_entry* pt_pointer_m = pid * vpn_limit+pt_pointer;
     page_table_entry pte = pt_pointer_m[vpn];
    

    if ((pte  & bit_write)==0) {
        exit_ps(pid);
        error_no = ERR_SEG_FAULT;        
    }
    else {
        PS_MEM[(pfn_frm_pagetableentry(pte) << 12) + vmem_off] = byte;

    }

}

int pte_to_frame_num(page_table_entry pte)
{    return pfn_frm_pagetableentry(pte);
}

int is_readable(page_table_entry pte) 
{   if(bit_read & pte) return 1;
    else return 0;
}

int is_writeable(page_table_entry pte) 
{    if(pte & bit_write) return 1;
    else return 0;
}

int is_executable(page_table_entry pte) 
{    if(pte & bit_exec) return 1;
    else return 0;
}

int is_present(page_table_entry pte) 
{    if(pte & bit_present) return 1;
    else return 0;
}


void print_page_table(int pid)
{

    page_table_entry* page_table_start = pid+pt_pointer; 
    int num_page_table_entries = vpn_limit;           

    // Do not change anything below
    puts("------ Printing page table-------");
    for (int i = 0; i < num_page_table_entries; i++)
    {
        page_table_entry pte = page_table_start[i];
        printf("Page num: %d, frame num: %d, R:%d, W:%d, X:%d, P%d\n",
                i,
                pte_to_frame_num(pte),
                is_readable(pte),
                is_writeable(pte),
                is_executable(pte),
                is_present(pte)
                );
    }

}
