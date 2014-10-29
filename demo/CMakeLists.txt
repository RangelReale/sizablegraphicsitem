INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

SET(sizablegraphicsitemdemo_SOURCES ../SizableGraphicsItem.cpp MainWindow.cpp main.cpp)
SET(sizablegraphicsitemdemo_HEADERS ../SizableGraphicsItem.h MainWindow.h)

ADD_EXECUTABLE(sizablegraphicsitemdemo
  ${sizablegraphicsitemdemo_SOURCES}
  ${sizablegraphicsitemdemo_HEADERS}
)

TARGET_LINK_LIBRARIES(sizablegraphicsitemdemo)

qt5_use_modules(sizablegraphicsitemdemo Widgets)
