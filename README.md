Xcode-Proj-Adder
================

Add files to your Xcode project from command line

When building Xcode projects from command line it is surprising to find that there is currently no way to add files to a project without going through the GUI. So… here is this quick tool to add existing files an Xcode project through OSX command line.

Currently supports adding these types of files
.h .m .cpp .swift .png .jpg .mp3 .ttf .ogg

If you just want the prebuilt tool, it is available in the 'bin' directory.

**Usage:**
Run from terminal/script setting the -XCP argument along with one of the other two arguments.

`-XCP` : Fully qualified path of ‘.xcodeproj’ (the project you want to add files to)

`-SCSV` : CSV list of source file locations relative to the .xcodeproj file

`-RESTORE` : removes files added since last run


**Example:**

**Add Source files**

`$ ./XcodeProjAdder -XCP "Full Path to .xcodeproj" -SCSV "csv of source file locations relative to xcode .xcodeproj"`

`$ ./XcodeProjAdder -XCP /Users/jimjohn/Products/TestProj.xcodeproj -SCSV ../tst1.cpp,../tst2.cpp,../tst1.h`

**Restore project to state before files were added**

`$ ./XcodeProjAdder -XCP "Full Path to .xcodeproj" -RESTORE`

`$ ./XcodeProjAdder -XCP /Users/jimjohn/Products/TestProj.xcodeproj -RESTORE`


This project is made available under the DON'T BE A DICK PUBLIC LICENSE (http://www.dbad-license.org/)