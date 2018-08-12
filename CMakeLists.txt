CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(DemoForCpp CXX)

MESSAGE(STATUS                                      "Project Directory: ${PROJECT_SOURCE_DIR}")

SET(MAIN_DIR                                        ${PROJECT_SOURCE_DIR})
SET(SOURCE_DIR                                      ${MAIN_DIR}/source)

### 设置各个DEMO源文件
AUX_SOURCE_DIRECTORY(${SOURCE_DIR}/demos        DEMOS_SRC)
AUX_SOURCE_DIRECTORY(${SOURCE_DIR}/base         BASE_SRC)

SET(ALL_SRC     ${DEMOS_SRC}
                ${BASE_SRC})

#AUX_SOURCE_DIRECTORY(<dir> <variable>)

### 添加INCLUDE路径
INCLUDE_DIRECTORIES(${SOURCE_DIR}/include)

### 输出路径
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY                  ${MAIN_DIR})

### 编译选项
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall")

### 添加DEMO
ADD_EXECUTABLE(run_demo                             ${ALL_SRC})