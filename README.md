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

> __`Overview`__ `Arithmetic` `Bounds-checking` `< >`

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
>__C-RUN Runtime Checking__
>- [x] Enable
>   - [ ] Use checked heap
>   - [ ] Enable bounds checking
4. Make sure all these checks are selected:
>__Insert checks for__
>- [x] Integer overflow
>   - [x] Including unsigned 
>- [x] Integer conversion
>   - [x] Including explicit casts 
>- [x] Integer shift overflow
>   - [x] Including unsigned shifts 
>- [x] Division by zero
>- [x] Unhandled switch case

5. Click `  OK  ` to close the __Project Options__ dialog box.

6. Choose __Project__ → __Download and Debug__ (<kbd>Ctrl</kbd>+<kbd>D</kbd>) to start executing the application.

7. The C-SPY Debugger will hit a breakpoint at `main()`. Press <kbd>F5</kbd> to resume the program execution.

8. The execution will _Stop_, with the following line of code highlighted:

![image](https://user-images.githubusercontent.com/54443595/223120924-98fea4f5-ab7a-487e-8309-bf650db05ee8.png)

>In the editor window, C-SPY highlights in green the statement in which the execution stopped when the runtime error checking was triggered. In addition, C-RUN narrows the problem down and highlights the root cause of the runtime error in purple.

![image](https://user-images.githubusercontent.com/54443595/223120962-c875ed49-8322-4a44-b296-5decd196b6df.png)

> Concurrently, the __C-RUN Messages__ window (__View__ → __C-RUN__ → __Messages__) will break down the detected runtime error as well as its call stack. Clicking on the call stack takes you to the corresponding source code line.

9. Examine the remaining detected errors by pressing <kbd>F5</kbd> to resume the program execution until the next error message, or until the execution ends.

10. Stop the debug session (<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd>).

11. When you create applications, there are situations where relying on the wrap-around property of overflown unsigned integers is efficient. In such cases, specific C-RUN checks can simply be deselected. In the project's __Runtime checking__ options, disable these:
>__Insert checks for__
>- [x] Integer overflow
>   - [ ] Including unsigned 
>- [x] Integer conversion
>   - [ ] Including explicit casts 
>- [x] Integer shift overflow
>   - [ ] Including unsigned shifts 
>- [x] Division by zero

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
>__C-RUN Runtime Checking__
>- [x] Enable
>   - [ ] Use checked heap
>   - [x] Enable bounds checking
>
>__Instrumentation__
>- [x] Track pointer bounds
>   - [x] Check accesses
>   - [ ] Generate functions callable from non-instrumented code
>   - [ ] Check pointers for non-instrumented functions

6. Rebuild and run the project.

![image](https://user-images.githubusercontent.com/54443595/223133775-e597ae6e-fe4f-4d17-9f82-c6023bcdb6d1.png)
> Note that now C-RUN highlighted an out-of-bounds access for `*(ap+2)`. However, the execution stopped earlier, at the first `printf()` statement. The reason is that the compiler determines that pointer addresses used as parameters for those `printf()` calls are related and, with that, C-RUN efficiently can test them in one go.

7. Press <kbd>F5</kbd> to resume the execution.
> [!TIP]
> It will stop at the last statement of the application, indicating that the assignment is performed out of bounds. From a bounds-checking perspective, dynamically allocated memory is no different from local pointers, static buffers, or buffers on the stack.

8. Again, choose __Project__ → __Options__ (<kbd>Alt</kbd>+<kbd>F7</kbd>) → __Runtime Checking__ and take a look at the __Global bounds table__ group box.
> __Global bounds table__
>   - [x] Check pointers from non-instrumented memory<br>
>   Number of entries `2   `

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
```c
#ifdef __AS_BOUNDS__             // Module built with C-RUN Bounds checking?
#define default_no_bounds=on     // Turn OFF bounds-checking information generation
#include "library-header.h"
#define default_no_bounds=off    // Turn ON  bounds-checking information generation
#else
#include "library-header.h"
#endif
/* Application code */
```

To run this example, do this:

1. Select the  _Bounds-checking+libs_ project.
>This project comes with two build configurations, with different options for C-RUN:
> - `DoNotCheckPointersFromNonInstrumentedCode` and 
> - `CheckPointersFromNonInstrumentedCode`

2. Begin with the `DoNotcheckPointersFromNonInstrumentedCode` build configuration.
>At the top of the __Workspace__ window, you can switch between existing build configurations.

3. Choose __Project__ → __Options__ (<kbd>Alt</kbd>+<kbd>F7</kbd>) → __Runtime Checking__ and confirm these settings:
>__C-RUN Runtime Checking__
>- [x] Enable
>   - [ ] Use checked heap
>   - [x] Enable bounds checking
>
>__Instrumentation__
>- [x] Track pointer bounds
>   - [x] Check accesses
>   - [ ] Generate functions callable from non-instrumented code
>   - [ ] Check pointers for non-instrumented functions

4. Close the __Project Options__ dialog box, and choose __Project__ → __Download and Debug__ (<kbd>Ctrl</kbd>+<kbd>D</kbd>) to start executing the application.
>You should get no C-RUN errors, or any other indications that something is wrong. In the `DoNotCheckPointersFromNonInstrumentedCode` build configuration, turning off bounds-checking information for library headers worked well- (As it should do in most cases; returned pointers will not be bounds-checked but will have associated bounds that are always "large enough" to accommodate them.) In other words, this means that pointers originating from your code will be checked, but not pointers from the library. This should normally be perfectly acceptable and the process is non-intrusive in terms of code changes.

5. Stop the debug session (<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd>).
 
6. Switch to the `CheckPointersFromNonInstrumentedCode` build configuration.
>The `CheckPointersFromNonInstrumentedCode` build configuration demonstrates a situation where it is desirable to have _bounds checking_ for pointers and returned pointers defined in the library code.

7. Choose __Project__ → __Options__ (<kbd>Alt</kbd>+<kbd>F7</kbd>) → __Runtime Checking__ and make sure that the __C-RUN Runtime Checking__ options are:
>__C-RUN Runtime Checking__
>- [x] Enable
>   - [ ] Use checked heap
>   - [x] Enable bounds checking
>
>__Instrumentation__
>- [x] Track pointer bounds
>   - [x] Check accesses
>   - [ ] Generate functions callable from non-instrumented code
>   - [x] Check pointers for non-instrumented functions
>   
>__Global bounds table__
>- [x] Check pointers from non-instrumented memory
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
>__C-RUN Runtime Checking__
>- [x] Enable
>   - [x] Use checked heap
>   - [ ] Enable bounds checking
4. Choose __Project__ → __Download and Debug__ (<kbd>Ctrl</kbd>+<kbd>D</kbd>) to start executing the application.

5. For each reported error, examine the comments at that location in the code.

6. Comment out the line
```c
listsize = __iar_set_delayed_free_size(2);
```

7. Rebuild, and __Download and Debug__ (<kbd>Ctrl</kbd>+<kbd>D</kbd>) the application.


<!-- --------------------------------------------------------------------------------------------------- -->
## Using C-RUN in non-interactive mode
There are scenarios where it might not be possible to debug an application built with C-RUN information directly in the IDE. Perhaps there is need for electrical insulation, or for running the device in its real operating environment where there is no access to debug ports, etc.

By default, C-RUN messages are displayed in the __C-RUN Messages__ window in the IDE. The messages can alternatively be redirected to the the standard output stream (__`stdout`__). This means that capturing the C-RUN messages during field testing for post-mortem analysis might be attractive.

### Redirecting C-RUN messages to the standard output stream
All you need to do is to redirect the built-in function `__iar_ReportCheckFailed()` to `__iar_Report_Check_FailedStdOut()`.

1. Choose an application project built with C-RUN information.

2. Choose __Project__ → __Options__ → __Linker__ → __Extra Options__ and specify this command line option:
>```
>--redirect __iar_ReportCheckFailed=__iar_ReportCheckFailedStdout
>```

> [!NOTE]
> For your convenience, the source file `$EW_DIR$/<target>/src/lib/crun/ReportCheckFailedStdOut.c`, which implements the `__iar_Report_Check_FailedStdOut()` function, was added to every application project in this guide's workspace. The source file comes bundled with your product's installation. It is only there for reference as it was __excluded from build__, and it can be used as starting point for any customizations (for example, serial port output).

3. Choose __Project__ → __Download and Debug__ (<kbd>Ctrl</kbd>+<kbd>D</kbd>) to start executing the application.

4. Choose __View__ → __C-RUN__ → __Messages__ to open the __C-RUN Messages__ window.
5. Choose __View__ → __C-RUN__ → __Terminal I/O__ to open the __Terminal I/O__ window.
6. Choose __Debug__ → __Logging__ → __Set Terminal I/O Log File__ and select the __Enable Terminal I/O log file__ option.

![image](https://user-images.githubusercontent.com/54443595/223496215-7f2f5bbe-82ea-440b-a204-17987c7c9321.png)
> __Note__ We will use the `TermIO.log` file later.

7. Press <kbd>F5</kbd> to resume the application execution.
>Note that the __C-RUN Messages__ window is empty now. Any messages are redirected to `stdout`, and each message is printed in raw format in the C-SPY __Terminal I/O__ window:

![image](https://user-images.githubusercontent.com/54443595/223490090-3c0e7441-f31e-4a0b-b867-90228029b013.png)

> [!NOTE]
> C-RUN for Arm depends on the _semihosting_ interface used by the C-RUN library function `__iar_ReportCheckFailed()`. Semihosting enables code that executes on the target system to interface with a debugger running on the host computer, while taking advantage of its low-level I/O facilities.


### Running the application from the command line
IAR Embedded Workbench includes the IAR C-SPY Command Line Utility (`cspybat.exe`). Using this utility, C-SPY can run applications from the command line. When an application for Arm is built using the runtime library semihosting option, this utility can take advantage of the host's standard output stream (__stdout__) to print the application's messages (for example, via `printf()`, etc.).

1. Launch a __Command Prompt__ shell and change to the __settings__ folder.

2. Execute `<project-name>.Debug.cspy.bat`, replacing `<project-name>` with your actual project's name.
>For every build configuration you create, IAR Embedded Workbench will create an automatic batch file (`<project-name>.<build-configuration>.cspy.bat`) for you. Inspect the script and its accompanying files and you will see all project parameters that are needed to execute the application from the command line.


### Filtering C-RUN raw messages
The C-RUN messages are encoded to be used in the IDE. In the console they are shown in raw text format. The `cspybat` utility provides the `--rtc_filter` option for converting the raw messages to human-readable text.

1. Edit `settings\<project-name>.Debug.general.xcl`, to add this line after `--rtc_enable`, and save:
```
--rtc_filter
```

2. Execute the project's `.cspy.bat` file.
> Notice that now, in filtering mode, `cspybat` waits for input. You could paste C-SPY raw messages in the terminal that executes C-SPY and they would be automatically converted to human-readable text.

3. Take advantage of previously generated messages you got in [Redirecting C-RUN messages to the standard output stream](#redirecting-c-run-messages-to-the-standard-output-stream) and redirect them as input for running C-SPY with the C-RUN filtering capabilities:
```
...\settings><project-name>.Debug.cspy.bat < ..\TermIO.log
```

<details><summary><b>Expected output example</b> (click to expand)</summary>

>```
>...\crun-evaluation-guide\arm\settings>"C:\IAR\EW\ARM\8.11.1\common\bin\cspybat" 
> -f "...\crun-evaluation-guide\arm\settings\Arithmetic.Debug.general.xcl" 
> --backend 
> -f "...\crun-evaluation-guide\arm\settings\Arithmetic.Debug.driver.xcl"
> 
>     IAR C-SPY Command Line Utility V8.0.6.4851
>     Copyright 2000-2017 IAR Systems AB.
>
>crun_fail Integer conversion failure
>-- Conversion changes the value from         500 (0x000001f4)
>-- to                                        -12 (0xf4).
>-- Arithmetic.c\41:8-14
>crun_fail Integer conversion failure
>-- Conversion changes the value from         500 (0x000001f4)
>-- to                                        244 (0xf4).
>-- Arithmetic.c\50:8-22
>crun_fail Integer conversion failure
>-- Conversion changes the value from  244 (0xf4)
>-- to                                 -12 (0xf4).
>-- Arithmetic.c\50:8-22
>crun_fail Signed integer overflow
>-- Result is greater than the largest representable number:
>--   2147483647 (0x7fffffff) + 2 (0x2).
>-- Arithmetic.c\23:10-14
>crun_fail Unsigned integer overflow
>-- Result is greater than the largest representable number:
>--   4294967295 (0xffffffff) + 2 (0x2).
>-- Arithmetic.c\32:10-15
>crun_fail Shift overflow
>-- Left shift of negative value:
>--   -2147483647 (0x80000001) << 1.
>-- Arithmetic.c\59:10-15
>crun_fail Division by zero
>-- Division by zero.
>-- Arithmetic.c\76:7-11
>crun_fail Unhandled case in switch
>-- Switch to undefined case label.
>-- Arithmetic.c\84:3-12
>```
> __Note__ In contrast to using C-RUN from the IDE, C-RUN raw messages do __not__ contain call stack information.

</details>

## Redirecting C-RUN raw messages to a serial port
Use the information in this section to customize how C-RUN raw messages are routed in your applications.
We will not offer any source code that relies on hardware-specific communication peripherals.
Instead, we will abstract from hardware implementation details and refer to a generic `serial_send(channel, unsigned char)` function.

We assume that the hardware peripheral has been correctly initialized for operation, and that a similar function has been implemented somewhere else in your application's drivers.

Now that you know how to redirect C-RUN raw messages to `stdout`, you can customize the `__iar_ReportCheckFailedStdout()` function to print to a serial port, starting from the provided `$EW_DIR$/<target>/src/lib/crun/ReportCheckFailedStdout.c` source file.

1. Add the `$EW_DIR$/<target>/src/lib/crun/ReportCheckFailedStdout.c` source file to your project.

2. Open `ReportCheckFailedStdout.c`.
>On the editor window tab you might see __[Read-Only]__ or __[RO]__. This indicates that the file was added directly from the IAR Embedded Workbench installation directory, which is write-protected. Leave this file unchanged for future reference.
3. Choose __File__ → __Save As__.

4. A message is displayed asking "The file is read-only. Would you like to remove the read-only attribute?". Click __No__, navigate to the project's folder and save a copy of the file there.
>Now, __[Read-Only]__ (or __[RO]__) should not be visible on the editor tab.

5. In the function `__iar_ReportCheckFailedStdout()`, comment out the call to `__write()` and insert the following code:
```c
  //__write(_LLIO_STDOUT, (unsigned char const *)buf, (size_t)(b - buf));
  for (size_t i = 0; i < (size_t)(b - buf); i++)
  {
    serial_send(USART6, (unsigned char)buf[i]);
  }
```

> [!NOTE]
> - `serial_send()` could be replaced by another function that sends the characters from the C-RUN messages strings to other media such as SPI, I2C, RAM, Flash, etc.
> - Alternatively, the low-level I/O `__write()` function can be overridden, provided that it does not affect other parts of your application. For more information, refer to the article [Overriding and redirecting library modules without rebuilding the entire library](https://www.iar.com/knowledge/learn/programming/overriding-and-redirecting-library-modules-without-rebuilding-the-entire-library/).


### Run the board in stand-alone mode
1. Launch a Virtual Terminal Emulator (such as Tera Term VT) and connect it to the serial port.
2. Choose __Project__ → __Download and Debug__ to start executing the application.
3. Power off and disconnect the debug probe from the board.
4. Power up the board and verify that the C-RUN raw messages are being displayed in your Virtual Terminal Emulator.

![image](https://user-images.githubusercontent.com/54443595/223522886-2e792b4f-0deb-41a3-b4d5-8f2d76c89e85.png)
>C-RUN raw messages should be seen from the Virtual Terminal Emulator.
For C-RUN messages collected from the serial port during the field test, do as explained in the [Filtering C-RUN Raw Messages](##filtering-c-run-raw-messages) section: feed the raw messages so that the `--rtc_filter` option converts them to human-readable format.

>:bulb: To prevent `cspybat` from re-flashing a target when filtering C-RUN raw data this way, choose __Project__ → __Options__ → __Debugger__ → __Download__ and deselect the option __Use flash loader(s)__. The corresponding `.cspy.bat` script in the settings folder will be updated accordingly when you close the workspace. 


## Summary
C-RUN is a powerful runtime analysis add-on for IAR Embedded Workbench that can make a difference when you run field tests. Are you interested in using C-RUN for your projects? [__Request a quote__](https://iar.com/buy) for the licensing option that suits your needs.

For in-depth C-RUN information, refer to _C-RUN runtime error checking_ in the _C-SPY Debugging Guide_ bundled with the IAR product you use.


## Issues

### Disclaimer
The information in this repository is subject to change without notice and does not represent a commitment on any part of IAR. While the information contained 
herein is assumed to be accurate, IAR assumes no responsibility for any errors or omissions.

Have you found an issue or do you have a suggestion related to [this guide][url-repo]? Please use the public issue tracker.
- Do not forget to take a look at [earlier issues][url-repo-issue-old].
- If you create a [new][url-repo-issue-new] issue, please describe it in detail.

>:envelope: You can also privately reach out to us via <a href="mailto:fae.emea@iar.com?subject=[GitHub] C-RUN Evaluation Guide -- Contacting via email">email</a>.
<!-- Links -->
[url-repo]:                https://github.com/iarsystems/crun-evaluation-guide
[url-repo-wiki]:           https://github.com/iarsystems/crun-evaluation-guide/wiki
[url-repo-issue-new]:      https://github.com/iarsystems/crun-evaluation-guide/issues/new
[url-repo-issue-old]:      https://github.com/iarsystems/crun-evaluation-guide/issues?q=is%3Aissue+is%3Aopen%7Cclosed
