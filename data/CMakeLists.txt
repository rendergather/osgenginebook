SET( DATA_PATH ${PROJECT_SOURCE_DIR}/data )

SET( DATA_FILES
    ${DATA_PATH}/axes.osg
    ${DATA_PATH}/bunny-high.ive
    ${DATA_PATH}/bunny-low.ive
    ${DATA_PATH}/bunny-mid.ive
    ${DATA_PATH}/cessna.osg
    ${DATA_PATH}/cessnafire.osg
    ${DATA_PATH}/cow.osg
    ${DATA_PATH}/glider.osg
    ${DATA_PATH}/house.ive
    ${DATA_PATH}/lz.osg
    ${DATA_PATH}/clockface.jpg
    ${DATA_PATH}/posx.jpg
    ${DATA_PATH}/negx.jpg
    ${DATA_PATH}/posy.jpg
    ${DATA_PATH}/negy.jpg
    ${DATA_PATH}/posz.jpg
    ${DATA_PATH}/negz.jpg
    ${DATA_PATH}/tree.rgba
    ${DATA_PATH}/wall.png
    ${DATA_PATH}/osg64.png
    ${DATA_PATH}/osg128.png
    ${DATA_PATH}/osg256.png
    ${DATA_PATH}/0.JPG
    ${DATA_PATH}/1.JPG
    ${DATA_PATH}/2.JPG
    ${DATA_PATH}/3.JPG
    ${DATA_PATH}/4.JPG
    ${DATA_PATH}/5.JPG
    ${DATA_PATH}/6.JPG
    ${DATA_PATH}/7.JPG
    ${DATA_PATH}/8.JPG
    ${DATA_PATH}/9.JPG
)

INSTALL(FILES ${DATA_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
