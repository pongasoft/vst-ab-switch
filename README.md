VST2/3 A/B Switch
=================

This project is a VST implementation of the [A/B Audio Switch](https://pongasoft.com/rack-extensions/ABSwitch.html) rack extension.

It is, at the moment, a work in progress but is being released early in connection with the [VST Development Notes](https://www.pongasoft.com/blog/yan/vst/2018/02/17/VST-development-notes) blog post series.

2018-03-10 - Status for tag `blog-part2`
----------------------------------------
* the plugin compiles while depending on the SDK (following this other project [vst3-again-sample](https://github.com/pongasoft/vst3-again-sample))
* the processing part is doing exactly what the [vst24-hello-world](https://github.com/pongasoft/vst24-hello-world) plugin is doing: simply removing 3dB by multiplying every sample by 0.5 (as a way to check that the processing part is being executed properly)
* the controller part (UI) is a black square and by right clicking in it you can enter the inline UI editor that comes built-in with VSTGUI 4! (if compiled in `Debug` mode).
* see [VST Development Notes - Part 2](https://www.pongasoft.com/blog/yan/vst/2018/03/10/VST-development-notes-part2/) for details

Licensing
---------
GPL version 3
