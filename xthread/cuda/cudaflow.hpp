#pragma once

#include <xthread/taskflow.hpp>
#include <xthread/cuda/cuda_graph.hpp>
#include <xthread/cuda/cuda_graph_exec.hpp>
#include <xthread/cuda/algorithm/single_task.hpp>

/**
@file taskflow/cuda/cudaflow.hpp
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


