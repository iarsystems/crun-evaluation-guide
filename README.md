# Evaluation Guide for IAR C-RUN


<!-- --------------------------------------------------------------------------------------------------- -->
## What is C-RUN?
[C-RUN](https://iar.com/crun) is an add-on runtime analysis tool completely integrated into IAR Embedded Workbench. It helps you to ensure code quality in your C and C++ code by inserting efficient instrumentation code into the application for automatic runtime error checking capabilities.

<!-- ![image](https://user-images.githubusercontent.com/54443595/222785546-f0f2a98f-24b5-4d05-a341-6ecd8cc6e84a.png) -->


<!-- --------------------------------------------------------------------------------------------------- -->
## What is this guide?
This guide contains a walkthrough for evaluating the runtime error checking capabilities offered by C-RUN.

You can evaluate C-RUN right now free of charge with a 14-day time-limited trial version of IAR Embedded Workbench for Arm or IAR Embedded Workbench for Renesas RX. Register and download using the corresponding links provided in the _Software Requirements_ table, under _Required License Types_, for the target architecture of your choosing.


<!-- --------------------------------------------------------------------------------------------------- -->
## Software requirements
This guide works for any of these products, given that the requirements are met:
| __Product__ | __Target architecture__ | __Required version__ | __Required license types__ |
| - | - | - | - |
| IAR Embedded Workbench | [Arm](https://iar.com/ewarm) | 8.11 or later | - Cortex-M, or<br>- Standard, or<br>- Extended, or<br>- [Time-limited trial version](https://www.iar.com/products/architectures/arm/iar-embedded-workbench-for-arm/iar-embedded-workbench-for-arm---free-trial-version/) |
| IAR Embedded Workbench | [Renesas RX](https://iar.com/ewrx) | 5.10 or later | - Standard, or<br>- [Time-limited trial version](https://www.iar.com/products/architectures/renesas/iar-embedded-workbench-for-renesas-rx/iar-embedded-workbench-for-renesas-rx---free-trial-version/) |

> [!NOTE]
> No special action needs to be taken when you evaluate C-RUN in code-size-limited mode using the time-limited trial version. This special mode was created to allow customers to evaluate C-RUN using smaller pieces of code while exploring its tight integration with the IAR C-SPY Debugger.

> [!TIP]
> For access to a non-limited license [contact](https://iar.com/contact) your IAR representative.

<!-- --------------------------------------------------------------------------------------------------- -->
## Exploring C-RUN
A number of example projects, created as demonstrations of the feature set offered by C-RUN, can be found in this repository.

To run the examples:

1. Clone this repository, or download the [latest release](https://github.com/IARSystems/crun-evaluation-guide/releases/latest).
2. Launch the IAR Embedded Workbench IDE for a supported target architecture.
3. Open the `Workspace.eww` file, found in the folder for the desired target architecture.

The workspace will launch with a pre-selected project. In the workspace __Overview__ there are tabs for switching from one project to another:

![image](https://github.com/IARSystems/crun-evaluation-guide/assets/54443595/56bdb6c8-aef4-4605-90fb-e6835de579f9)

> [!TIP]
> The arrow buttons scroll to tabs that did not fit into the window width. The window can be resized. Alternatively, right-click a project in the __Overview__ and choose __Set as active__ from the context menu.

Below you will find specific instructions for running each of these projects.





<!-- --------------------------------------------------------------------------------------------------- -->
### Arithmetic Checking
The first example explores the most straightforward functionality in C-RUN: the _Arithmetic_ checks.

To run this example, do this:

1. Select the _Arithmetic_ project in the workspace window.

2. Choose __Project__ → __Options__ (<kbd>Alt</kbd>+<kbd>F7</kbd>) → __Runtime Checking__.

3. Make sure that __C-RUN Runtime Checking__ is enabled

![image](https://github.com/IARSystems/crun-evaluation-guide/assets/54443595/79e69f03-a87c-4c75-afbf-fc210562554d)

4. Make sure all these checks are selected:

![image](https://github.com/IARSystems/crun-evaluation-guide/assets/54443595/80cd14e7-7deb-43b1-9313-d3e7b13929f1)

5. Click `  OK  ` to close the __Project Options__ dialog box.

6. Choose __Project__ → __Download and Debug__ (<kbd>Ctrl</kbd>+<kbd>D</kbd>) to start executing the application.

7. The C-SPY Debugger will hit a breakpoint at `main()`. Press <kbd>F5</kbd> to resume the program execution.

8. The execution will _Stop_, with the following line of code highlighted:

![image](https://github.com/IARSystems/crun-evaluation-guide/assets/54443595/5737b5b0-2b25-4b67-9242-07a4e4bb0fa3)

>In the editor window, C-SPY highlights in green the statement in which the execution stopped when the runtime error checking was triggered. In addition, C-RUN narrows the problem down and highlights the root cause of the runtime error.

![image](https://user-images.githubusercontent.com/54443595/223120962-c875ed49-8322-4a44-b296-5decd196b6df.png)

> Concurrently, the __C-RUN Messages__ window (__View__ → __C-RUN__ → __Messages__) will break down the detected runtime error as well as its call stack. Clicking on the call stack takes you to the corresponding source code line.

9. Examine the remaining detected errors by pressing <kbd>F5</kbd> to resume the program execution until the next error message, or until the execution ends.

![image](https://github.com/IARSystems/crun-evaluation-guide/assets/54443595/2604cd6e-9f49-4ac2-949e-a3379f4cfdb3)

10. Stop the debug session (<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd>).

11. When you create applications, there are situations where relying on the wrap-around property of overflown unsigned integers is efficient. In such cases, specific C-RUN checks can simply be deselected. In the project's __Runtime checking__ options, disable these:

![image](https://github.com/IARSystems/crun-evaluation-guide/assets/54443595/3ec8fa7d-53e3-42ed-9df6-5e79406b5bc1)

12. Rebuild, then __Download and Debug__ (<kbd>Ctrl</kbd>+<kbd>D</kbd>) the application.
> Disabling the checks you do not need will generally make execution faster and decrease the code size. 

13. By default, C-RUN will __Stop__ at each detected error. In the __C-RUN Messages__ window, the _Default action_ can be changed to __Log__ or __Ignore__.

> [!NOTE]
> __C-RUN Messages__ can be filtered by rules. For details, refer to the _Creating rules for messages_ section in the _C-SPY Debugging Guide_.





<!-- --------------------------------------------------------------------------------------------------- -->
### Bounds checking
The second example explores the _Bounds Checking_ capabilities provided by C-RUN.

To run this example, do this:

1.  Select the _Bounds-checking_ project.

2. Choose __Project__ → __Download and Debug__ (<kbd>Ctrl</kbd>+<kbd>D</kbd>) to start executing the application.

3. After the execution reaches the breakpoint in the `main()` function, resume the execution (<kbd>F5</kbd>).
> Note how the application finishes executing (`exit()`) without any apparent errors of any kind.

4. Stop the debug session (<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd>).

5. Choose __Project__ → __Options__ (<kbd>Alt</kbd>+<kbd>F7</kbd>) → __Runtime Checking__ and _enable bounds checking_:

![image](https://github.com/IARSystems/crun-evaluation-guide/assets/54443595/9581c3f2-ab79-4f4b-9ab4-d0ce0b350e22)

6. Rebuild and run the project.

![image](https://github.com/IARSystems/crun-evaluation-guide/assets/54443595/bfd4cb27-f942-4cc4-a690-418ae14b8cf5)

> Note that now C-RUN highlighted an out-of-bounds access for `*(ap+2)`. However, the execution stopped earlier, at the first `printf()` statement. The reason is that the compiler determines that pointer addresses used as parameters for those `printf()` calls are related and, with that, C-RUN efficiently can test them in one go.

7. Press <kbd>F5</kbd> to resume the execution and inspect the remaining C-RUN Message:

![image](https://github.com/IARSystems/crun-evaluation-guide/assets/54443595/b50e1834-0da8-42b3-a0ba-f375dd21c50c)

> [!TIP]
> It will stop at the last statement of the application, indicating that the assignment is performed out of bounds. From a bounds-checking perspective, dynamically allocated memory is no different from local pointers, static buffers, or buffers on the stack.

8. Again, choose __Project__ → __Options__ (<kbd>Alt</kbd>+<kbd>F7</kbd>) → __Runtime Checking__ and take a look at the __Global bounds table__ group box.

![image](https://github.com/IARSystems/crun-evaluation-guide/assets/54443595/f84c7f68-9a58-4717-b605-3732aed4500c)

Pointers that can be accessed through other pointers must have information in a table stored in memory. The __Number of entries__ field allows you to fine-tune the number of slots available in the table.

> [!WARNING]
> Leaving __Number of entries__ blank will remove the limit, resulting in a large global bounds table (4k slots!). The number of entries you need is often fairly low, so you might want to experiment with shrinking the global table, to lower the resource consumption for the instrumentation. Do not worry if you use a number that is too low; if this happens, you will get a warning message telling you that the global bounds table is running out of slots.

9. Set the __Number of entries__ to `1   ` and close the __Project Options__ dialog box.

10. Rebuild, and __Download and Debug__ (<kbd>Ctrl</kbd>+<kbd>D</kbd>) the application.
> In this example, there is only one pointer that needs to be kept in the table, so a single entry is enough.





<!-- --------------------------------------------------------------------------------------------------- -->
### Bounds checking and libraries
In scenarios where the main project relies on pre-built (third-party) libraries, _bounds checking_ requires extra consideration for shared pointers.

The project _Bounds-checking+libs_ is a modified version of the _Bounds-checking_ project. The functionality available from the `IntMax.c` file was moved to a _Library project_ that produced a static library named `MaxLib.a`, pre-built with no C-RUN bounds-checking instrumentation, typical for third-party libraries where the code cannot be changed. 

When you use pointers and pointer arguments between the _instrumented application code_ and the _non-instrumented library code_, you must inform the compiler (and linker) that functions in the library code do not have bounds-checking information. The best way to do so is to use the `#pragma default_no_bounds` directive when including a library header, to inform the compiler that the library was not built with C-RUN Bounds-checking information:

![image](https://github.com/IARSystems/crun-evaluation-guide/assets/54443595/788c9bba-3610-4197-a9c5-43b7beb01e0c)

To run this example, do this:

1. Select the  _Bounds-checking+libs_ project.
>This project comes with two build configurations, with different options for C-RUN:
> - `DoNotCheckPointersFromNonInstrumentedCode` and 
> - `CheckPointersFromNonInstrumentedCode`

2. Begin with the `DoNotcheckPointersFromNonInstrumentedCode` build configuration.
>At the top of the __Workspace__ window, you can switch between existing build configurations.

3. Choose __Project__ → __Options__ (<kbd>Alt</kbd>+<kbd>F7</kbd>) → __Runtime Checking__ and confirm these settings:

![image](https://github.com/IARSystems/crun-evaluation-guide/assets/54443595/634f5447-51af-440e-95e2-b322a8e57011)

4. Close the __Project Options__ dialog box, and choose __Project__ → __Download and Debug__ (<kbd>Ctrl</kbd>+<kbd>D</kbd>) to start executing the application.
>You should get no C-RUN errors, or any other indications that something is wrong. In the `DoNotCheckPointersFromNonInstrumentedCode` build configuration, turning off bounds-checking information for library headers worked well- (As it should do in most cases; returned pointers will not be bounds-checked but will have associated bounds that are always "large enough" to accommodate them.) In other words, this means that pointers originating from your code will be checked, but not pointers from the library. This should normally be perfectly acceptable and the process is non-intrusive in terms of code changes.

5. Stop the debug session (<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd>).
 
6. Switch to the `CheckPointersFromNonInstrumentedCode` build configuration.
>The `CheckPointersFromNonInstrumentedCode` build configuration demonstrates a situation where it is desirable to have _bounds checking_ for pointers and returned pointers defined in the library code.

7. Choose __Project__ → __Options__ (<kbd>Alt</kbd>+<kbd>F7</kbd>) → __Runtime Checking__ and make sure that the __C-RUN Runtime Checking__ options are:

![image](https://github.com/IARSystems/crun-evaluation-guide/assets/54443595/7a16881f-d9ed-4ebd-8296-af3be6f198bc)

8. Build and run the application again. This time you should see one C-RUN message for the third `printf()` statement.
>Read the source code and compare the use of `__as_make_bounds()` for the pointer `ap` to how the bounds are set for the pointer used in the next `printf()` statement. We have also defined a project-specific macro to control the use of `__as_make_bounds()`. This built-in function is used when the returned pointer must be given sensible bounds. If no bounds are given for returned pointers, a bounds error will be generated on the first access made to the pointer. Note that this build configuration defines a preprocessor symbol called `CONFIG` that conditionally compiles with `__as_make_bounds()` calls to give pointers sensible bounds.
9. Comment out one of the calls to the `CRUN_MAKE_BOUNDS()` macro, rebuild and run.
>:grey_question: Did it change the output in the __C-RUN Messages__ window?





<!-- --------------------------------------------------------------------------------------------------- -->
### Heap checking capabilities
C-RUN can check for errors in how heap memory is being used. _Heap checking_ can catch when the application tries to use already freed memory, non-matching deallocation attempts, and leaked heap blocks.

When you use _heap checking_, each memory block is expanded with bookkeeping information and a buffer area, so that the blocks as seen by the application are not located side-by-side.

The various checker functions examine the bookkeeping information and the buffer areas and report violations of correct heap usage.

> [!WARNING]
> - Using _heap checking_ makes it much easier to find heap usage errors, but it is **not** fail-safe.
> - _Heap checking_ and _bounds checking_ can complement each other in identifying dynamic memory usage errors. However, because of the potential impact in terms of performance and overhead, you are advised **not** to enable both at the same time.

To run this example, do this:

1. Select the _Heap_ project.

2. Choose __Project__ → __Options__ (<kbd>Alt</kbd>+<kbd>F7</kbd>) → __Runtime Checking__.

3. Make sure that _Use checked heap_ is enabled:

![image](https://github.com/IARSystems/crun-evaluation-guide/assets/54443595/c3f62008-cfcc-4525-919e-cef032226551)

4. Choose __Project__ → __Download and Debug__ (<kbd>Ctrl</kbd>+<kbd>D</kbd>) to start executing the application.

5. Examine the source code comments for each reported error.

![image](https://github.com/IARSystems/crun-evaluation-guide/assets/54443595/36ccd11f-7037-4e81-b4e3-f6626ac60936)

6. Stop the debug session (<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd>).

>[!NOTE]
>The function `HeapFunc3()` in `Heap.c` can be enabled by uncommenting the `CRUN_FULL_EDITION` macro definition. The function requires a full edition of C-RUN since its resource consumption will exceed the code size limitation in the time-limited trial version. [Contact us](https://www.iar.com/about/contact) in case you need the full license or a demonstration.





<!-- --------------------------------------------------------------------------------------------------- -->
# Using C-RUN in non-interactive mode
There are scenarios in which might not be possible to debug an application built with C-RUN information directly from the IDE. Below you will find some examples on how to use C-RUN in non-interactive mode.


## C-RUN Runtime Analysis from the command line
The IAR C-SPY Command Line Utility (`cspybat`) can run applications directly from the command line. This utility is suitable for non-interactive debugging and can be used in conjunction with IAR C-RUN where runtime analysis is desired. One typical scenario for considering `cspybat` is within automated tests from a continuous integration environment. In this example, we will use the `Heap` project.

1. Close the IDE, launch a __Command Prompt__ shell and change to the `Heap` project's folder.
```
cd \path\to\crun-evaluation-guide\arm
```

>[!TIP]
> You will notice that, in this project's `settings/` folder, the IDE automatically generated four files for each project(/build configuration):
>
> | File                          | Description                                                     | Example
> | -                             | -                                                               | -
> | `<project>.<cfg>.cspy.bat`    | Batch script for executing the application using `cspybat`      | `Heap.Debug.cspy.bat`
> | `<project>.<cfg>.cspy.ps1`    | PowerShell script for executing the application using `cspybat` | `Heap.Debug.cspy.ps1`
> | `<project>.<cfg>.general.xcl` | Extended command line (`*.xcl`) containing general options      | `Heap.Debug.general.xcl`
> | `<project>.<cfg>.driver.xcl`  | Extended command line (`*.xcl`) containing backend/driver options       | `Heap.Debug.driver.xcl`
> 
>Inspect the scripts and its accompanying files and you will see all project parameters that are needed to execute the application using `cspybat`.

2. Use the option `--rtc_enable` to enable C-RUN in `cspybat`.
```
echo --rtc_enable >> settings\Heap.Debug.general.xcl
```

3. Execute the batch script.
```
settings\Heap.Debug.cspy.bat
```

<details><summary><b>Expected output example</b> (click to expand)</summary>
 
>```
>C:\crun-evaluation-guide\arm>settings\Heap.Debug.cspy.bat
>
>C:\crun-evaluation-guide\arm\settings>"C:\IAR\EW\ARM\9.50.2\common\bin\cspybat"
>-f "C:\crun-evaluation-guide\arm\settings\Heap.Debug.general.xcl"
>--backend -f "C:\crun-evaluation-guide\arm\settings\Heap.Debug.driver.xcl"
>
>     IAR C-SPY Command Line Utility V9.3.2.12345
>     Copyright 2000-2024 IAR Systems AB.
>
>Heap usage error @ 0x227a Core: 0
>The address 0x20001249 does not appear to be the start of a heap block.
>Call Stack:
>    HeapFunc1 in "C:\crun-evaluation-guide\common\Heap.c", 32:3 - 32:10
>    main in "C:\crun-evaluation-guide\common\Heap.c", 101:3 - 101:13
>    [_call_main + 0xd]
>Heap usage error @ 0x2280 Core: 0
>The address 0x20001208 does not appear to be the start of a heap block.
>Call Stack:
>    HeapFunc1 in "C:\crun-evaluation-guide\common\Heap.c", 34:3 - 34:10
>    main in "C:\crun-evaluation-guide\common\Heap.c", 101:3 - 101:13
>    [_call_main + 0xd]
>Heap usage error @ 0x2286 Core: 0
>The address 0x20001249 does not appear to be the start of a heap block.
>Call Stack:
>    HeapFunc1 in "C:\crun-evaluation-guide\common\Heap.c", 35:1 - 35:1
>    main in "C:\crun-evaluation-guide\common\Heap.c", 101:3 - 101:13
>    [_call_main + 0xd]
>Out of heap space @ 0x2292 Core: 0
>There is no more heap space to allocate.
>A request for 4120 bytes could not be satisfied.
>A total of 36 bytes have been allocated in 1 heap blocks.
>Call Stack:
>    HeapFunc2 in "C:\crun-evaluation-guide\common\Heap.c", 44:3 - 44:9
>    main in "C:\crun-evaluation-guide\common\Heap.c", 102:3 - 102:13
>    [_call_main + 0xd]
>
>     CSpyBat terminating.
>```

</details>

>[!NOTE]
>- All `cspybat` options for C-RUN begin with `--rtc_*`. For more information about these options, see _cspybat options for C-RUN_ in the _C-SPY Debugging Guide_.
>- The IDE might regenerate the project's `*.xcl` files, overwriting your changes. Use `attrib +r settings/*.xcl` if you wish to pin it and avoid further automatic changes performed by the IDE. Use `attrib -r settings/*.xcl` to remove the read-only attribute.


## Redirecting C-RUN messages to a serial port
Now consider scenarios where there is a need for electrical insulation, or for running the device in its real operating environment where there should be no access to debug ports, etc. In this section you will find information on how to customize your applications to reroute C-RUN raw messages to the desired communications channel so that they can be captured during the field testing for post-mortem analysis.

>[!NOTE]
>In this guide, we will not offer any source code that relies on hardware-specific communication peripherals. It is assumed that the Hardware Abstraction Layer (HAL) in the application has been correctly initialized and it is ready for operation, providing serial transmission support through a function such as `serial_send(channel, unsigned char)`. Ultimately `serial_send()` can be replaced by an equivalent function for writing C-RUN raw messages to any suitable media (e.g., SPI, I2C, RAM, Flash, etc.).

### Procedure
1. Add the `$EW_DIR$/<target>/src/lib/crun/ReportCheckFailedStdout.c` source file to your project.

2. Open `ReportCheckFailedStdout.c`.
>On the editor window tab you might see __[Read-Only]__ (or __[RO]__). This indicates that the file was added directly from the IAR Embedded Workbench installation directory, which is write-protected. Leave this file unchanged for future reference.

3. Choose __File__ → __Save As__.

4. A message is displayed asking "The file is read-only. Would you like to remove the read-only attribute?". Click __No__, navigate to the project's folder and save a copy of the file there.
>Now, __[Read-Only]__ (or __[RO]__) should not be visible on the editor tab.

5. In the function `__iar_ReportCheckFailedStdout()`, comment out the call to `__write()` and insert the following code:
```c
  //__write(_LLIO_STDOUT, (unsigned char const *)buf, (size_t)(b - buf));
  for (size_t i = 0; i < (size_t)(b - buf); i++)
  {
    serial_send(USART7, (unsigned char)buf[i]);
  }
```

6. Choose __Project__ → __Options__ → __Linker__ → __Extra Options__ and use this command line option:

![image](https://github.com/IARSystems/crun-evaluation-guide/assets/54443595/021c8c4f-61db-4e56-ba42-b59299f85a34)

>```
>--redirect __iar_ReportCheckFailed=__iar_ReportCheckFailedStdout
>```

> [!NOTE]
> - Alternatively, the low-level I/O `__write()` function can be overridden, provided that it does not affect other parts of your application. For more information, refer to the article [Overriding and redirecting library modules without rebuilding the entire library](https://www.iar.com/knowledge/learn/programming/overriding-and-redirecting-library-modules-without-rebuilding-the-entire-library/).


### Run the board in stand-alone mode
1. Connect the Debug probe to the target.
2. In the IDE, choose __Project__ → __Download__ → __Download Active Application__ to flash the device with the the application.
3. Power off and disconnect the debug probe from the board.
4. Launch a Virtual Terminal Emulator (such as [Tera Term VT](https://teratermproject.github.io/index-en.html)) and connect it to the target board's serial port.
5. Power up the board and verify that the C-RUN raw messages are being displayed in your Virtual Terminal Emulator.

![image](https://github.com/IARSystems/crun-evaluation-guide/assets/54443595/5f8bffc3-58a4-4050-abf6-f22f4b93061d)

6. Save the collected `CRUN_ERROR` messages to a text file (e.g., `field-tests-with-crun.txt`).

### Filtering the collected messages
In possession of the C-RUN raw messages collected from the field, feed it back to C-RUN itself using `cspybat`. The `cspybat` utility provides the `--rtc_raw_to_txt` option for converting the raw messages to human-readable text.

1. Append the `--rtc_raw_to_txt="/path/to/field-tests-with-crun.txt"` to the project's `settings/<project>.<cfg>.general.xcl`.

2. Run `cspybat`:
```
settings/<project>.<cfg>.cspy.bat
```

<details><summary><b>Output example</b> (click to expand)</summary>
 
>```
>C:\project\settings>"C:\IAR\EW\ARM\9.50.2\common\bin\cspybat"
>-f "C:\project\settings\project.Debug.general.xcl"
>--backend -f "C:\project\settings\project.Debug.driver.xcl"
>
>     IAR C-SPY Command Line Utility V9.3.2.391
>     Copyright 2000-2023 IAR Systems AB.
>
>crun_fail Signed integer overflow
>-- Result is greater than the largest representable number:
>--   1 (0x1) + 2147483647 (0x7fffffff).
>crun_fail Integer conversion failure
>-- Conversion changes the value from -2147483648 (0x80000000)
>-- to                                 2147483648 (0x80000000).
>```

</details>

>[!NOTE]
>Call Stack Information is not provided in this mode.


## Summary
C-RUN is a powerful runtime analysis add-on for IAR Embedded Workbench that can make a difference when you run field tests. Are you interested in using C-RUN for your projects? [__Request a quote__](https://iar.com/buy) for the licensing option that suits your needs.

For in-depth C-RUN information, refer to _C-RUN runtime error checking_ in the _C-SPY Debugging Guide_ bundled with the IAR product you use.


## Issues
Have you found an issue or do you have a suggestion related to [this guide][url-repo]? Please use the public issue tracker.
- Do not forget to take a look at [earlier issues][url-repo-issue-old].
- If you create a [new][url-repo-issue-new] issue, please describe it in detail.

Do not use the public issue tracker if you need technical support. The issue tracker is not a support forum. For support options refer to [IAR Support](https://iar.com/support).

>:envelope: You can also privately reach out to us via <a href="mailto:fae.emea@iar.com?subject=[GitHub] C-RUN Evaluation Guide -- Contacting via email">email</a>.

<!-- Links -->
[url-repo]:                https://github.com/iarsystems/crun-evaluation-guide
[url-repo-wiki]:           https://github.com/iarsystems/crun-evaluation-guide/wiki
[url-repo-issue-new]:      https://github.com/iarsystems/crun-evaluation-guide/issues/new
[url-repo-issue-old]:      https://github.com/iarsystems/crun-evaluation-guide/issues?q=is%3Aissue+is%3Aopen%7Cclosed
