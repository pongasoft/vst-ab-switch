VST2/3 A/B Switch
=================

This project is a VST implementation of the [A/B Audio Switch](https://pongasoft.com/rack-extensions/ABSwitch.html) rack extension. You can check the [A/B Switch](https://pongasoft.com/vst/ABSwitch.html) documentation directly.

This project is connected to the [VST Development Notes](https://www.pongasoft.com/blog/yan/vst/2018/03/12/VST-development-notes) blog post series.

2018-06-19 - Status for tag `v1.1.2`
------------------------------------
* fixed memory allocation in the real time processing issue

2018-06-12 - Status for tag `v1.1.1`
------------------------------------
* fixed soften status not being saved

2018-04-18 - Status for tag `v1.1.0`
------------------------------------
* Now builds on Windows as well

2018-04-14 - Status for tag `v1.0.0`
------------------------------------
* the logic is fully implemented: switching between A & B, optional cross fading (soften feature), ability to name each input, LED audio on status light
* the UI is now similar to the rack extension UI
* see [A/B Switch](https://pongasoft.com/vst/ABSwitch.html) documentation

2018-03-24 - Status for tag `blog-part4-369`
--------------------------------------------
* the logic is fully implemented: switching between A & B, optional cross fading (soften feature), ability to name each input, LED audio on status light
* no "pretty" UI
* see [VST Development Notes (3.6.9) - Part 4](https://www.pongasoft.com/blog/yan/vst/2018/03/24/VST-development-notes-part4/) for details

2018-03-17 - Status for tag `blog-part3-369`
--------------------------------------------
* the plugin has a small UI with text and a switch to toggle between input A and B
* the basic logic is working => toggling between A and B actually toggles which input is copied to the output
* see [VST Development Notes (3.6.9) - Part 3](https://www.pongasoft.com/blog/yan/vst/2018/03/17/VST-development-notes-part3/) for details

2018-03-13 - Status for tag `blog-part2-369`
--------------------------------------------
* the plugin uses SDK 3.6.9
* the plugin compiles while depending on the SDK (following this other project [vst3-again-sample](https://github.com/pongasoft/vst3-again-sample))
* the processing part is doing exactly what the [vst24-hello-world](https://github.com/pongasoft/vst24-hello-world) plugin is doing: simply removing 3dB by multiplying every sample by 0.5 (as a way to check that the processing part is being executed properly)
* the controller part (UI) is a black square and by right clicking in it you can enter the inline UI editor that comes built-in with VSTGUI 4! (if compiled in `Debug` mode).
* see [VST Development Notes (3.6.9) - Part 2](https://www.pongasoft.com/blog/yan/vst/2018/03/14/VST-development-notes-part2/) for details

Configuration and requirements
------------------------------
This project is known to work on macOS High Siera 10.13.3 with Xcode 9.2 installed. It also has been tested on Windows 10 64 bits and Visual Studio Build tools (2017). It requires `cmake` version 3.9 at the minimum. Because it uses `cmake` it should work on other platforms but it has not been tested.

Downloading the SDK
-------------------
You need to download the VST3 SDK from [steinberg](https://download.steinberg.net/sdk_downloads/vstsdk369_01_03_2018_build_132.zip) (3.6.9 as of 2018/03/01 and what is used in this project) (shasum 256 => `7c6c2a5f0bcbf8a7a0d6a42b782f0d3c00ec8eafa4226bbf2f5554e8cd764964`).

Installing the SDK
-------------------
Unpack the SDK to the following location (note how I renamed it with the version number)

* `/Users/Shared/Steinberg/VST_SDK.369` for macOS
* `C:\Users\Public\Documents\Steinberg\VST_SDK.369` for windows.

You can also store in a different location and use the `VST3_SDK_ROOT` variable when using cmake to define its location.

Configuring the SDK
-------------------
In order to build both VST2 and VST3 at the same time, you need to run the following commands

    # for macOS
    cd /Users/Shared/Steinberg/VST_SDK.369
    ./copy_vst2_to_vst3_sdk.sh

    # for Windows
    cd C:\Users\Public\Documents\Steinberg\VST_SDK.369
    copy_vst2_to_vst3_sdk.bat

Building this project for macOS
-------------------------------

- Create a folder for the build and `cd` to it (for simplicity I am creating it at the root of the source tree, but can obviously be *outside* the source tree entirely):

        mkdir -p build/Debug
        cd build/Debug

- Generate the Makefile(s): provide the path to the *source* of this project (which contains `CMakeLists.txt`):

        cmake -DCMAKE_BUILD_TYPE=Debug ../

- Now build the plugin (all its dependencies will be built as well):

        cmake --build .

- Testing that it is a valid VST3 plugin (already run part of the build, but can be run separately):

        > ./bin/validator VST3/pongasoft_ABSwitch.vst3

        * Loading module...

        	/tmp/vst3-again-build/VST3/pongasoft_ABSwitch.vst3

        * Scanning classes...

          Factory Info:
        	vendor = pongasoft
        	url = https://www.pongasoft.com
        	email = mailto:support@pongasoft.com

          Class Info 0:
        	name = ABSwitch VST
        	category = Audio Module Class
        	cid = 8D6054662515496785DDBB258AC01235

          Class Info 1:
        	name = ABSwitch VSTController
        	category = Component Controller Class
        	cid = 82AEA4A35B4E4A5FA3D68B1A8A1B69C5

        * Creating tests...

        * Running tests...
        ....

- Testing that it is a valid VST2 plugin (with [MrsWatson](https://github.com/teragonaudio/MrsWatson)):

        > mrswatson64 --display-info -p VST3/pongasoft_ABSwitch.vst3
        - 00000000 000001 MrsWatson version 0.9.8 initialized, build 20150122
        - 00000000 000001 Plugin 'VST3/pongasoft_ABSwitch.vst3' is of type VST2.x
        - 00000000 000001 Opening VST2.x plugin 'VST3/pongasoft_ABSwitch.vst3'
        - 00000000 000094 Information for VST2.x plugin 'pongasoft_ABSwitch.vst3'
        - 00000000 000094 Vendor: pongasoft
        - 00000000 000094 Version: 16973825
        - 00000000 000094 Unique ID: TBDx
        - 00000000 000094 Plugin type: effect, category 1
        - 00000000 000094 Version: 1
        - 00000000 000094 I/O: 2/2
        - 00000000 000094 InitialDelay: 0 frames
        - 00000000 000094 Parameters (0 total):
        - 00000000 000094 Programs (0 total):
        - 00000000 000094 Current program: ''
        - 00000000 000094 Common canDo's:
        - 00000000 000094   sendVstEvents: No
        - 00000000 000094   sendVstMidiEvent: No
        - 00000000 000094   receiveVstEvents: No
        - 00000000 000094   receiveVstMidiEvent: No
        - 00000000 000094   receiveVstTimeInfo: Yes
        - 00000000 000094   offline: Yes
        - 00000000 000094   midiProgramNames: No
        - 00000000 000094   bypass: No
        E 00000000 000094 Output source could not be opened, exiting

- Deploying the plugin and testing in a real DAW

    -  For VST2 (like Maschine and Reason) you copy and *rename* it:

            mkdir -p ~/Library/Audio/Plug-Ins/VST
            cp -r VST3/pongasoft_ABSwitch.vst3 ~/Library/Audio/Plug-Ins/VST/pongasoft_ABSwitch.vst

    -  For VST3:

            mkdir -p ~/Library/Audio/Plug-Ins/VST3
            cp -r VST3/pongasoft_ABSwitch.vst3 ~/Library/Audio/Plug-Ins/VST3

- You can also run the unit tests part of this project:

        cmake --build . --target VST_AB_Switch_test
        ctest

Because this project uses `cmake` you can also generate an Xcode project by using the proper generator (`-G Xcode`). You can also load the project directly in CLion.

Building this project for Windows
---------------------------------
- Create a folder for the build and `cd` to it (for simplicity I am creating it at the root of the source tree, but can obviously be *outside* the source tree entirely):

      mkdir build
      cd build

- Generate the Makefile(s): provide the path to the *source* of this project (which contains `CMakeLists.txt`):

      cmake -G"Visual Studio 15 2017 Win64" ../

- Now build the plugin (all its dependencies will be built as well) (note that unlike macOS the type of build is specified during the build not during the generation of the project):

      cmake --build . --config Release

Note that the validator will automatically run at the end of the build.

Building the archive (.zip)
---------------------------
A convenient script (`build-prod.sh` for macOS and `build-prod.bat` for Windows) will invoke the proper commands to build and zip the entire project for production release. This can be run in any directory and will create a `build` folder.

Misc
----
This project uses [loguru](https://github.com/emilk/loguru) for logging (included under `src/cpp/logging`)

Licensing
---------
GPL version 3
