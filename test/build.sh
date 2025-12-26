#! /bin/bash

build_cmake  () {
    mkdir -p $1
    cd $1
    if [ $1 = "windows" ]; then
        cmake -DCMAKE_TOOLCHAIN_FILE=../mingw-w64-toolchain.cmake ../
    else
        cmake ../
    fi
    make -j$(nproc)
    if [ $? -eq 0 ]; then
        echo -e "$1 build succesfully"
    else
        echo -e "$1 build failed"
    fi
}

case $1 in
    "linux")
        build_cmake "linux";;

    "windows")
        build_cmake "windows";;

    "clean")
        rm -rf linux windows;;
    "all")
        build_cmake "linux"
        cd ../
        build_cmake "windows";;
    *)
        echo "available options [ linux | windows | clean | all ]";;
esac
# mkdir -p Linux
# cd Linux
# cmake ../
# make -j$(nproc)
# if [ $? -eq 0 ]; then
#     echo -e "Linux build successful!"
# else
#     echo -e "Linux build failed!\n"
#     exit 1
# fi
# cd ../

# # Build for Windows
# mkdir -p Windows
# cd Windows
# cmake -DCMAKE_TOOLCHAIN_FILE=../mingw-w64-toolchain.cmake ../
# make -j$(nproc)
# if [ $? -eq 0 ]; then
#     echo -e "Windows build successful!"
# else
#     echo -e "Windows build failed!\n"
#     exit 1
# fi