Python Bindings
===============
The Python bindings define a collection of modules, where each module
wraps a subset of the libopenflow library. Currently, there are three
modules:

* flog - Contains the basic facilities in the flog namespace.
* flog_ofp_v1_0 - Wraps the message structures in v1.0 of the OFP protocol.
* flog_ofp_v1_1 - Wraps the message structures in v1.1 of the OFP protocol.

Each module is self-contained. It depends on no other modules (it includes
the others, but does not import them).

Each module is specied in a .i file. The contents of the file match (or
approximate) the declarations in the message.hpp file. A module is loaded
from Python as:

    import flog
    import flog_ofp_v1_0

Some effort, but not enough, has been put into language naturalization -- that
is, the set of functions that would make these data structures interoperate
cleanly with common Python idioms. This is a work in progress.

In order to use the Python bindings, the compiled modules must be in the
interpreters search path. These are currently not installed by the build system
and must be manually configured.  This can be done (in Linux and Mac OS X) by
setting the PYTHONPATH environment variable to the build location of the
bindings ($FLOG_ROOT/build/bindings/ofp).

New Modules
===========
Just copy the message header into a .i file, and modify it so that it looks
like the others (the SWIG preamble, etc). Remove all of the function
implementations, and enum initializers.


Notes
=====
This are significant redundancies in the design. Each protocol version
also includes (and re-declares) bindings in the top-level namespace and
the ofp namespace. This could be avoided by a more careful restructuring,
but this actually seemed the best way to do it.

Running Python (on Linux)
=========================
No additional requirements are needed.


Running Python (on Mac)
=======================
When using g++-mp-4.8 on Mac OS X, you must ensure that the C++11 standard
library is in your DYLD_LIBRARY_PATH before running Python scripts that
import any of the flog modules. For example:

    $ export DYLD_LIBRARY_PATH=/opt/local/lib:$DYLD_LIBRARY_PATH
    $ ofp_test.py <args>

Without this, the Python interpreter will crash, probably claiming a double
allocation due to the use of conflicting C++ runtimes.


Future Work
===========
There are a number of remaining problems to be solved.

=== Naturualization and Wrapping ===
Make the bindings more idiomatic for their respective languages.

=== System and Application Interfaces ===
Integrate the system and application interfaces with the bindings. How do
we create new OpenFlow applications in Python?

=== Remodularization ===
This is an workable pass on the Python bindings, but not especially elegant
It would be ideal if the bindings could be modularized in a similar way to
the libopenflow library, but there have been some technical difficulties.
In particular, we have thusfar been unable to make Python import .so libraries
when they appear in different directories. Experimentation continues.

=== Ruby Bindings ===
TODO

=== Java Bindings ===
TODO
