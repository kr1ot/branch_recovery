#include "renamer.h"

renamer::renamer(uint64_t n_log_regs,
		uint64_t n_phys_regs,
		uint64_t n_branches,
		uint64_t n_active)
        {
            //create rmt with size n_log_regs
            rmt = new uint64_t[n_log_regs];
            //pipeline empty state
            for (uint64_t idx = 0; idx < n_log_regs; idx++){
                rmt[idx] = idx;
            }
            
            //similarly initialize AMT
            amt = new uint64_t[n_log_regs];
            for (uint64_t idx = 0; idx < n_log_regs; idx++){
                amt[idx] = idx;
            }

            //size of free list = n_phys_reg - n_log_regs
            uint64_t free_list_size = n_phys_regs - n_log_regs;
            //create the free list
            free_list.free_list_entry = new uint64_t[free_list_size];
            for (uint64_t idx = 0; idx < free_list_size; idx++){
                //free list contains all the physical register mappings other than
                //registers in the RMT 
                free_list.free_list_entry[idx] = n_log_regs + idx;
            }

            //initialize free list to be full 
            free_list.head_ptr = 0;
            free_list.tail_ptr = 0;
            free_list.head_phase = false;
            free_list.tail_phase = true;

            //create Active list with size n_active
            active_list.active_list_entry = new active_list_entry_s[n_active];
            
            //make active list empty using the pointers
            active_list.head_ptr = 0;
            active_list.tail_ptr = 0;
            active_list.head_phase = false;
            active_list.tail_phase = false;
        
            //create physical register file with the size n_phys_reg
            prf = new uint64_t[n_phys_regs];
            //same size for the ready bits
            prf_ready_bits = new bool[n_phys_regs];


        }