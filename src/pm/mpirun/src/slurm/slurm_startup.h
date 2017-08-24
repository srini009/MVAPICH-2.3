/* Copyright (c) 2001-2017, The Ohio State University. All rights
 * reserved.
 *
 * This file is part of the MVAPICH2 software package developed by the
 * team members of The Ohio State University's Network-Based Computing
 * Laboratory (NBCL), headed by Professor Dhabaleswar K. (DK) Panda.
 *
 * For detailed copyright and licensing information, please refer to the
 * copyright file COPYRIGHT in the top level MVAPICH2 directory.
 */

#ifndef SLURM_STARTUP_H
#define SLURM_STARTUP_H 1

int slurm_startup (int);
int slurm_nprocs (void);
int check_for_slurm();

#endif
