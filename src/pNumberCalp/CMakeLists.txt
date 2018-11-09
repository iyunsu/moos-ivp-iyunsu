#--------------------------------------------------------
# The CMakeLists.txt for:                       pNumberCalp
# Author(s):                              iyunsu
#--------------------------------------------------------

SET(SRC
  NumberCalp.cpp
  NumberCalp_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pNumberCalp ${SRC})

TARGET_LINK_LIBRARIES(pNumberCalp
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread)

