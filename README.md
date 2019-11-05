# SQF-VM for VSCode extension

This extension provides a few tasks to run SQF-VM from your VSCode:

#### SQF-VM: Preprocess
Runs preprocessor on the current file. Will report preprocessing errors.

#### SQF-VM: Compile
Preprocesses and compiles the current files. Will report compilation errors.

#### SQF-VM: Run
Preprocesses, compiles and runs the current file. Output of commands like `diag_log`, `systemChat`, etc is displayed in the console.

# Limitations
- Not all SQF commands are implemented, so if you can't compile some script, it's possible that some command is not yet implemented.
- Include paths from pboprefix are not supported.
