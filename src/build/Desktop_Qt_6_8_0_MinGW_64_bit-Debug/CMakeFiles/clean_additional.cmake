# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "2024-JCO-The-Legend-of-Chiup-Chiup-ALE_autogen"
  "CMakeFiles\\2024-JCO-The-Legend-of-Chiup-Chiup-ALE_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\2024-JCO-The-Legend-of-Chiup-Chiup-ALE_autogen.dir\\ParseCache.txt"
  )
endif()
