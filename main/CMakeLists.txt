INCLUDE_DIRECTORIES(${BLUETOOTH_SOURCE_DIR}/include)
ADD_EXECUTABLE(synchroCarte synchroCarte.c)
TARGET_LINK_LIBRARIES(synchroCarte bt_op)
ADD_EXECUTABLE(synchroServeur synchroServeur.c)
TARGET_LINK_LIBRARIES(synchroServeur bt_op)
ADD_EXECUTABLE(recvMsg recvMsg.c)
TARGET_LINK_LIBRARIES(recvMsg bt_op)
ADD_EXECUTABLE(sendMsg sendMsg.c)
TARGET_LINK_LIBRARIES(sendMsg bt_op)
