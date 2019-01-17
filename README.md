# Image2Geometry
Implementation of PHOR paper image-to-geometry registration method in C++ on common desktop computers for result replication.

# Disclaimer
This repository is **not** containing the "Geological Registration and Interpretation Toolset" (GRIT) for mobile devices, as that software is kind-of behind a paywall from petroleum industry consortium funding institutions and companies - sorry to disappoint, but I have little hope this will *ever* get public.

This repository only includes the specific image-to-geometry registration method published openly in "The Photogrammetric Record" (volume 32, issue 158) 
and in the ISPRS Annals (volume 3, issue 2) and related academic publications (see CITATION.md). As such, and as part of an also publically-funded 
project, it is my obligation and privilege to provide a reference implementation of how we do the 2D-3D registation for images captured by mobile 
device cameras. The code is *just* a simple and straight end-to-end implementation without any precautions on engineering finesse or runtime 
improvement. It is given as-is without guarantees or liability of any sort - experiment on you own duty with it.

The code is checked to compile and work in the following systems:
Ubuntu 12.0.5 - gcc 3.49
Ubuntu 14.04 - gcc 4.9
Ubuntu 18.04 - gcc 8.1
MinGW 64 (requiring you to have the necessary thrird-party libraries somewhere) - gcc-8.1

The code as-is will **not** compile in Visual Studio (vc compiler - any version), as we use high-density linear algebra packages. The configuration has 
been tested and it breaks due to the lack of a .lib/.dll generation from armadillo, which this build requires.

Sending in a compilation success with Cygwin would be appreciated.

The provided license applies to further usage, embedding and sharing (and alike) of this specific software and its contents.
