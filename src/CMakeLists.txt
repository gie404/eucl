cmake_minimum_required(VERSION 3.10)

project(Eucl)

# set(SOURCE_DIR src)

add_executable(${PROJECT_NAME} 
circle.cpp
intersect.cpp
line.cpp
main.cpp
point.cpp
builder.cpp
)