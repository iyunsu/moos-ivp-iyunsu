#--------------------------------------------------------
# The CMakeLists.txt for:              lib_behaviors-test
# Author(s):                                
#--------------------------------------------------------

# Set System Specific Libraries
if (${WIN32})
  # Windows Libraries
  SET(SYSTEM_LIBS
      )
else (${WIN32})
  # Linux and Apple Libraries
  SET(SYSTEM_LIBS
      m )
endif (${WIN32})


MACRO(ADD_BHV BHV_NAME)
  ADD_LIBRARY(${BHV_NAME} SHARED ${BHV_NAME}.cpp)
  TARGET_LINK_LIBRARIES(${BHV_NAME} 
    helmivp
    behaviors 
    ivpbuild 
    logic 
    ivpcore 
    bhvutil 
    mbutil 
    geometry 
    ${SYSTEM_LIBS} )


ENDMACRO(ADD_BHV)

# example  
  ADD_LIBRARY(BHV_example SHARED BHV_example.cpp)
  TARGET_LINK_LIBRARIES(BHV_example 
    helmivp
    behaviors 
    ivpbuild 
    logic 
    ivpcore 
    bhvutil 
    mbutil 
    geometry 
    ${SYSTEM_LIBS} )

#BHV_PULSE
#  ADD_LIBRARY(BHV_Pulse SHARED BHV_Pulse.cpp)
#  TARGET_LINK_LIBRARIES(BHV_Pulse 
#    helmivp
#    behaviors 
#    ivpbuild 
#    logic 
#    ivpcore 
#    bhvutil 
#    mbutil 
#    geometry 
#    ${SYSTEM_LIBS} )
#
#BHV_ZIGLEG
#ADD_LIBRARY(BHV_ZigLeg SHARED BHV_ZigLeg.cpp)
#  TARGET_LINK_LIBRARIES(BHV_ZigLeg 
#    helmivp
#    behaviors 
#    ivpbuild 
#    logic 
#    ivpcore 
#    bhvutil 
#    mbutil 
#    geometry 
#    ${SYSTEM_LIBS} )



#BHV_PolygonV2
ADD_LIBRARY(BHV_PolygonV2 SHARED BHV_PolygonV2.cpp)
  TARGET_LINK_LIBRARIES(BHV_PolygonV2
    helmivp
    behaviors
    ivpbuild
    logic
    ivpcore
    bhvutil
    mbutil
    geometry
    ${SYSTEM_LIBS} )

#BHV_PoseKeeping
ADD_LIBRARY(BHV_PoseKeeping SHARED BHV_PoseKeeping.cpp)
  TARGET_LINK_LIBRARIES(BHV_PoseKeeping
    helmivp
    behaviors
    ivpbuild
    logic
    ivpcore
    bhvutil
    mbutil
    geometry
    ${SYSTEM_LIBS} )



#--------------------------------------------------------
#                                      BHV_SimpleWaypoint
#--------------------------------------------------------
#//ADD_LIBRARY(BHV_SimpleWaypoint SHARED 
#//   BHV_SimpleWaypoint.cpp AOF_SimpleWaypoint.cpp)
#//TARGET_LINK_LIBRARIES(BHV_SimpleWaypoint
#//   helmivp
#//   behaviors 
#//   ivpbuild 
#//   logic 
#//   ivpcore 
#//   bhvutil 
#//   mbutil 
#//   geometry 
#//   ${SYSTEM_LIBS} )
