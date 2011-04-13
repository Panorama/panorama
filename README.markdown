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

Once you have these tools, you should get hold of the latest version of the
Panorama source code distribution, which you can do by going to the
[GitHub repository][github] for Panorama. You'll also need the Pandora
libraries that are used for PND software package integration. These are
available in [another git][pandora-libraries] which you should clone to
to the pandora-libraries subdirectory.

Then, do the following:

*   Run `qmake` for the Qt version you used. If you want to disable OpenGL
    rendering for compatibility reasons use `qmake CONFIG+=disable_opengl panorama.pro`
*   Run `gmake` (or `make`). You should now have the `panorama` executable in the panorama/target directory.

Further documentation
---------------------
If you want to find out more about Panorama, please visit the project's
[Wiki][]. There, you will find guides for creating new Panorama UIs or extending
the project.

[ccbysa]: http://creativecommons.org/licenses/by-sa/3.0/ (Creative Commons Attribution Share-Alike)
[openpandora]: http://openpandora.org/ (OpenPandora - The OMAP3 based Handheld)
[git]: http://git-scm.com/ (Git)
[github]: http://github.com/bzar/panorama (GitHub)
[pandora-libraries]: https://github.com/dflemstr/pandora-libraries
[wiki]: http://wiki.github.com/dflemstr/panorama (Wiki)
