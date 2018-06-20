install(FILES org.qgis.qgis.desktop DESTINATION share/applications)
install(FILES org.qgis.qgis.appdata.xml DESTINATION share/metainfo)
install(FILES ${CMAKE_SOURCE_DIR}/images/icons/qgis_icon.svg DESTINATION share/icons/hicolor/scalable/apps)

foreach(_type qgs qlr qml qpt)
  install(FILES ${CMAKE_SOURCE_DIR}/images/icons/qgis_${_type}_icon.svg DESTINATION share/icons/hicolor/scalable/mimetypes/)
endforeach()
