README
======

This is the source distribution for the Panorama project. It is licensed under the
[Creative Commons Attribution Share-Alike][ccbysa] license.

About
-----

Panorama is an application lanucher written in Qt for the [OpenPandora][] portable
gaming platform. The focus lies on creating an extremely portable, modular and
extensible system that also is visually appealing and uses little resources. Having
intuitive controls and an efficient usage of screen real estate is also a primary
goal.

Building the source code
------------------------

You will need the following tools and resources to compile Panorama:

*   A C++ compiler
*   [Git][]
*   Qt 4.7 or later

If you for some reason don't have access to Qt 4.7 (because it doesn't exist yet,
for instance), do the following to gain access to Qt 4.6.1
and the Kinetic DeclarativeUI branch, which works just as well:

*   Clone [the Gitorious Qt Kinetic Git repository][qtrepo].
*   Check out the `kinetic-declarativeui` branch. Try `kinetic-bauhaus` instead if `kinetic-declartiveui` won't compile.
*   Compile the distribution via the usual `./configure; gmake -j4; gmake install`
    procedure. Note that this will take quite some time.

Once you have these tools, you should get hold of the latest version of the
Panorama source code distribution, which you can do by going to the
[GitHub repository][github] for Panorama.

Then, do the following:

*   Run `qmake` for the Qt version you used. If you compiled Qt 4.6.1 and are
    on Linux, enter the panorama source directory and invoke
    `/usr/local/Trolltech/Qt-4.6.1/bin/qmake`.
*   Run `gmake` (or `make`). You should now have the `panorama` executable.

Further documentation
---------------------
If you want to find out more about Panorama, please visit the project's
[Wiki][]. There, you will find guides for creating new Panorama UIs or extending
the project.

[ccbysa]: http://creativecommons.org/licenses/by-sa/3.0/ (Creative Commons Attribution Share-Alike)
[openpandora]: http://openpandora.org/ (OpenPandora - The OMAP3 based Handheld)
[git]: http://git-scm.com/ (Git)
[qtrepo]: git://gitorious.org/+qt-kinetic-developers/qt/kinetic.git (Qt Kinetic on Gitorious)
[github]: http://github.com/dflemstr/panorama (GitHub)
[wiki]: http://wiki.github.com/dflemstr/panorama (Wiki)
