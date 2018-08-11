CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(DemoForCpp CXX)

MESSAGE(STATUS                              "Project Directory: ${PROJECT_SOURCE_DIR}")

SET(MAIN_DIR                                ${PROJECT_SOURCE_DIR})
SET(SOURCE_DIR                              ${MAIN_DIR}/source)

### 设置各个DEMO文件夹
SET(STL_DEMOS                               ${SOURCE_DIR}/STL_Demos)
SET(TEMPLATE_DEMOS                          ${SOURCE_DIR}/template_Demos)

#AUX_SOURCE_DIRECTORY(<dir> <variable>)

### 添加INCLUDE路径
INCLUDE_DIRECTORIES(${SOURCE_DIR}/include)

### 输出路径
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY          ${MAIN_DIR})

### 编译选项
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")

### 添加DEMO
ADD_EXECUTABLE(demo_vector                  ${STL_DEMOS}/demo_vector.cpp)
ADD_EXECUTABLE(demo_template_unit_program   ${TEMPLATE_DEMOS}/demo_template_unit_program.cpp)
