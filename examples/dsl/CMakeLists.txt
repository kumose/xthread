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

list(APPEND TF_DSL_EXAMPLES
  condition_dsl
  simple_dsl
  visualization_dsl
)

foreach(dsl_example IN LISTS TF_DSL_EXAMPLES)
  kmcmake_cc_binary(
    NAME ${dsl_example}
    SOURCES ${dsl_example}.cc
    LINKS
    ${KMCMAKE_DEPS_LINK}
    DEPS
    ${PROJECT_NAME}::xthread
    CXXOPTS
    ${KMCMAKE_CXX_OPTIONS}
  )
endforeach()
