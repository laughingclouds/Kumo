# Kumo

Welcome to Kumo, the PDF Reader written in C++.

It uses [poppler](https://gitlab.freedesktop.org/poppler/poppler) for extracting text and image data from PDFs.

Currently Kumo only supports headless mode. It is _heavily_ in development. <br> But don't worry, an mvp will be released soon.

Until then, feel free to compile Kumo yourself and play around with it.

## Build

### Dependencies

I have hardcoded the compiler and linker options in the `CMakeLists.txt` file. You can make changes if you want to.

With that in mind, currently Kumo has the following dependencies:

- [poppler](https://gitlab.freedesktop.org/poppler/poppler)
- clang
- [mold linker](https://github.com/rui314/mold)

Please make sure you have at least poppler installed (and make necessary changes if you wish to use a different compiler + linker).

> Give mold a try though. It has saved hours of my life.

### Compile

For now you can only compile Kumo using a single compilation mode. More will be added as the project grows.

```
git clone https://github.com/laughingclouds/Kumo.git
cd Kumo
cmake -B build
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
