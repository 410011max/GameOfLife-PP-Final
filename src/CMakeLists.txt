include_directories(${Conway_SOURCE_DIR}/include)
include_directories(${GLUT_INCLUDE_DIRS} )

# file(GLOB SOURCES "*.cpp")
# add_executable(Conway ${SOURCES})
# target_link_libraries(Conway OpenGL::OpenGL GLUT::GLUT GLU Threads::Threads)

file(GLOB CPP_SOURCES "*.cpp")
# add_executable(Conway ${CPP_SOURCES})

file(GLOB CU_SOURCES "*.cu")
cuda_add_executable(Conway ${CPP_SOURCES} ${CU_SOURCES})

include_directories(
  ${CUDA_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIRS}
  ${GLUT_INCLUDE_DIRS}
  ${GLEW_INCLUDE_DIRS}
)
# target_link_libraries(Conway OpenGL::OpenGL GLUT::GLUT GLU ${CUDA_LIBRARIES})
target_link_libraries(Conway
    ${CUDA_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}
    ${glm_LIBRARY}
    ${GLUE_LIBRARY}
    ${GLEW_LIBRARIES}
    Threads::Threads
    OpenMP::OpenMP_CXX
)