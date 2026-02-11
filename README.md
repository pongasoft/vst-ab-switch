> [!Warning]
> This project is now hosted on [Codeberg](https://codeberg.org/pongasoft/vst-ab-switch)

VST2/3 A/B Switch
=================

This project is a VST implementation of the [A/B Audio Switch](https://pongasoft.com/rack-extensions/ABSwitch.html) rack extension. You can check the [A/B Switch](https://pongasoft.com/vst/ABSwitch.html) documentation directly.

This project is connected to the [VST Development Notes](https://www.pongasoft.com/blog/yan/vst/2018/03/12/VST-development-notes) blog post series.

### Unreleased - `master`

* Upgraded to [Jamba](https://github.com/pongasoft/jamba) 7.1.3 / VST3 SDK 3.7.12
* Removed support for VST2

> [!NOTE]
> This version is not released because there are no new features or bug fixes, and since
> it removes support for VST2, it is not released at the moment.
> `master` has been updated to the latest version of Jamba / VST3 SDK so that it compiles with
> more recent versions of macOS / Windows.

2021-01-04 - Status for tag `v1.1.3`
------------------------------------
* Use of [jamba](https://github.com/pongasoft/jamba) framework and VST SDK 3.7.0
* Use of `ParamImageView` for LED status lights
* Added support for Audio Unit
* Added support for Apple Chipset / universal build on macOS

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

The following steps describes how to build the plugin: 

1. Invoke the `configure.py` python script to configure the project
2. Run the `jamba.sh` (resp. `jamba.bat`) command line to build, test validate...

### macOS

For simplicity I am creating the build at the root of the source tree, but can obviously be *outside* the source tree entirely by running the script from anywhere

```
> ./configure.py -h # to see the help
> ./configure.py
> cd build
> ./jamba.sh -h
```

### Windows

For simplicity I am creating the build at the root of the source tree, but can obviously be *outside* the source tree entirely by running the script from anywhere. Note that PowerShell is highly recommended.

```
> python configure.py -h # to see the help
> python configure.py
> cd build
> .\jamba.bat -h
```

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
