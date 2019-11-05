/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Microsoft Corporation. All rights reserved.
 *  Licensed under the MIT License. See License.txt in the project root for license information.
 *--------------------------------------------------------------------------------------------*/

 // See https://stackoverflow.com/questions/52868095/add-tasks-to-tasks-json-for-users-of-a-vscode-extension

import * as vscode from 'vscode';
//import { RakeTaskProvider } from './rakeTaskProvider';
//import { CustomBuildTaskProvider } from './customTaskProvider';




/////////////////////////////////


class CSQFVMTaskProviderCompile implements vscode.TaskProvider {
	static staticType: string = "sqf_vm_compile";
	private tasks: vscode.Task[] | undefined;

	private sharedState: string | undefined;

	constructor(private workspaceRoot: string) { }

	public provideTasks(): vscode.Task[] {

		let myExt = vscode.extensions.getExtension("Sparker95.sqf-vm-vscode");
		let myExtDir = "C:\\"; // Otherwise it complains that myExt.extensionPath might be null
		if (myExt) {
			myExtDir = myExt.extensionPath;
		}

		// Compile task
		let taskCompile = new vscode.Task(
				{type: CSQFVMTaskProviderCompile.staticType},
				"Compile (some SQF functions are NYI)",
				"SQF-VM", // Shows up as SQF-VM: Compile
				new vscode.ProcessExecution (
					"SQF-VM/sqfvm.exe",
					[ // Arguments
						"-a",
						"--no-execute-print",
						"--parse-only",
						"--load",
						".",
						"-i",
						"${file}",
						"--disable-macro-warnings"
					],
					{cwd: myExtDir}
				),
				["sqf_vm_abs"] // Problem matchers
			);
		return [ taskCompile ];
	}

	public resolveTask(_task: vscode.Task): vscode.Task | undefined {
		return _task;
	}
}

class CSQFVMTaskProviderPreprocess implements vscode.TaskProvider {
	static staticType: string = "sqf_vm_preprocess";
	private tasks: vscode.Task[] | undefined;

	private sharedState: string | undefined;

	constructor(private workspaceRoot: string) { }

	public provideTasks(): vscode.Task[] {

		console.log("Extension: PROVIDE TASKS");

		let myExt = vscode.extensions.getExtension("Sparker95.sqf-vm-vscode");
		let myExtDir = "C:\\"; // Otherwise it complains that myExt.extensionPath might be null
		if (myExt) {
			myExtDir = myExt.extensionPath;
		}

		// Preprocess task
		let taskPreprocess = new vscode.Task(
			{type: CSQFVMTaskProviderPreprocess.staticType},
			"Preprocess",
			"SQF-VM", // Shows up as SQF-VM: Preprocess
			new vscode.ProcessExecution (
				"SQF-VM/sqfvm.exe",
				[ // Arguments
					"-a",
					"--no-execute-print",
					"--load",
					".",
					"-E",
					"${file}",
					"--disable-macro-warnings"
				],
				{cwd: myExtDir}
			),
			["sqf_vm_abs"] // Problem matchers
		);

		return [ taskPreprocess ];
	}

	public resolveTask(_task: vscode.Task): vscode.Task | undefined {
		return _task;
	}
}


class CSQFVMTaskProviderRun implements vscode.TaskProvider {
	static staticType: string = "sqf_vm_run";
	private tasks: vscode.Task[] | undefined;

	private sharedState: string | undefined;

	constructor(private workspaceRoot: string) { }

	public provideTasks(): vscode.Task[] {

		console.log("Extension: PROVIDE TASKS");

		let myExt = vscode.extensions.getExtension("Sparker95.sqf-vm-vscode");
		let myExtDir = "C:\\"; // Otherwise it complains that myExt.extensionPath might be null
		if (myExt) {
			myExtDir = myExt.extensionPath;
		}

		// Preprocess task
		let taskPreprocess = new vscode.Task(
			{type: CSQFVMTaskProviderRun.staticType},
			"Run (some SQF functions are NYI)",
			"SQF-VM", // Shows up as SQF-VM: Preprocess
			new vscode.ProcessExecution (
				"SQF-VM/sqfvm.exe",
				[ // Arguments
					"-a",
					"--no-execute-print",
					"--disable-macro-warnings",
					"--load",
					".",
					"-i",
					"${file}"
				],
				{cwd: myExtDir}
			),
			["sqf_vm_abs"] // Problem matchers
		);

		return [ taskPreprocess ];
	}

	public resolveTask(_task: vscode.Task): vscode.Task | undefined {
		return _task;
	}
}


/////////////////////////////////




let SQFVMTaskProviderCompile: vscode.Disposable | undefined;
let SQFVMTaskProviderPreprocess: vscode.Disposable | undefined;
let SQFVMTaskProviderRun: vscode.Disposable | undefined;

export function activate(_context: vscode.ExtensionContext): void {
	//console.log("Extension: ACTIVATE");
	//console.log("Extension: REGISTER TASK PROVIDER");
	SQFVMTaskProviderCompile = vscode.tasks.registerTaskProvider(CSQFVMTaskProviderCompile.staticType, new CSQFVMTaskProviderCompile(""));
	SQFVMTaskProviderPreprocess = vscode.tasks.registerTaskProvider(CSQFVMTaskProviderPreprocess.staticType, new CSQFVMTaskProviderPreprocess(""));
	SQFVMTaskProviderRun = vscode.tasks.registerTaskProvider(CSQFVMTaskProviderRun.staticType, new CSQFVMTaskProviderRun(""));
}

export function deactivate(): void {
	if (SQFVMTaskProviderCompile) {
		SQFVMTaskProviderCompile.dispose();
	}
	if (SQFVMTaskProviderPreprocess) {
		SQFVMTaskProviderPreprocess.dispose();
	}
	if (SQFVMTaskProviderRun) {
		SQFVMTaskProviderRun.dispose();
	}
}