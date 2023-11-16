if(ESP_PLATFORM)
	file(GLOB_RECURSE SOURCES *.c )
	idf_component_register(SRCS ${SOURCES}
	                       INCLUDE_DIRS "." 
						   REQUIRES 
						       lvgl
							   led
						  )						
	target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-error=format-overflow) 
else()
	message(FATAL ERROR "LVGL LV generated: ESP PLATFORM is not defined. Try reinstalling ESP-IDF.") 
endif()

