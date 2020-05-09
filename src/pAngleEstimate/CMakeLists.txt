#--------------------------------------------------------
# The CMakeLists.txt for:                       pAngleEstimate
# Author(s):                              
#--------------------------------------------------------

SET(SRC
  AngleEstimate.cpp
  AngleEstimate_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pAngleEstimate ${SRC})

TARGET_LINK_LIBRARIES(pAngleEstimate
   ${MOOS_LIBRARIES}
   mbutil
   m
   pthread)

