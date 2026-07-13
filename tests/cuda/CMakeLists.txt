# Copyright (C) Kumo inc. and its affiliates.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

include(../doctest/doctest.cmake)

list(APPEND XFLOW_CUDA_UNITTESTS
  test_cuda_objects
  test_cuda_basics
  test_cuda_updates
  test_cuda_matrix
  test_cuda_kmeans
  test_cuda_for_each
  test_cuda_transform
  #test_cuda_reduce
  #test_cuda_scan
  #test_cuda_find
  #test_cuda_min_max_element
  #test_cuda_merge
  #test_cuda_capturer_optimizer
  #test_cuda_capture
  #cuda_algorithms
  #cuda_algorithm_updates
)

foreach(cudatest IN LISTS XFLOW_CUDA_UNITTESTS)
  add_executable(${cudatest} ${cudatest}.cu)
  target_link_libraries(${cudatest} ${PROJECT_NAME}::xthread ${KMCMAKE_DEPS_LINK})
  target_include_directories(${cudatest} PRIVATE ${PROJECT_SOURCE_DIR}/tests/doctest)

  if(NOT CUDA_ARCHITECTURES)
    set_property(TARGET ${cudatest} PROPERTY CUDA_ARCHITECTURES OFF)
  endif()

  doctest_discover_tests(${cudatest})
endforeach()
