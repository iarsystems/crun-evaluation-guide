# Evaluation Guide for the IAR C-RUN


<!-- --------------------------------------------------------------------------------------------------- -->
## What is C-RUN?
[C-RUN](https://iar.com/crun) is an add-on to the IAR C-SPY Debugger, completely integrated into the IAR Embedded Workbench. It helps you to ensure code quality in both your C and C++ code by inserting efficient instrumentation to the application for automatic runtime error checking capabilities.

<!-- ![image](https://user-images.githubusercontent.com/54443595/222785546-f0f2a98f-24b5-4d05-a341-6ecd8cc6e84a.png) -->


<!-- --------------------------------------------------------------------------------------------------- -->
## What is in this guide?
This guide contains a walk-through for those evaluating the runtime error checking capabilities offered by C-RUN.

You can evaluate it right now for free.


<!-- --------------------------------------------------------------------------------------------------- -->
## Software Requirements
This guide works for any of the products mentioned below, given that the following requirements are met:
| __Product__ | __Target Architecture__ | __Required Version__ | __Required License Types__ |
| - | - | - | - |
| IAR Embedded Workbench | [Arm](https://iar.com/ewarm) | 8.11 or later | - Cortex-M or,<br>- Standard or,<br>- Time-limited |
| IAR Embedded Workbench | [Renesas RX](https://iar.com/ewrx) | 3.10 or later | - Standard or,<br>- Time-limited |

>### C-RUN licensing considerations
>:bulb: No special action needs to be taken when evaluating C-RUN in code size limited mode. This mode was created for allowing customers to evaluate C-RUN using smaller pieces of code while exploring its tight integration with the IAR C-SPY Debugger.
>
>:warning: The size-limited mode is __not__ intended for use in production environment. Please get in [contact](https://iar.com/contact) with your IAR representative for access to non-limited licensing.
>
>:warning: C-RUN does not work with size-limited evaluation licenses (e.g., _KickStart_ or _Baseline_).


<!-- --------------------------------------------------------------------------------------------------- -->
## Exploring C-RUN
A number of example projects created as demonstrations of the feature set offered by C-RUN can be found in this repository.

To run the examples,

1. Clone this repository, or download its [latest release](https://github.com/IARSystems/crun-evaluation-guide/releases/latest).
2. Launch the IAR Embedded Workbench for a supported target architecture.
3. Open the _Workspace.eww_ found in the folder for the desired target architecture.

The Workspace will start in with a pre-selected project. In the Workspace `Overview` you will notice buttons for switching from one project to another. 

> `Overview` `Arithmetic` `Bounds-checking` `< >`<br>

>:bulb: The arrow buttons scrolls towards other buttons that did not fit into the panel width. The panel can be resized. Alternatively, the context menu for each project in the `Overview` gives you the __Set as active__ option.

Below you will find specific instructions for when running each of these projects.


<!-- --------------------------------------------------------------------------------------------------- -->
### `Arithmetic Checking` capabilities
The first example explores the most straightforward functionality in C-RUN: the _Arithmetic_ checks.

To run this example, follow the steps as described below.

1. Select the _Arithmetic_ project.

2. Go to __Project__  →  __Options__ → __Runtime Checking__ (<kbd>Alt</kbd> + <kbd>F7</kbd>).

3. Make sure that __C-RUN Runtime Checking__ is enabled
>__C-RUN Runtime Checking__
>- [x] Enable
>   - [ ] Use checked heap
>   - [ ] Enable bounds checking

4. Check that all the checks below are inserted
>__Insert checks for__
>- [x] Integer overflow
>   - [x] Including unsigned 
>- [x] Integer conversion
>   - [x] Including explicit casts 
>- [x] Integer shift overflow
>   - [x] Including unsigned shifts 
>- [x] Division by zero
>- [x] Unhandled switch case

5. Press the **`  OK  `** button to close the Project Options window.

6. **Download and Debug** the executable (<kbd>CTRL</kbd> + <kbd>D</kbd>).

7. The C-SPY Debugger will hit a breakpoint at `main()`. Hit <kbd>F5</kbd> to resume the program execution.

8. The execution will _Stop_, with the following line of code highlighted:

![image](https://user-images.githubusercontent.com/54443595/223120924-98fea4f5-ab7a-487e-8309-bf650db05ee8.png)

>In the Code Editor, C-SPY highlights in green the statement in which the execution stopped when the runtime error checking was triggered. On top of that, C-RUN narrows down to the runtime error's root cause, highlighted in purple.

![image](https://user-images.githubusercontent.com/54443595/223120962-c875ed49-8322-4a44-b296-5decd196b6df.png)

> Concurrently, __C-RUN Messages__ (__View__ → __C-RUN__ → __Messages__) will break down the detected runtime error as well as its call stack. Clicking on the call stack navigates to the corresponding source code line.

9. Examine the remaining detected errors by hitting <kbd>F5</kbd> to resume the program execution until the next error message or until the program ends.

10. Terminate the debugging session (<kbd>CTRL</kbd> + <kbd>SHIFT</kbd> + <kbd>D</kbd>).

11. In the project's __Runtime checking__ options, disable the following
>__Insert checks for__
>- [x] Integer overflow
>   - [ ] Including unsigned 
>- [x] Integer conversion
>   - [ ] Including explicit casts 
>- [x] Integer shift overflow
>   - [ ] Including unsigned shifts 
>- [x] Division by zero

12. Rebuild, Download and Debug the executable (<kbd>CTRL</kbd> + <kbd>D</kbd>).
> :bulb: When creating applications, there are situations where relying on the wrapping around property of overflown unsigned integers is efficient. In such cases, specific C-RUN checks can be simply deselected :white_medium_square:. Disabling the checks you do not need will generally yield improved execution time and code size.

13. By default, C-RUN will __Stop__ at each detected error. In the __C-RUN Messages__, the _Default action_ can be changed to __Log__ or __Ignore__.

>:bulb: __C-RUN Messages__ can be filtered by rules. For details, refer to the _Creating rules for messages_ section in the _C-SPY Debugging Guide_.


<!-- --------------------------------------------------------------------------------------------------- -->
### `Bounds Checking` capabilities
The second example explores the _Bounds Checking_ capabilities provided by C-RUN.

To run this example, follow the steps below.

1.  Select the _Bounds-checking_ project.

2. **Download and Debug** the executable (<kbd>CTRL</kbd> + <kbd>D</kbd>).

3. After the program reaches the breakpoint in the `main()` function, resume the execution (<kbd>F5</kbd>).
> Note how the program finishes its execution (`exit()`) without any apparent errors of any kind.

4. Terminate the debugging session (<kbd>CTRL</kbd> + <kbd>SHIFT</kbd> + <kbd>D</kbd>).

5. Go to __Project__ → __Options__ → __Runtime Checking__ (<kbd>Alt</kbd> + <kbd>F7</kbd>) and _enable bounds checking_ as below
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

> Note that now C-RUN highlighted out-of-bounds access for `*(ap+2)`. However, the execution stopped earlier, at the first `printf()` statement. The reason is that the compiler determines pointer addresses used as parameter for those `printf()` calls are related and, with that, C-RUN efficiently can test them in one go.

7. Hit <kbd>F5</kbd> to resume the program execution.
>:bulb: It will stop at the last statement of the program, indicating that the assignment is done out-of-bounds. From a bound checking perspective, dynamically allocated memory is no different from local pointers, static buffers or buffers on the stack.

8. Go back to __Project__  →  __Options__ → __Runtime Checking__ (<kbd>Alt</kbd> + <kbd>F7</kbd>) and take a look at the __Global bounds table__ frame.
> __Global bounds table__
>   - [x] Check pointers from non-instrumented memory<br>
>   Number of entries `2   `

>Pointers accessible trough other pointers need to have information in a table stored in memory. The __Number of entries__ field allows you to fine tune the number of slots available in the table. 
>
>:warning: Leaving __Number of entries__ blank will remove the limit, resulting in a large global bounds table (4k slots!). The number of entries you need is often fairly low, so that some experimentation towards shrinking the global table might be interesting for lowering the resource consumption for the instrumentation. While you are in control of this, do not worry if you use a number that is too low: if this happens you should get a warning message telling you about the global bounds table running out of slots.

9. Set the __Number of entries__ to `1   ` and close the __Project Options__ window.

10. Rebuild, Download and Debug the executable (<kbd>CTRL</kbd> + <kbd>D</kbd>).
> In this example there is only one pointer that needs to be kept in the table, hence a single entry does for the job.


<!-- --------------------------------------------------------------------------------------------------- -->
### `Bounds Checking` and libraries
Within scenarios where the main project relies on pre-built (/third-party) libraries, _bounds checking_ requires extra considerations for shared pointers.

The project _Bounds-checking+libs_ is a modified version of the _Bounds-checking_ project. The functionality available from the `IntMax.c` file was moved to a _Library project_ that produced a static library named `MaxLib.a`, pre-built with no C-RUN bounds checking instrumentation, as it would be the common case for third-party libraries where the code cannot be changed. 

When using pointers and pointer arguments between the _instrumented application code_ and the _non-instrumented library code_ one must inform the compiler (and linker) that functions in the library code do not have bounds check information. The best way to do so is to use `#pragma default_no_bounds=on/off` for when including a library header so we can inform the compiler that the library was not built with C-RUN Bounds checking information:
```c
#ifdef __AS_BOUNDS__             // Module built with C-RUN Bounds checking?
#define default_no_bounds=on     // Turn OFF bounds checking information generation
#include "library-header.h"
#define default_no_bounds=off    // Turn ON  bounds checking information generation
#else
#include "library-header.h"
#endif

/* Application code */
```

To run this example, follow the steps below.

1. Select the  _Bounds-checking+libs_ project.
>This project comes with 2 build configurations with different options for C-RUN:
> - `DoNotCheckPointersFromNonInstrumentedCode` and 
> - `CheckPointersFromNonInstrumentedCode`

2. Let's start with the `DoNotcheckPointersFromNonInstrumentedCode` build configuration.
>From the top of the __Workspace__ panel, you can switch between existing build configurations.

3. Go to __Project__ → __Options__ → __Runtime Checking__ (<kbd>Alt</kbd> + <kbd>F7</kbd>) and make sure the options are set as below
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

4. Close the __Project Options__ window, __Download and Debug__ the executable (<kbd>CTRL</kbd> + <kbd>D</kbd>).
>You should get no C-RUN errors reported nor other indications that something is wrong. In the `DoNotCheckPointersFromNonInstrumentedCode` build configuration, turning off bounds check information for library headers worked well as it will work in most cases; returned pointers will not be bounds-checked but will have associated bounds that are always "big enough" to accommodate them. In other words, this means that pointers originating from your code will be checked, but not pointers from the library. This might be perfectly acceptable and the process is non-intrusive in terms of code changes.

5. Terminate C-SPY (<kbd>CTRL</kbd> + <kbd>ALT</kbd> + <kbd>D</kbd>).
 
6. Switch to the `CheckPointersFromNonInstrumentedCode` build configuration.
>The `CheckPointersFromNonInstrumentedCode` build configuration demonstrates a situation where is desirable to have _bounds checking_ for pointers and returned pointers defined in the library code. 

7. Go to __Project__ → __Options__ → __Runtime Checking__ (<kbd>Alt</kbd> + <kbd>F7</kbd>) and make sure the __C-RUN Runtime Checking__ options are set as below

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

8. Build and run the program again. This time you should see one C-RUN message for the third `printf()` statement.
>Read the source code and compare the use of `__as_make_bounds()` for the pointer `ap` to how the bounds are set for the pointer used in the next `printf()` statement. We have also defined a project-specific macro to control the use of `__as_make_bounds()`. This built-in function is used when the returned pointer must be given sensible bounds. If for returned pointers is not given bounds, a bounds error will be generated on the first access made to the pointer. Note that this build configuration defines a preprocessor symbol called `CONFIG` that conditionally compile with `__as_make_bounds()` calls for giving pointers sensible bounds.

9. Comment out one of the calls to the `CRUN_MAKE_BOUNDS()` macro, rebuild and run.
>:grey_question: Did it change the output in the __C-RUN Messages__?


<!-- --------------------------------------------------------------------------------------------------- -->
### `Heap Checking` capabilities
C-RUN can check for errors in the use of heap memory. _Heap checking_ can catch when the application tries to use already freed memory, non-matching deallocation attempts and even leaked heap blocks.

When using _Heap checking_, each memory block is expanded with bookkeeping information and a buffer area, so that the blocks as seen by the application are not located side-by-side.

The various checker functions examine the bookkeeping information and the buffer areas and reports violations of correct heap usage.

>:warning: Using _checked heap_ substantially increases the likelihood of finding heap usage errors, but it’s **not** fail-safe.
>
>:warning: _Checked heap_ and _bounds checking_ can complement each other when tracking down dynamic memory usage errors. However, due to potential impact in terms of performance and overhead, it’s **not** advised to enable both at the same time.

To run this example, follow the steps below.

1. Select the _Heap_ project.

2. Go to __Project__  →  __Options__ → __Runtime Checking__ (<kbd>Alt</kbd> + <kbd>F7</kbd>).

3. Make sure that _Use checked heap_ is enabled
>__C-RUN Runtime Checking__
>- [x] Enable
>   - [x] Use checked heap
>   - [ ] Enable bounds checking

4. Download and Debug the executable (<kbd>CTRL</kbd> + <kbd>D</kbd>).

5. For each reported error, examine the comments at that location in the code.

6. Comment out the line
```c
listsize = __iar_set_delayed_free_size(2);
```

7. Rebuild, Download and Debug the executable (<kbd>CTRL</kbd> + <kbd>D</kbd>).


<!-- --------------------------------------------------------------------------------------------------- -->
## Using C-RUN in non-interactive mode
There are scenarios in which debugging an application built with C-RUN information in C-SPY Debugger directly from the IDE might not be possible. The reason might be due to the need for electrical insulation, or the need to run the device in its real operating environment where there is no access to debug ports, etc.

By default, C-RUN messages on the IDE are displayed in the __C-RUN Messages__ window. These messages can alternatively be redirected to the Standard Output (__`stdout`__). When we consider this option, capturing the C-RUN Messages during field testing for post-mortem analysis starts to sound like a plan.

### Redirecting C-RUN Messages to the Standard Output
All you need to do is to redirect the built-in function `__iar_ReportCheckFailed()` to `__iar_Report_Check_FailedStdOut()`.

1. Choose an Application Project built with C-RUN information.

2. Go to __Category__ → __Linker__ → __Extra Options__ and
>- [x] Use command line options
>Command line options: (one per line)
>
>```
>--redirect __iar_ReportCheckFailed=__iar_ReportCheckFailedStdout
>```
>:bulb: For your convenience, the source file `$EW_DIR$/<target>/src/lib/crun/ReportCheckFailedStdOut.c`, which implements the `__iar_Report_Check_FailedStdOut()` function was added to every application project in this guide's workspace. The source file comes bundled with your product's installation, it is there only for reference as it was __excluded from build__, and can be used as starting point for eventual customizations (e.g., serial port output).

3. __Download and Debug__ the executable (<kbd>CTRL</kbd> + <kbd>D</kbd>).

4. Go to __View__ → __C-RUN__ → __Messages__.
5. Go to __View__ → __Terminal I/O__.
6. Go to __Debug__ → __Logging__ → __Set Terminal I/O Log File...__ and __Enable Terminal I/O log file__.

![image](https://user-images.githubusercontent.com/54443595/223496215-7f2f5bbe-82ea-440b-a204-17987c7c9321.png)
>:bulb: We will use _TermIO.log_ later.

7. Hit <kbd>F5</kbd> to resume the program execution.
>Note that now the __C-RUN Messages__ window shows nothing. The messages were redirected to `stdout` and now each message is printed out in raw format in the C-SPY Terminal I/O.

![image](https://user-images.githubusercontent.com/54443595/223490090-3c0e7441-f31e-4a0b-b867-90228029b013.png)

>:bulb: C-RUN for Arm depends on the semihosting interface used by the C-RUN library function `__iar_ReportCheckFailed()`. Semihosting enables code running on the target system to interface with a debugger running on the host computer while taking advantage of its low-level I/O facilities.

### Running the application from the command line
The IAR Embedded Workbench includes the IAR C-SPY Command Line Utility (`cspybat.exe`). This utility enables you to run applications from the command line. When an application for Arm is built using the runtime library semihosting option, the utility can take advantage of the host's Standard Output (__stdout__) for printing out application's messages (e.g., via `printf()`, etc.).  

1. Launch a __Command Prompt__ shell and change to the __settings__ folder.

2. Execute `<project-name>.Debug.cspy.bat`, replacing the `<project-name>` by your actual project's name.
>For every build configuration you create, the IAR Embedded Workbench will create an automatic batch file (`<project-name>.<build-configuration>.cspy.bat`) for you. Take a peek at the script and its accompanying files and you will see all the project's parameters necessary for executing the application from the command line.

### Filtering C-RUN Raw Messages
The C-RUN Messages are encoded in a way to be used from the IDE. From the console they are shown in raw text format. The `cspybat` utility provides the `--rtc_filter` option for transforming the raw messages into their human-readable counterparts.

1. Edit `settings\<project-name>.Debug.general.xcl`, append the following line after `--rtc_enable` and save:
```
--rtc_filter
```

2. Execute the project's `.cspy.bat` file.
> You will notice that now, in filtering mode, `cspybat` waits for input. We could paste C-SPY raw messages on the terminal executing C-SPY and they would be automatically translated to their human-readable counterparts.

3. Now let's take advantage of previously generated messages we got during _Redirecting C-RUN Messages to the Standard Output_ and redirect it as input for running C-SPY with the C-RUN filtering capabilities:
```
...\settings><project-name>.Debug.cspy.bat < ..\TermIO.log
```
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
>:warning: Differently from when using from the IDE, C-RUN raw messages do __not__ contain call stack information.

## Redirecting C-RUN Raw Messages to a serial port
The information in this section serves as basis for you to customize the routing of the C-RUN raw messages in your applications.
It is provided without source code relying on any hardware-specific communication peripherals.
Instead we will abstract from hardware implementation details and refer to a generic `serial_send(channel, unsigned char)` function.

It is assumed that the hardware peripheral has been correctly initialized for operation and that a similar function has been implemented somewhere else in your application's drivers.

Now that we understand the mechanics of redirecting the C-RUN raw messages to `stdout` we can inspect how to customize the `__iar_ReportCheckFailedStdout()` for printing out to a serial port, starting from the provided `$EW_DIR$/<target>/src/lib/crun/ReportCheckFailedStdout.c` source file.

1. Add the `$EW_DIR$/<target>/src/lib/crun/ReportCheckFailedStdout.c` source file to your project.

2. Open `ReportCheckFailedStdout.c`.
>When looking at the file's tab on the editor window you might see `[RO]` (read-only). This indicates that the file is being added directly from the IAR Embedded Workbench installation folder, which is write-protected. It is advised to leave this file intact for future reference.

3. Go to __File__ → __Save as...__.

4. A message window will pop-up saying "The file is read-only. Would you like to remove the read-only attribute?". Answer `NO`, then from the "Save As..." dialog window, navigate back to the project's folder and save a copy of the file there.
>If the file had the `[RO]` on its tab before, it should be gone now.

5. In the function `__iar_ReportCheckFailedStdout()` comment the call to `__write()` and insert the following code:
```c
  //__write(_LLIO_STDOUT, (unsigned char const *)buf, (size_t)(b - buf));

  for (size_t i = 0; i < (size_t)(b - buf); i++)
  {
    serial_send(USART6, (unsigned char)buf[i]);
  }
}    
```

>:bulb: `serial_send()` could be replaced by another function that sends the characters from teh C-RUN messages strings to other mediums such as SPI, I2C, RAM, Flash, etc.

>:bulb: Alternatively, the low-level I/O `__write()` function can be overriden if that does not affect other parts of your application. For more information, refer to the article [Overriding and redirecting library modules without rebuilding the entire library](https://www.iar.com/knowledge/learn/programming/overriding-and-redirecting-library-modules-without-rebuilding-the-entire-library/).

### Run the board in stand-alone mode
1. Launch a Virtual Terminal Emulator (such as Tera Term VT) and connect it to the serial port.
2. __Download and Debug__ the application.
3. Power off, unplug the debugging probe from the board.
4. Power the board. and verify that the C-RUN raw messages are being displayed in your Virtual Terminal Emulator.

![image](https://user-images.githubusercontent.com/54443595/223522886-2e792b4f-0deb-41a3-b4d5-8f2d76c89e85.png)
>C-RUN raw messages should be seen from the Virtual Terminal Emulator.

In possession of the C-RUN Messages collected from the serial port during the field test, proceed as previously explained in the [Filtering C-RUN Raw Messages](##filtering-c-run-raw-messages) subsection, by feeding the raw messages so that the `--rtc_filter` option translates them into their human-readable counterparts for you.

>:bulb: For preventing `cspybat` from re-flashing a target when using it to filter C-RUN raw data, go to __Project Options__ → __Debugger__ → __Download__ and deselect :white_medium_square: Use flash loader(s), so that the corresponding `.cspy.bat` script in the settings folder will be updated accordingly when you close the Workspace. 

## Summary
C-RUN is a powerful runtime analysis add-on for the IAR Embedded Workbench which can make a difference when running field tests. Are you interested in using C-RUN for your projects? [__Request a quote__](https://iar.com/buy) for the licensing option that suits your needs.

For in-depth C-RUN information, refer to the section _C-RUN runtime error checking_ in the _C-SPY Debugging Guide_ documentation bundled with the IAR product in use.

## Issues

### Disclaimer
The information in this repository is subject to change without notice and does not represent a commitment on any part of IAR. While the information contained 
herein is assumed to be accurate, IAR assumes no responsibility for any errors or omissions.

Found an issue or have a suggestion related to [this guide][url-repo]? Feel free to use its public issue tracker.
- Do not forget to take a look at [earlier issues][url-repo-issue-old].
- If creating a [new][url-repo-issue-new] issue, please describe it in detail.

>:envelope: You can also privately reach out to us via <a href="mailto:fae.emea@iar.com?subject=[GitHub] C-RUN Evaluation Guide -- Contacting via email">e-mail</a>.

<!-- Links -->
[url-repo]:                https://github.com/iarsystems/crun-evaluation-guide
[url-repo-wiki]:           https://github.com/iarsystems/crun-evaluation-guide/wiki
[url-repo-issue-new]:      https://github.com/iarsystems/crun-evaluation-guide/issues/new
[url-repo-issue-old]:      https://github.com/iarsystems/crun-evaluation-guide/issues?q=is%3Aissue+is%3Aopen%7Cclosed
