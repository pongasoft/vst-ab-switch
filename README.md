VST2/3 A/B Switch
=================

This project is a VST implementation of the [A/B Audio Switch](https://pongasoft.com/rack-extensions/ABSwitch.html) rack extension. You can check the [A/B Switch](https://pongasoft.com/vst/ABSwitch.html) documentation directly.

This project is connected to the [VST Development Notes](https://www.pongasoft.com/blog/yan/vst/2018/03/12/VST-development-notes) blog post series.

Status for `master` (unreleased)
--------------------------------
* 2018-10-06 - Use of [jamba](https://github.com/pongasoft/jamba) framework. No new feature (easier to build and use common code).

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

Build this project
------------------

The following steps describes (for each platform) how to build the plugin.

### macOS

- For simplicity I am creating the build at the root of the source tree, but can obviously be *outside* the source tree entirely by running the script from anywhere

        ./configure.sh
        cd build

- In order to build, test, validate, etc... simply use the `jamba.sh` script (use `-h` for details):

         ./jamba.sh -h

- Testing that it is a valid VST2 plugin (with [MrsWatson](https://github.com/teragonaudio/MrsWatson)):

        > mrswatson64 --display-info -p VST3/Debug/pongasoft_ABSwitch.vst3
        - 00000000 000001 MrsWatson version 0.9.8 initialized, build 20150122
        - 00000000 000001 Plugin 'VST3/Debug/pongasoft_ABSwitch.vst3' is of type VST2.x
        - 00000000 000001 Opening VST2.x plugin 'VST3/Debug/pongasoft_ABSwitch.vst3'
        - 00000000 000011 Information for VST2.x plugin 'pongasoft_ABSwitch.vst3'
        - 00000000 000011 Vendor: pongasoft
        - 00000000 000011 Version: 16843264
        - 00000000 000011 Unique ID: jobi
        - 00000000 000011 Plugin type: effect, category 1
        - 00000000 000011 Version: 1
        - 00000000 000011 I/O: 6/2
        - 00000000 000011 InitialDelay: 0 frames
        - 00000000 000011 Parameters (2 total):
        - 00000000 000011   0: 'Audio Switch' (0.000000)
        - 00000000 000011   1: 'Soften' (1.000000)
        - 00000000 000011 Programs (0 total):
        - 00000000 000011 Current program: ''
        - 00000000 000011 Common canDo's:
        - 00000000 000011   sendVstEvents: No
        - 00000000 000011   sendVstMidiEvent: No
        - 00000000 000011   receiveVstEvents: No
        - 00000000 000011   receiveVstMidiEvent: No
        - 00000000 000011   receiveVstTimeInfo: Yes
        - 00000000 000011   offline: Yes
        - 00000000 000011   midiProgramNames: No
        - 00000000 000011   bypass: No
        E 00000000 000011 Output source could not be opened, exiting

### Windows

- For simplicity I am creating the build at the root of the source tree, but can obviously be *outside* the source tree entirely by running the script from anywhere. Note that PowerShell is highly recommended.

        .\configure.bat
        cd build

- In order to build, test, validate, etc... simply use the `jamba.bat` script (use `-h` for details):

         .\jamba.bat -h

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
This project uses [loguru](https://github.com/emilk/loguru) for logging.

Licensing
---------
GPL version 3
