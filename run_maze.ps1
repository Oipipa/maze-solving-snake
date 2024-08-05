$ScriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition

cd $ScriptDir

$BuildDir = Join-Path $ScriptDir "build\Debug"
$env:PYTHONPATH = "$BuildDir;$env:PYTHONPATH"

python main.py
