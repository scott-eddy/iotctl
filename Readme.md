# Building for Android
```
cmake -DCMAKE_SYSTEM_NAME=Android -DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK}/build/cmake/android.toolchain.cmake -DANDROID_ABI=armeabi-v7a  -DANDROID_TOOLCHAIN=clang -DCMAKE_PREFIX_PATH=/home/eddy/Qt5.12.1/5.12.1/android_armv7/lib/cmake/Qt5 ..
```
