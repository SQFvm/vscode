# SQF-VM for VSCode extension

This extension provides a few tasks to run SQF-VM in different modes from your VSCode.
Obvious application is to run SQF right in your editor, without any need to run Arma. Also you can compile your script to detect compilation and preprocessor errors prior to testing it in-game.

#### SQF-VM: Preprocess
Runs preprocessor on the current file.

#### SQF-VM: Compile
Preprocesses and compiles the current files.

#### SQF-VM: Run
Preprocesses, compiles and runs the current file. Output of commands like `diag_log`, `systemChat`, etc is displayed in the console.

# Limitations
- Not all SQF commands are implemented, so if you can't compile some script, it's possible that some command is not yet implemented.
- Include paths from pboprefix are not supported.

# Backend
This extension is powered by SQF-VM. For general functionality issues, please refer to SQF-VM.

# Authors
SQF-VM by @X39
Task configuration done by @billw2012
Extension by @Sperker95
