# Building for Android
```
- cmake -DCMAKE_SYSTEM_NAME=Android -DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK}/build/cmake/android.toolchain.cmake -DANDROID_ABI=armeabi-v7a  -DANDROID_TOOLCHAIN=clang -DQT_INSTALL_ROOT=~/Qt5.12.0/5.12.0/ ..
```
