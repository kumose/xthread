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

list(APPEND XFLOW_CUDA_EXAMPLES
  cuda_device_property
  cuda_saxpy
  cuda_matmul
  cuda_knn
  #cuda_capturer
  #cuda_reduce
  #cuda_scan
  #cuda_merge
  #cuda_sort
  #cuda_transform
  cuda_saxpy_update
  #cuda_find
)

foreach(cuda_example IN LISTS XFLOW_CUDA_EXAMPLES)
  add_executable(${cuda_example} ${cuda_example}.cu)
  target_link_libraries(${cuda_example}
    ${PROJECT_NAME}::xthread ${KMCMAKE_DEPS_LINK}
  )

  if(NOT CUDA_ARCHITECTURES)
    set_property(TARGET ${cuda_example} PROPERTY CUDA_ARCHITECTURES OFF)
  endif()
endforeach()
