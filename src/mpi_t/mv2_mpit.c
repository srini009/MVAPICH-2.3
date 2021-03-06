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
#include <mpichconf.h>
#include <mpiimpl.h>

/*
 * Profile IB channel-manager
 */
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mv2_ibv_channel_ctrl_packet_count);
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mv2_ibv_channel_out_of_order_packet_count);
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mv2_ibv_channel_exact_recv_count);

/*
 * Profile RDMA_FP connections and packets
 */
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mv2_rdmafp_ctrl_packet_count);
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mv2_rdmafp_out_of_order_packet_count);
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mv2_rdmafp_exact_recv_count);

/*
 * Track vbuf usage
 */
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mv2_vbuf_allocated);
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mv2_vbuf_freed);
MPIR_T_PVAR_ULONG_LEVEL_DECL(MV2, mv2_vbuf_available);
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mv2_ud_vbuf_allocated);
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mv2_ud_vbuf_freed);
MPIR_T_PVAR_ULONG_LEVEL_DECL(MV2, mv2_ud_vbuf_available);

/*
 * Track smp memory usage
 */
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mv2_smp_eager_sent);
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mv2_smp_rndv_sent);
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mv2_smp_eager_received);
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mv2_smp_rndv_received);
MPIR_T_PVAR_ULONG_LEVEL_DECL(MV2, mv2_smp_eager_total_buffer);
MPIR_T_PVAR_ULONG_LEVEL_DECL(MV2, mv2_smp_rndv_total_buffer);
MPIR_T_PVAR_ULONG_LEVEL_DECL(MV2, mv2_smp_eager_avail_buffer);
MPIR_T_PVAR_ULONG_LEVEL_DECL(MV2, mv2_smp_rndv_avail_buffer);
MPIR_T_PVAR_ULONG_LEVEL_DECL(MV2, mv2_smp_eager_buffer_max_use);
MPIR_T_PVAR_ULONG_LEVEL_DECL(MV2, mv2_smp_rndv_buffer_max_use);

/*
 * Track the registration cache hits and misses
 */
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mv2_reg_cache_hits);
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mv2_reg_cache_misses);

/*
 * Count progress engine polling
 */
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mpit_progress_poll);
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mv2_smp_read_progress_poll);
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mv2_smp_write_progress_poll);
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mv2_smp_read_progress_poll_success);
MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, mv2_smp_write_progress_poll_success);

/*
 * Count number of shared-memory collective calls
 */
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_num_shmem_coll_calls);

/*
 * Count 2-level communicator creation requests
 */
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_num_2level_comm_requests);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_num_2level_comm_success);

/*
 * Count MVAPICH Broadcast algorithms used
 */
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_bcast_binomial);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_bcast_scatter_doubling_allgather);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_bcast_scatter_ring_allgather);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_bcast_scatter_ring_allgather_shm);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_bcast_shmem);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_bcast_knomial_internode);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_bcast_knomial_intranode);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_bcast_mcast_internode);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_bcast_pipelined);

/*
 * Count MVAPICH Alltoall algorithms used
 */
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_alltoall_inplace);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_alltoall_bruck);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_alltoall_rd);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_alltoall_sd);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_alltoall_pw);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mpit_alltoallv_mv2_pw);

/*
 * Count MVAPICH Allreduce algorithms used
 */
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_allreduce_sharp);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_allreduce_shm_rd);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_allreduce_shm_rs);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_allreduce_shm_intra);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_allreduce_intra_p2p);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_allreduce_2lvl);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_allreduce_shmem);
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_allreduce_mcast);

/*
 * Count MVAPICH Iallreduce algorithms used
 */
MPIR_T_PVAR_ULONG2_COUNTER_DECL(MV2, mv2_coll_iallreduce_sharp);

/*
 * Count number of UD retransmissions
 */

/* Watermarks for message sizes used in pt-to-pt and collective communications
 *
 */
MPIR_T_PVAR_ULONG2_HIGHWATERMARK_DECL(MV2, mv2_allreduce_max_message_size);
MPIR_T_PVAR_ULONG2_LOWWATERMARK_DECL(MV2, mv2_allreduce_min_message_size);
MPIR_T_PVAR_ULONG2_HIGHWATERMARK_DECL(MV2, mv2_reduce_max_message_size);
MPIR_T_PVAR_ULONG2_LOWWATERMARK_DECL(MV2, mv2_reduce_min_message_size);
MPIR_T_PVAR_ULONG2_HIGHWATERMARK_DECL(MV2, mv2_bcast_max_message_size);
MPIR_T_PVAR_ULONG2_LOWWATERMARK_DECL(MV2, mv2_bcast_min_message_size);

MPIR_T_PVAR_ULONG_COUNTER_DECL(MV2, rdma_ud_retransmissions);

void
MPIT_REGISTER_MV2_VARIABLES (void)
{
    MPIR_T_PVAR_HIGHWATERMARK_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_bcast_max_message_size,
			0,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_MPI_COMM,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Maximum message size used in MPI_Bcast");
    
	MPIR_T_PVAR_LOWWATERMARK_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_bcast_min_message_size,
			4294967295, /*Maximum 32-bit unsigned value to be on the safer side*/
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_MPI_COMM,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Minimum message size used in MPI_Bcast");
    
	MPIR_T_PVAR_HIGHWATERMARK_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_reduce_max_message_size,
			0,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_MPI_COMM,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Maximum message size used in MPI_Reduce");
    
	MPIR_T_PVAR_LOWWATERMARK_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_reduce_min_message_size,
			4294967295, /*Maximum 32-bit unsigned value to be on the safer side*/
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_MPI_COMM,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Minimum message size used in MPI_Reduce");

    MPIR_T_PVAR_HIGHWATERMARK_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_allreduce_max_message_size,
			0,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_MPI_COMM,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Maximum message size used in MPI_Allreduce");
    
	MPIR_T_PVAR_LOWWATERMARK_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_allreduce_min_message_size,
			4294967295, /*Maximum 32-bit unsigned value to be on the safer side*/
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_MPI_COMM,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Minimum message size used in MPI_Allreduce");

    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_num_2level_comm_requests,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of 2-level comm creation requests");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_num_2level_comm_success,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of successful 2-level comm creations");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_num_shmem_coll_calls,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of times MV2 shared-memory collective calls were invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mpit_progress_poll,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "CH3 RDMA progress engine polling count");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_smp_read_progress_poll,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "CH3 SMP read progress engine polling count");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_smp_write_progress_poll,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "CH3 SMP write progress engine polling count");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_smp_read_progress_poll_success,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Unsucessful CH3 SMP read progress engine polling count");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_smp_write_progress_poll_success,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Unsucessful CH3 SMP write progress engine polling count");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            rdma_ud_retransmissions,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "CH3 RDMA UD retransmission count");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_bcast_binomial,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 binomial bcast algorithm  was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_bcast_scatter_doubling_allgather,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 scatter+double allgather bcast algorithm "
            "was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_bcast_scatter_ring_allgather,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of times MV2 scatter+ring allgather bcast algorithm "
            "was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_bcast_scatter_ring_allgather_shm,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 scatter+ring allgather shm bcast "
            "algorithm was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_bcast_shmem,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 shmem bcast algorithm was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_bcast_knomial_internode,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 knomial internode bcast algorithm "
            "was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_bcast_knomial_intranode,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 knomial intranode bcast algorithm "
            "was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_bcast_mcast_internode,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 mcast internode bcast algorithm "
            "was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_bcast_pipelined,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 pipelined bcast algorithm was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_alltoall_inplace,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 in-place alltoall algorithm was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_alltoall_bruck,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 brucks alltoall algorithm was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_alltoall_rd,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 recursive-doubling alltoall algorithm was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_alltoall_sd,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 scatter-destination alltoall algorithm was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_alltoall_pw,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 pairwise alltoall algorithm was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mpit_alltoallv_mv2_pw,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 pairwise alltoallv algorithm was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_allreduce_shm_rd,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 shm rd allreduce algorithm was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_allreduce_shm_rs,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 shm rs allreduce algorithm was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_allreduce_shm_intra,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 shm intra allreduce algorithm was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_allreduce_intra_p2p,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 intra p2p allreduce algorithm was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_allreduce_2lvl,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 two-level allreduce algorithm was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_allreduce_shmem,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 shmem allreduce algorithm was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG_LONG,
            mv2_coll_allreduce_mcast,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "COLLECTIVE", /* category name */
            "Number of times MV2 multicast-based allreduce algorithm was invoked");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_reg_cache_hits,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of registration cache hits");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_reg_cache_misses,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of registration cache misses");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_vbuf_allocated,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of VBUFs allocated");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_vbuf_freed,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of VBUFs freed");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_ud_vbuf_allocated,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of UD VBUFs allocated");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_ud_vbuf_freed,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of UD VBUFs freed");
    MPIR_T_PVAR_LEVEL_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_vbuf_available,
            0, /* initial value */
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of VBUFs available");
    MPIR_T_PVAR_LEVEL_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_smp_eager_avail_buffer,
            0, /* initial value */
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Available number of SMP bytes for eager");
    MPIR_T_PVAR_LEVEL_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_smp_rndv_avail_buffer,
            0, /* initial value */
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Available number of SMP bytes for rndv");
    MPIR_T_PVAR_LEVEL_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_smp_eager_total_buffer,
            0, /* initial value */
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Total number of SMP bytes for eager");
    MPIR_T_PVAR_LEVEL_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_smp_rndv_total_buffer,
            0, /* initial value */
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Total number of SMP bytes for rndv");
    MPIR_T_PVAR_LEVEL_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_smp_eager_buffer_max_use,
            0, /* initial value */
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Max number of SMP bytes used for eager");
    MPIR_T_PVAR_LEVEL_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_smp_rndv_buffer_max_use,
            0, /* initial value */
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Max number of SMP bytes used for rndv");
    MPIR_T_PVAR_LEVEL_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_ud_vbuf_available,
            0, /* initial value */
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of UD VBUFs available");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_smp_eager_sent,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of SMP bytes sent through eager");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_smp_rndv_sent,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of SMP bytes sent through rendezvous");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_smp_eager_received,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of SMP bytes received through eager");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_smp_rndv_received,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of SMP bytes received through rendezvous");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_rdmafp_ctrl_packet_count,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of RDMA FP CTRL Packet count");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_rdmafp_out_of_order_packet_count,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of RDMA FP Out of Order Packet count");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_rdmafp_exact_recv_count,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of RDMA FP Exact Recv count");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_ibv_channel_ctrl_packet_count,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of IB control packets");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_ibv_channel_out_of_order_packet_count,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of IB out-of-order packets");
    MPIR_T_PVAR_COUNTER_REGISTER_STATIC(
            MV2,
            MPI_UNSIGNED_LONG,
            mv2_ibv_channel_exact_recv_count,
            MPI_T_VERBOSITY_USER_BASIC,
            MPI_T_BIND_NO_OBJECT,
            (MPIR_T_PVAR_FLAG_READONLY | MPIR_T_PVAR_FLAG_CONTINUOUS),
            "CH3", /* category name */
            "Number of IB exact receives");
}
