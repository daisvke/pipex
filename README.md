# pipex
This program mimics pipes and redirections of the Unix system

## Installation
```
git clone git@github.com:daisvke/pipex.git
make
```

## Description
* pipex should be executed in this way:
```
./pipex file1 cmd1 cmd2 file2
```
Where file1 is the file from which we read, cmd1 and cmd2 are shell commands with their parameters,
and finally file2 is the file in which we write the output from the last command.
* The execution of the pipex program should do the same as the next shell command:
```
< file1 cmd1 | cmd2 > file2
```
* It handles multiple pipes:
```
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```
<p align=center>
  <img src="/screenshots/multiple_pipes.png" width="100%" />
</p>
* It supports '<<' and '>>' when the first parameter is "here_doc":
<p align=center>
  <img src="/screenshots/multiple_pipes_and_heredoc.png" width="100%" />
</p>
This is equivalent to:
```
cmd << LIMITER | cmd1 >> file
```

