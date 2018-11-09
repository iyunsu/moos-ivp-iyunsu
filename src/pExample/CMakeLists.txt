#--------------------------------------------------------
# The CMakeLists.txt for:                       pExample
# Author(s):                              iyunsu
#--------------------------------------------------------

SET(SRC
  Example.cpp
  Example_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pExample ${SRC})

TARGET_LINK_LIBRARIES(pExample
   ${MOOS_LIBRARIES}
   mbutil
   m
   pthread)

