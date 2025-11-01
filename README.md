# Kumo

Welcome to Kumo, the PDF Reader written in C++.

It uses [poppler](https://gitlab.freedesktop.org/poppler/poppler) for extracting text and image data from PDFs.

Currently Kumo only supports headless mode. It is _heavily_ in development. <br> But don't worry, an mvp will be released soon.

Until then, feel free to compile Kumo yourself and play around with it.

## Build

### Dependencies

~~I have hardcoded the compiler and linker options in the `CMakeLists.txt` file. You can make changes if you want to.~~

Currently Kumo has the following (build) dependencies:

- [poppler](https://gitlab.freedesktop.org/poppler/poppler)
- (optional) clang
- (Optional) [mold linker](https://github.com/rui314/mold)
- gcc (>=14) or clang (>=18) since we're using the c++23 standard

By default cmake will try to use clang + mold. If they don't exist, the default compiler and/or linker will be used.

#### libpoppler

On linux mint,

```
sudo apt install libpoppler-cpp-dev
```

### Compile

```
git clone https://github.com/laughingclouds/Kumo.git
cd Kumo
cmake -B build -DCMAKE_CXX_COMPILER=g++-14
cmake --build build
```

The target binary will be named `kumo`

### Before Execution

Before you run/build the executable please know that the current repo hardcodes file links (I'm still at the testing/learning poppler stage).

> This is for commit hash: f4a9a5aecd4a67efd2c58f10b7a9b3186688b77f

Once you've built Kumo following the compilation instructions run it using from the terminal:

```
# assuming you're in the Kumo project root directory

./build/kumo
```
