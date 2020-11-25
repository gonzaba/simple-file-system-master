// fs.cpp: File System

#include "sfs/fs.h"

// #include <algorithm>

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Debug file system -----------------------------------------------------------

void debug(Disk *disk) {
    Block block;

    // Read Superblock
    
    disk->readDisk(disk, 0, block.Data);
    
    printf("SuperBlock:\n");
    printf("    magic number is %s\n", block.Super.MagicNumber == MAGIC_NUMBER?"valid":"invalid");
    printf("    %u blocks\n"         , block.Super.Blocks);
    printf("    %u inode blocks\n"   , block.Super.InodeBlocks);
    printf("    %u inodes\n"         , block.Super.Inodes);
    
    // Read Inode blocks
    int numberOfInodeBlocks = block.Super.InodeBlocks;
    for(int inodeBlock=1; inodeBlock <= numberOfInodeBlocks;inodeBlock++){
        disk->readDisk(disk,inodeBlock,block.Data);
        for(unsigned int currentInode=0;currentInode<INODES_PER_BLOCK;currentInode++){
            Inode inode = block.Inodes[currentInode];
            if(inode.Valid==0)
                continue;
            printf("Inode %d:\n",currentInode);
            printf("    size: %u bytes\n", inode.Size);
            printf("    direct blocks:");
            for(unsigned int directBlock=0; directBlock < POINTERS_PER_INODE; directBlock++){
                    if(inode.Direct[directBlock]){
                        printf(" %u",inode.Direct[directBlock]);
                    }
            }
            printf("\n");
        }
            
    }
    
}

// Format file system ----------------------------------------------------------

bool format(Disk *disk) {
    
    // Write superblock
    if(disk-> mounted(disk)){
        return false;
    } 

    Block bloque; 

    bloque.Super.MagicNumber = MAGIC_NUMBER;
    bloque.Super.Blocks = disk->size(disk);
    bloque.Super.InodeBlocks = bloque.Super.Blocks/10;

    if (bloque.Super.Blocks % 10 != 0) {
        bloque.Super.InodeBlocks++;
    }

    bloque.Super.Inodes = bloque.Super.InodeBlocks * INODES_PER_BLOCK;

    disk->writeDisk(disk,0, bloque.Data);
    
    // Clear all other blocks
    Block EmptyBlock = {0};
    for (unsigned int i = 1; i < disk->size(disk); i++){
        disk-> writeDisk(disk, i, EmptyBlock.Data);
    }
    return true;
}



// Mount file system -----------------------------------------------------------

bool mount(Disk *disk) {
    // Read superblock

    // Set device and mount

    // Copy metadata

    // Allocate free block bitmap

    return true;
}

// Create inode ----------------------------------------------------------------

size_t create() {
    // Locate free inode in inode table

    // Record inode if found
    return 0;
}

// Remove inode ----------------------------------------------------------------

bool removeInode(size_t inumber) {
    // Load inode information

    // Free direct blocks

    // Free indirect blocks

    // Clear inode in inode table
    return true;
}

// Inode stat ------------------------------------------------------------------

size_t stat(size_t inumber) {
    // Load inode information
    return 0;
}

// Read from inode -------------------------------------------------------------

size_t readInode(size_t inumber, char *data, size_t length, size_t offset) {
    // Load inode information

    // Adjust length

    // Read block and copy to data
    return 0;
}

// Write to inode --------------------------------------------------------------

size_t writeInode(size_t inumber, char *data, size_t length, size_t offset) {
    // Load inode
    
    // Write block and copy to data
    return 0;
}
