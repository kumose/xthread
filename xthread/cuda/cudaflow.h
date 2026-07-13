#pragma once

#include <xthread/taskflow.h>
#include <xthread/cuda/cuda_graph.h>
#include <xthread/cuda/cuda_graph_exec.h>
#include <xthread/cuda/algorithm/single_task.h>

/**
@file taskflow/cuda/cudaflow.h
@brief cudaFlow include file
*/

namespace xthread {

/**
@brief default smart pointer type to manage a `cudaGraph_t` object with unique ownership
*/
using cudaGraph = cudaGraphBase<cudaGraphCreator, cudaGraphDeleter>;

/**
@brief default smart pointer type to manage a `cudaGraphExec_t` object with unique ownership
*/
using cudaGraphExec = cudaGraphExecBase<cudaGraphExecCreator, cudaGraphExecDeleter>;

}  // end of namespace xthread -----------------------------------------------------


