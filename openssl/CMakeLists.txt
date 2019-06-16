cmake_minimum_required(VERSION 3.5)

project(learn_openssl)


include_directories(/usr/include)

link_directories(/usr/lib)

add_executable(test_bio test_bio_md.c)
target_link_libraries(test_bio crypto)

add_executable(test_bio_base64 test_bio_base64.c)
target_link_libraries(test_bio_base64 crypto)