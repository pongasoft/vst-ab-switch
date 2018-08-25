VST2/3 A/B Switch
=================

This project is a VST implementation of the [A/B Audio Switch](https://pongasoft.com/rack-extensions/ABSwitch.html) rack extension. You can check the [A/B Switch](https://pongasoft.com/vst/ABSwitch.html) documentation directly.

This project is connected to the [VST Development Notes](https://www.pongasoft.com/blog/yan/vst/2018/03/12/VST-development-notes) blog post series.

Status for `master` (unreleased)
--------------------------------
* 2018-08-05 - Use of [jamba](https://github.com/pongasoft/jamba) framework

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
Check the Jamba [README](https://github.com/pongasoft/jamba/blob/master/README.md) file for instructions on how to install and configure the VST3 SDK.

Building this project for macOS
-------------------------------

- For simplicity I am creating the build at the root of the source tree, but can obviously be *outside* the source tree entirely by running the script from anywhere

        ./configure.sh Debug
        cd build/Debug

- In order to build the plugin run:

        ./build.sh

- In order to validate the plugin (uses validator) run:

        ./validate.sh

- In order to edit the plugin UI (uses editor) run:

        ./edit.sh

- In order to install the plugin locally run (~/Library/Audio/Plug-Ins/VST for VST2 and ~/Library/Audio/Plug-Ins/VST3 for VST3):

        ./install.sh

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

Because this project uses `cmake` you can also generate an Xcode project by using the proper generator (`-G Xcode`). You can also load the project directly in CLion.

Building this project for Windows
---------------------------------

- For simplicity I am creating the build at the root of the source tree, but can obviously be *outside* the source tree entirely by running the script from anywhere

        ./configure.bat
        cd build

- In order to build the plugin run:

        For Debug => ./build.bat
        For Release => ./build.bat Release

- In order to validate the plugin (uses validator) run:

        For Debug => ./validate.bat
        For Release => ./validate.bat Release

- In order to edit the plugin UI (uses editor) run:

        ./edit.sh

- In order to install the plugin:

  For VST2, copy VST3/ABSwitch.vst3 and RENAME into ABSwitch.dll under
  - C:\ProgramFiles\VstPlugins
  - or any DAW specific path (64bits)
  - MAKE SURE TO RENAME the file otherwise it will not work

  For VST3, copy ABSwitch.vst3 under
  - C:\Program Files\Common Files\VST3 (may require admin access)
  - or any DAW specific path (64bits)

Building the archive (.zip)
---------------------------
A convenient script (`build-prod.sh` for macOS and `build-prod.bat` for Windows) will invoke the proper commands to build and zip the entire project for production release. This can be run in any directory and will create a `build` folder.

Parameters
----------
These are the parameters used by this plugin:

    | ID   | TITLE        | TYP | OW | TRS | SHA | DEF.N | DEF.S         | STP | FLG | SHORT  | PRE | UID | UNS |
    -------------------------------------------------------------------------------------------------------------
    | 1000 | Audio Switch | vst | rt |     |     | 0.000 | A             | 1   | 1   | Switch | 4   | 0   |     |
    -------------------------------------------------------------------------------------------------------------
    | 1010 | Soften       | vst | rt |     |     | 1.000 | On            | 1   | 1   | Soft   | 4   | 0   |     |
    -------------------------------------------------------------------------------------------------------------
    | 1020 | Audio On     | vst | rt | x   |     | 0.000 | Off           | 1   | 2   |        | 4   | 0   |     |
    -------------------------------------------------------------------------------------------------------------
    | 500  | Label A      | jmb | ui |     |     |       | Input Label A |     |     |        |     |     |     |
    -------------------------------------------------------------------------------------------------------------
    | 501  | Label B      | jmb | ui |     |     |       | Input Label B |     |     |        |     |     |     |
    -------------------------------------------------------------------------------------------------------------

Misc
----
This project uses [loguru](https://github.com/emilk/loguru) for logging (included under `src/cpp/logging`)

Licensing
---------
GPL version 3
