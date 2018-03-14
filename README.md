VST2/3 A/B Switch
=================

This project is a VST implementation of the [A/B Audio Switch](https://pongasoft.com/rack-extensions/ABSwitch.html) rack extension.

It is, at the moment, a work in progress but is being released early in connection with the [VST Development Notes](https://www.pongasoft.com/blog/yan/vst/2018/03/12/VST-development-notes) blog post series.

2018-03-13 - Status for tag `blog-part2-369`
--------------------------------------------
* the plugin uses SDK 3.6.9
* the plugin compiles while depending on the SDK (following this other project [vst3-again-sample](https://github.com/pongasoft/vst3-again-sample))
* the processing part is doing exactly what the [vst24-hello-world](https://github.com/pongasoft/vst24-hello-world) plugin is doing: simply removing 3dB by multiplying every sample by 0.5 (as a way to check that the processing part is being executed properly)
* the controller part (UI) is a black square and by right clicking in it you can enter the inline UI editor that comes built-in with VSTGUI 4! (if compiled in `Debug` mode).
* see [VST Development Notes (3.6.9) - Part 2](https://www.pongasoft.com/blog/yan/2018/03/14/VST-development-notes-part2/) for details

Configuration and requirements
------------------------------
This project is known to work on macOS High Siera 10.13.3 with Xcode 9.2 installed. It requires `cmake` version 3.9 at the minimum. Because it uses `cmake` it should work on other platforms but it has not been tested.

Downloading the SDK
-------------------
You need to download the VST3 SDK from [steinberg](https://download.steinberg.net/sdk_downloads/vstsdk369_01_03_2018_build_132.zip) (3.6.9 as of 2018/03/01 and what is used in this project) (shasum 256 => `7c6c2a5f0bcbf8a7a0d6a42b782f0d3c00ec8eafa4226bbf2f5554e8cd764964`).

Installing the SDK
-------------------
Unpack the SDK to a location of your choice (in my case the SDK is unpacked and renamed `/Applications/VST_SDK.368/`).

Configuring the SDK
-------------------
In order to build both VST2 and VST3 at the same time, you need to run the following commands

    cd /Applications/VST_SDK.369/
    ./copy_vst2_to_vst3_sdk.sh

Building this project
---------------------

- Create a folder *outside* the source tree and `cd` to it:

        mkdir -p /tmp/vst-ab-switch-build/Debug
        cd /tmp/vst-ab-switch-build/Debug

- Generate the Makefile(s): `VST3_SDK_ROOT` needs to point to the root of the VST3 SDK (as installed/configured previously) and provide the path to the *source* of this project (which contains `CMakeLists.txt`):

        cmake -DVST3_SDK_ROOT=/Applications/VST_SDK.369/VST3_SDK -DCMAKE_BUILD_TYPE=Debug /Volumes/Development/github/org.pongasoft/vst-ab-switch

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

Because this project uses `cmake` you can also generate an Xcode project by using the proper generator (`-G Xcode`). You can also load the project directly in CLion.

Licensing
---------
GPL version 3
